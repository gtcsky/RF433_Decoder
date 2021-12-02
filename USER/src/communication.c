/*
 * communication.c
 *
 *  Created on: 2019年12月6日
 *      Author: Bough_004
 */
#include "string.h"
#include "stdlib.h"
#include "communication.h"
#include "const.h"
#include "io_define.h"
#include "user_exti.h"
#include "user_basetime.h"
#include "user_menu.h"
#include "user_ddl.h"
#include "user_lptimer.h"
#include "user_key.h"
#include "user_internalFlash.h"
u8	vCommBitCnt=0;
//u8	receiveData[MAX_RECEIVE_INDEX+1]={0};
u8	receivedData=0;
u16	vTimeoutCnt=0;
//u8	vtTestindex=0;
ChgReceiveStts			chgRecStts;
ChgReceiveStts			vtRecSttsTemp;
ChgRecevingParams		chgRecingParams;

u8	lastRecData[5]={9};
u8	vSkipCommKeyTimer=0;
u8  vtTest=0;
u16 vSyncCnt=0;
void	deinitComm(void){
	DDL_ZERO_STRUCT(chgRecingParams);
	//chgRecStts.fIsNotFirstReceived=0;
}
void	initChargeComm(void){
	DDL_ZERO_STRUCT(chgRecingParams);
	DDL_ZERO_STRUCT(chgRecStts);
}


void	 testLedFunc(void){
	if(getDebugPinStts)
		clr_Debug_Pin;
	else
		set_Debug_Pin;
}

void	validCodeReceived(void){
	memcpy(chgRecStts.vReceivedData,vtRecSttsTemp.vReceivedData,3);
	chgRecStts.fReceivedResult = validResultBuff;
	deinitComm();
	chgRecStts.fIsNotFirstReceived = 1;
}

/***************************************************************************************
 *
 * 通信接收函数
 *
 ****************************************************************************************/
