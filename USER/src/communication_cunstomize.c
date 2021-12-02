/*
 * communication.c
 *
 *  Created on: 2019年12月6日
 *      Author: Bough_004
 */
#include "../inc/communication_customize.h"
#include "const.h"
#include "io_define.h"
#include "user_exti.h"
#include "user_basetime.h"
#include "user_menu.h"
#include "user_ddl.h"
#include "user_lptimer.h"
#include "user_key.h"
u8	vCommBitCnt=0;
//u8	receiveData[MAX_RECEIVE_INDEX+1]={0};
u8	receivedData=0;
u16	vTimeoutCnt=0;
//u8	vtTestindex=0;
ChgReceiveStts			chgRecStts;
ChgRecevingParams		chgRecingParams;
u8	vSkipCommKeyTimer=0;

void	deinitComm(void){
	DDL_ZERO_STRUCT(chgRecingParams);
	chgRecStts.vFirstRecData=0;
}
void	initChargeComm(void){
	DDL_ZERO_STRUCT(chgRecingParams);
	DDL_ZERO_STRUCT(chgRecStts);
	vTimeoutCnt=0;
}
/***************************************************************************************
 *
 * 通信接收函数
 *
 ****************************************************************************************/
void dataReceiveFunc(void) {
//	u32 vtCurrentTimer = 0;
	u16	vtCurrentTimer = 0;
	if (CommunPort->DI & CommunPin) {			//rising
		set_Debug_Pin;
		vtCurrentTimer=TIM_GetCountRegister(TIM11)&0xFFFF;
		chgRecingParams.vLowLastTimer=(vtCurrentTimer+chgRecingParams.vLowStartTimer)&0xffff;
		if(chgRecingParams.vLowLastTimer<CHARGE_LOW_BIT_LOW){
			deinitComm();								//ERROR
			return;
		}
		if(!chgRecingParams.fIsFirstHiGot){
			if(chgRecingParams.vLowLastTimer>CHARGE_HIGH_BIT_LOW){		//Sync code 时Low过长
				deinitComm();											//ERROR
				return;
			}
			chgRecingParams.fIsFirstHiGot=TRUE;
			chgRecingParams.vSyncCodeStts=SyncHiGot;
		}
		chgRecingParams.vHiStartTimer= 0x10000-vtCurrentTimer;		//正脉冲开始时间
		vTimeoutCnt=10000-vTime1msCnt;
		if(!vTimeoutCnt)
			vTimeoutCnt=1;
	} else {						//falling
		clr_Debug_Pin;
		vtCurrentTimer = TIM_GetCountRegister(TIM11)&0xFFFF;
		chgRecingParams.vLowStartTimer =  0x10000-vtCurrentTimer;		//负脉冲开始时间
		if (!chgRecingParams.vSyncCodeStts) {
			chgRecingParams.vSyncCodeStts = SyncLowGot;	//
		} else if ((chgRecingParams.vSyncCodeStts == SyncHiGot)||(chgRecingParams.vSyncCodeStts ==SyncCodeGot)) {
				if (chgRecingParams.fIsFirstHiGot) {
					chgRecingParams.vHiLastTimer=(vtCurrentTimer+chgRecingParams.vHiStartTimer)&0xffff;
					if(chgRecingParams.vHiLastTimer >= ERROR_SYNC_HIGH){
							deinitComm();	//ERROR
							return;
					}
					if (chgRecingParams.vHiLastTimer >= CHARGE_SYNC_BIT_HIGH) {//同步码
							chgRecingParams.vReceiveTemp = 0;
							chgRecingParams.vCommBitCnt = 0;
							chgRecingParams.vSyncCodeStts = SyncCodeGot;
//							clr_Debug_Pin;
							return;
						//}
					}
					else if (SyncCodeGot == chgRecingParams.vSyncCodeStts) {		//chgRecingParams.vHiLastTimer<CHARGE_SYNC_BIT_HIGH
						if (chgRecingParams.vHiLastTimer >= CHARGE_SYNC_BIT_HIGH) {
							deinitComm();	//ERROR
							return;
						}
						if (chgRecingParams.vHiLastTimer >= CHARGE_LOW_BIT_HIGH) {
							chgRecingParams.vReceiveTemp = chgRecingParams.vReceiveTemp >> 1;
							chgRecingParams.vCommBitCnt++;

						} else if (chgRecingParams.vHiLastTimer >= CHARGE_HIGH_BIT_HIGH) {
							chgRecingParams.vReceiveTemp = (chgRecingParams.vReceiveTemp >> 1) | 0x80;
							chgRecingParams.vCommBitCnt++;
						} else {	//error data
							deinitComm();	//ERROR
						}
						if (chgRecingParams.vCommBitCnt >= 8) {	//一帧数据接收完成

							if(!chgRecStts.vFirstRecData){
								chgRecStts.vFirstRecData=chgRecingParams.vReceiveTemp;
								return;
							}else{
								if(chgRecingParams.vReceiveTemp==chgRecStts.vFirstRecData){
									chgRecStts.vReceivedData = chgRecingParams.vReceiveTemp;
									chgRecStts.fReceivedResult = validResultBuff;
									deinitComm();
								}else{
									chgRecStts.vFirstRecData=chgRecingParams.vReceiveTemp;
								}
							}
						}
					}
				}
//			}
		}
	}
}
/***************************************************************************************
 *
 * 通信处理函数
 *
 ****************************************************************************************/

