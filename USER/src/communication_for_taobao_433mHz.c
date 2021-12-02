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
u8  vtTest=0;
u16 vSyncCnt=0;
void	deinitComm(void){
	DDL_ZERO_STRUCT(chgRecingParams);
}
void	initChargeComm(void){
	DDL_ZERO_STRUCT(chgRecingParams);
	DDL_ZERO_STRUCT(chgRecStts);
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
		if ( vtTt1>=6818) {						//step 1.33us
			set_Debug_Pin;
			vtCurrentTimer = LPTIMER_ReadCnt() & 0XFF;
			chgRecingParams.vHiStartTimer = ~vtCurrentTimer + 1;//正脉冲开始时间
			vTimeoutCnt = 0x10000 - vSystemLIRC5ms;
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
			if (chgRecingParams.vCommBitCnt >= 8) {	//一帧数据接收完成
				if(chgRecingParams.vRecByteCnt<2){
					if(chgRecingParams.vReceiveTemp==MASK_BYTE){
						chgRecingParams.vRecByteCnt++;
						chgRecingParams.vCommBitCnt=0;
					}
				}else{
					chgRecStts.vReceivedData = chgRecingParams.vReceiveTemp;
					chgRecStts.fReceivedResult = validResultBuff;
					deinitComm();
				}
			}
			chgRecingParams.vHiStartTimer = ~vtCurrentTimer + 1;//正脉冲开始时间
			vTimeoutCnt = 0x10000 - vSystemLIRC5ms;
		}
	} else {						//falling
		clr_Debug_Pin;
//		clrPowerLed;
		vtCurrentTimer = LPTIMER_ReadCnt() & 0XFF;
		chgRecingParams.vLowStartTimer = ~vtCurrentTimer + 1;//负脉冲开始时间
		//vTimeoutCnt = vtCurrentTimer;
//		vSyncCnt = 10000 - vTime1msCnt;
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
	if (validResultBuff == chgRecStts.fReceivedResult) {
		if (!vSkipCommKeyTimer) {
			if(vtTest++>1){
				vtTest=0;
			}
			if (COMM_CODE_ONOFF == chgRecStts.vReceivedData) {
				vKeyValue = FUNC_KEY_SHORT_PRESSED;
			} else if (COMM_CODE_15MIN == chgRecStts.vReceivedData) {
				vKeyValue = TIMER_15MIN_PRESSED;
			} else if (COMM_CODE_30MIN == chgRecStts.vReceivedData) {
				vKeyValue = TIMER_30MIN_PRESSED;
			} else if (COMM_CODE_60MIN == chgRecStts.vReceivedData) {
				vKeyValue = TIMER_60MIN_PRESSED;
			}
		}else{
			vSkipCommKeyTimer = SERIES_TIME_CONST;
		}
		vSkipCommKeyTimer = SERIES_TIME_CONST;
		chgRecStts.fReceivedResult=invalidResult;
	}
}