void dataReceiveFunc(void) {
//	u32 vtCurrentTimer = 0;
	u8 vtCurrentTimer = 0;
	u16	vtTt0=0;
	u16	vtTt1=0;
	u16 vtACc = 0;
	if (CommunPort->DI & CommunPin) {			//rising
		vtTt0=TIM_GetCountRegister(TIM11);
		vtTt1=(vSyncCnt+vtTt0)&0xffff;
		if ( vtTt1>=SYNC_LOW_9MS) {						//step 1.33us
			vtCurrentTimer = LPTIMER_ReadCnt() & 0XFF;
			chgRecingParams.vHiStartTimer = ~vtCurrentTimer + 1;//正脉冲开始时间
//			vTimeoutCnt = 0x10000 - vSystemLIRC5ms;
			vTimeoutCnt=10000-vTime1msCnt;
			if(!vTimeoutCnt)
				vTimeoutCnt=1;
			chgRecingParams.fIsFirstHiGot = TRUE;
			chgRecingParams.vReceiveTemp = 0;
			chgRecingParams.vCommBitCnt = 0;
			chgRecingParams.vSyncCodeStts = SyncCodeGot;
			return;
		}
		else {
			if (!chgRecingParams.vSyncCodeStts) {
				deinitComm();				//ERROR
				return;
			}
		}
		if (chgRecingParams.vSyncCodeStts == SyncCodeGot) {
			vtCurrentTimer = LPTIMER_ReadCnt() & 0XFF;
			vtACc = vtCurrentTimer + chgRecingParams.vLowStartTimer;
			if (vtACc >= 0x0100)
				chgRecingParams.vLowLastTimer = vtACc & 0xff;
			else {
				chgRecingParams.vLowLastTimer = vtACc - NEG_LPT_CNT;
			}
			if ((chgRecingParams.vLowLastTimer < MIN_BIT_TIMER) || (chgRecingParams.vLowLastTimer > MAX_BIT_TIMER)) {
				deinitComm();				//ERROR
				return;
			}

			if (chgRecingParams.vLowLastTimer > VALID_BIT_TIMER) {
				chgRecingParams.vReceiveTemp = chgRecingParams.vReceiveTemp << 1;//low bit
				chgRecingParams.vCommBitCnt++;
			} else {
				chgRecingParams.vReceiveTemp = (chgRecingParams.vReceiveTemp << 1) | 0x01;//high bit
				chgRecingParams.vCommBitCnt++;
			}
			if (chgRecingParams.vCommBitCnt >= 8) {	//一个Byte数据接收完成
					chgRecingParams.vCommBitCnt=0;
				if(!chgRecStts.fIsNotFirstReceived){
					vtRecSttsTemp.vReceivedData[chgRecingParams.vRecByteCnt++]=chgRecingParams.vReceiveTemp;
					if(chgRecingParams.vRecByteCnt>=3){
						if(uvPairParams.fisPairing){
							memcpy(lastRecData,vtRecSttsTemp.vReceivedData,3);
							deinitComm();
							chgRecStts.fIsNotFirstReceived=1;
							return;
						}else{
							validCodeReceived();
						}
					}
				}else{
					if (vtRecSttsTemp.vReceivedData[chgRecingParams.vRecByteCnt++] == chgRecingParams.vReceiveTemp) {
						if (chgRecingParams.vRecByteCnt >= 3) {
							if(!uvPairParams.fisPairing){
								validCodeReceived();
							}
							else {
								if (!memcmp( lastRecData, vtRecSttsTemp.vReceivedData, 3)) {
									validCodeReceived();
								} else {
									memcpy( lastRecData, vtRecSttsTemp.vReceivedData, 3);
									deinitComm();
									chgRecStts.fIsNotFirstReceived = 1;
									return;
								}
							}
						}
					}else{
						vtRecSttsTemp.vReceivedData[chgRecingParams.vRecByteCnt-1]=chgRecingParams.vReceiveTemp;
					}
				}
			}
			chgRecingParams.vHiStartTimer = ~vtCurrentTimer + 1;//正脉冲开始时间
			vTimeoutCnt=10000-vTime1msCnt;
			if(!vTimeoutCnt)
				vTimeoutCnt=1;
		}
	} else {						//falling
		vtCurrentTimer = LPTIMER_ReadCnt() & 0XFF;
		chgRecingParams.vLowStartTimer = ~vtCurrentTimer + 1;//负脉冲开始时间
		vSyncCnt=0x10000-TIM_GetCountRegister(TIM11);
		if (!chgRecingParams.vSyncCodeStts) {
			return;
		} else if (chgRecingParams.vSyncCodeStts == SyncCodeGot)  {
			vtACc = chgRecingParams.vHiStartTimer + vtCurrentTimer;
			if (vtACc >= 0x0100)
				chgRecingParams.vHiLastTimer = vtACc & 0xff;
			else {
				chgRecingParams.vHiLastTimer = vtACc - NEG_LPT_CNT;
			}
			if ((chgRecingParams.vHiLastTimer < MIN_BIT_TIMER) || (chgRecingParams.vHiLastTimer > MAX_BIT_TIMER)) {
				deinitComm();				//ERROR
				return;
			}
		}
	}
}
/***************************************************************************************
 *
 * 通信处理函数
 *
 ****************************************************************************************/

//void	 chargeIcStatusProcess(u8 *vtStatus){
//	if(*vtStatus&0xC0){
//		if(*vtStatus&0x40){
//			vChargingCurrent=0.01;
//			fIsBattFully=TRUE;
//			fIsCharging = 1;
//		}else if(*vtStatus&0x80){
//			if(!fIsCharging){
//				startCharging();
//			}
//			if(fIsPowerOnFirst10s&&fIsBattFully){
//				startCharging();						//首次上电前10s,允许从满电变为充电状态
//			}
//		}
//	}else{
//		if(fIsCharging){
//			stopCharging();
//		}
//	}
//	if(*vtStatus&0x10){
//		fIsDischarging=TRUE;
//	}else if(fIsDischarging){
//		fIsDischarging=FALSE;
//	}
//}