void	dataReceivedProcess(void){
	u16 vtTimer=0,vtTimerLast=0;
	if (validResultBuff == chgRecStts.fReceivedResult) {
		if (!vSkipCommKeyTimer) {
			if (COMM_CODE_ONOFF == chgRecStts.vReceivedData) {
				vKeyValue = FUNC_KEY_SHORT_PRESSED;
				vSkipCommKeyTimer = SERIES_TIME_CONST;
			} else if (COMM_CODE_15MIN == chgRecStts.vReceivedData) {
				vKeyValue = TIMER_15MIN_PRESSED;
				vSkipCommKeyTimer = SERIES_TIME_CONST;
			} else if (COMM_CODE_30MIN == chgRecStts.vReceivedData) {
				vKeyValue = TIMER_30MIN_PRESSED;
				vSkipCommKeyTimer = SERIES_TIME_CONST;
			} else if (COMM_CODE_60MIN == chgRecStts.vReceivedData) {
				vKeyValue = TIMER_60MIN_PRESSED;
				vSkipCommKeyTimer = SERIES_TIME_CONST;
			}else if(COMM_PAIRING_CODE == chgRecStts.vReceivedData){
				vKeyValue = Pairing_code;
				vSkipCommKeyTimer = SERIES_TIME_CONST;
			}else if(COMM_PAIRED_CODE == chgRecStts.vReceivedData){
				vKeyValue = Paired_code;
				vSkipCommKeyTimer = SERIES_TIME_CONST;
			}else if(COMM_PAIRED_FAIL_CODE == chgRecStts.vReceivedData){
				vKeyValue = Paired_fail;
				vSkipCommKeyTimer = SERIES_TIME_CONST;
			}
			chgRecStts.vFirstRecData=0;
		}
//		else{
//			vSkipCommKeyTimer = SERIES_TIME_CONST;
//		}
//		vSkipCommKeyTimer = SERIES_TIME_CONST;
		chgRecStts.fReceivedResult=invalidResult;
	}
	else if (vTimeoutCnt) {
		if (CommunPort->DI & CommunPin) {		//高电平时才处理
			vtTimer=vTime1msCnt;
			vtTimerLast=vTimeoutCnt+vtTimer-10000;
			if(vtTimerLast> 15){
				clr_Debug_Pin;
//				initChargeComm();
				DDL_ZERO_STRUCT(chgRecingParams);
				chgRecStts.fReceivedResult=invalidResult ;
				chgRecStts.vFirstRecData=0;
				vTimeoutCnt=0;
				vSkipCommKeyTimer=0;
			}
		}
	}
}