void	dataReceivedProcess(void){
	u16 vtTimer=0,vtTimerLast=0;
	if (validResultBuff == chgRecStts.fReceivedResult) {
		if (!vSkipCommKeyTimer) {
			if(uvPairParams.fisPairing){
				storageParamsStruct.security_code[SECURITY_KEY_1]=chgRecStts.vReceivedData[SECURITY_KEY_1];
				storageParamsStruct.security_code[SECURITY_KEY_2]=chgRecStts.vReceivedData[SECURITY_KEY_2];
				storageParamsStruct.security_code[SECURITY_KEY_3]=(0xF0&chgRecStts.vReceivedData[SECURITY_KEY_3]);
				vKeyValue = Paired_code;
				StoreData2Flash();
				chgRecStts.fIsNotFirstReceived=0;
			} else {
				if((storageParamsStruct.security_code[SECURITY_KEY_1]==chgRecStts.vReceivedData[SECURITY_KEY_1])&&
						(storageParamsStruct.security_code[SECURITY_KEY_2]==chgRecStts.vReceivedData[SECURITY_KEY_2])&&
						(storageParamsStruct.security_code[SECURITY_KEY_3]==(0xF0&chgRecStts.vReceivedData[SECURITY_KEY_3]))){
					if (COMM_CODE_ONOFF == (chgRecStts.vReceivedData[SECURITY_KEY_3]&0x0F)) {
						vKeyValue = FUNC_KEY_SHORT_PRESSED;
					} else if (COMM_CODE_15MIN == (chgRecStts.vReceivedData[SECURITY_KEY_3]&0x0F)) {
						vKeyValue = TIMER_15MIN_PRESSED;
					} else if (COMM_CODE_30MIN == (chgRecStts.vReceivedData[SECURITY_KEY_3]&0x0F)) {
						vKeyValue = TIMER_30MIN_PRESSED;
					} else if (COMM_CODE_60MIN == (chgRecStts.vReceivedData[SECURITY_KEY_3]&0x0F)) {
						vKeyValue = TIMER_60MIN_PRESSED;
					}else{
						chgRecStts.fIsNotFirstReceived=0;		//only for test
					}
					testLedFunc();
					vSkipCommKeyTimer = SERIES_TIME_CONST;
					chgRecStts.fReceivedResult=invalidResult;
					return;
				}
			}
//		}else{
//			vSkipCommKeyTimer = SERIES_TIME_CONST;
//		}
//		vSkipCommKeyTimer = SERIES_TIME_CONST;
		}else{						//vSkipCommKeyTimer!=0
			if((storageParamsStruct.security_code[SECURITY_KEY_1]==chgRecStts.vReceivedData[SECURITY_KEY_1])&&\
					(storageParamsStruct.security_code[SECURITY_KEY_2]==chgRecStts.vReceivedData[SECURITY_KEY_2])&&\
					(storageParamsStruct.security_code[SECURITY_KEY_3]==(0xF0&chgRecStts.vReceivedData[SECURITY_KEY_3]))){
				if(( (chgRecStts.vReceivedData[SECURITY_KEY_3]&0x0F)==COMM_CODE_ONOFF)||\
						((chgRecStts.vReceivedData[SECURITY_KEY_3]&0x0F)==COMM_CODE_15MIN)||\
						((chgRecStts.vReceivedData[SECURITY_KEY_3]&0x0F)==COMM_CODE_30MIN)||\
						((chgRecStts.vReceivedData[SECURITY_KEY_3]&0x0F)==COMM_CODE_60MIN)){
					vSkipCommKeyTimer = SERIES_TIME_CONST;
				}
			}
		}
		chgRecStts.fReceivedResult=invalidResult;
	}
	else if (vTimeoutCnt) {
		if (CommunPort->DI & CommunPin) {		//高电平时才处理
			vtTimer=vTime1msCnt;
			vtTimerLast=vTimeoutCnt+vtTimer-10000;
			if(vtTimerLast> 30){
//				initChargeComm();
				DDL_ZERO_STRUCT(chgRecingParams);
				chgRecStts.fReceivedResult=invalidResult ;
				chgRecStts.fIsNotFirstReceived=0;
				vTimeoutCnt=0;
				vSkipCommKeyTimer=0;
			}
		}
	}
}
