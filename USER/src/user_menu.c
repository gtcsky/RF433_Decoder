/*
 * user_menu.c
 *
 *  Created on: 2019年8月15日
 *      Author: Bough_004
 */
#include "user_advtime.h"
#include "user_basetime.h"
#include "io_define.h"
#include "user_menu.h"
#include "misc.h"
#include "user_key.h"
#include "user_lptimer.h"
#include "user_adc.h"
#include "user_led.h"
#include "user_color.h"
#include "user_lightEffect.h"
#include "user_uart.h"
#include "user_tone.h"
#include "string.h"
#include "communication.h"
#include "user_internalFlash.h"
#include "user_ddl.h"
extern	u8		fTime50ms;
extern	u8		fTime100ms;
extern	u8		fTime500ms;
extern	u8		fTime1s;
u16		vSystem1s;
u16 		vTimeToSleep;								//vTimeToSleep*50ms  timeout , entry sleep mode
u8 		fIsSystemInitialing;
u8 		fIsSystemOff=0;								//	0/1  系统开启/关闭
u8 		fIsLightActive=OFF;									//	初始画面 灯光是否开启
u8		fTimerToPowerOnLED=0;
u8		vPowerOnLEDCnt=0;
UserPwmInitTypeDef  	userPwmParaStruct;
UserADCTypeDef		userAdcStruct;

uVUSturctDef	uvParams;
uPairStructDef uvPairParams;

systemErrorEnum vSystemStts;
U8	fIsTurnOffByException=FALSE;

u8		fIsNewCMDGod=FALSE;
float 	vSystemVdd=0;				//系统电压


u8	vBreakVoltDectCnt=0;
functionOffEnum	vFunctionIndex=Timer15mins;
void	uartRXPortAsNormalIoInput(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;						//input 模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;						//GPIOx_OTYPER   0/1 推挽输出/开漏输出
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;						//上拉
	GPIO_InitStruct.GPIO_Pin = UART_RX_GPIO_PIN;
	GPIO_Init(UART_RX_GPIO_PORT, &GPIO_InitStruct);					//位置  GPIOB4
}

void powerOnIoInit(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	/*--------------------------function key配置-----------------------------*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;						//input 模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;						//GPIOx_OTYPER   0/1 推挽输出/开漏输出
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;						//上拉
	GPIO_InitStruct.GPIO_Pin = KeyPower_Pin;							//
	GPIO_Init(KeyPower_Port, &GPIO_InitStruct);						//
	GPIO_InitStruct.GPIO_Pin = KeyTimer_Pin;							//
	GPIO_Init(KeyTimer_Port, &GPIO_InitStruct);						//
//	GPIO_InitStruct.GPIO_Pin = UART_RX_GPIO_PIN;						//
//	GPIO_Init(UART_RX_GPIO_PORT, &GPIO_InitStruct);					//
	GPIO_InitStruct.GPIO_Pin = CommunPin;							//
	GPIO_Init(CommunPort, &GPIO_InitStruct);						//
	//-----------------------以上为: 上拉输入口 设置------------------------------
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;					//不上拉
	GPIO_InitStruct.GPIO_Pin = Volt_Pin;								//4
	GPIO_Init(Volt_Port, &GPIO_InitStruct);							//AC检测
	GPIO_InitStruct.GPIO_Pin = Temperture_Pin;						//
	GPIO_Init(Temperture_Port, &GPIO_InitStruct);						//温度检测

	//-----------------------以上为: 不上拉输 入口设置------------------------------
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;					//output 模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;						//GPIOx_OTYPER   0/1 推挽输出/开漏输出
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;					//不上拉
	GPIO_InitStruct.GPIO_Pin = PowerLED_PIN|TimerLED_15m_PIN| TimerLED_30m_PIN|TimerLED_60m_PIN;						//
	GPIO_Init(PowerLED_PORT, &GPIO_InitStruct);
	clrPowerLed;
	clrTimer15mLed;
	clrTimer30mLed;
	clrTimer60mLed;
	GPIO_InitStruct.GPIO_Pin = P_UV_Power_PIN ;							//
	GPIO_Init(P_UV_Power_PORT, &GPIO_InitStruct);
	UV_PowerOff;
	GPIO_InitStruct.GPIO_Pin = DebugPinPin ;								//
	GPIO_Init(DebugPinPort, &GPIO_InitStruct);
	//-----------------------以上为: I2C口设置 设置------------------------------
//	GPIO_Init(zeroCrossOutPort, &GPIO_InitStruct);
	//-----------------------???: I2C??? ??------------------------------	
	GPIOA->AFR&=0xFFFF000F;											//
	GPIOA->AFR|=0xFFFF100F;											//GPIOA 复用配置 		PA1.2均为普通IO
	GPIOB->AFR&=0xFF00FFFF;
	GPIOB->AFR|=0xFF00FFFF;											//PB4,B5 普通IO
	GPIOC->AFR&=0xF0000FFF;
	GPIOC->AFR|=0x00000000;											//PC3~6 均为普通IO
	GPIOD->AFR&=0xF00000FF;
	GPIOD->AFR|=  0x0FF00000;											//PD5~6为ADC 其它全为普通IO

}

void resetEntrySleepTime(void){
		if(fIsSystemOff)
			vTimeToSleep=POWER_DOWN_MODE_TIMEOUT;							//4*5ms=20ms
		else
			vTimeToSleep=NORMAL_MODE_TIMEOUT;								//30s
}
void entryNormalModeChk(void){
		disableRXInt();
		UART_Config();									//uart重置
		LPTIMER_Cmd(DEBUG_LPTIMERx, ENABLE);			//醒来后重启LPT定时器
		resetEntrySleepTime();								//重置进入睡眠时间
}


void clrAllSttsBeforeEntrySleep(void){
	clrPowerKeyPressed;
	vPowerKeyTimer=0;
	vIsPowerKeyGod&=~(POWER_KEY_SHOT_PRRESS_GOD|POWER_KEY_LONG_PRRESS_GOD);
	fIsTurnOffByException=FALSE;
	vSystemStts = SystemOK;
	uvParams.fIsUVFuncOn=FALSE;
	uvParams.vTimeToTurnUV=0;
	UV_PowerOff;
	turnOffAllLightEffect();
	turnOffTone();
}

/**********************************************************************************
 *
 * 系统关机
 *
 ***********************************************************************************/
void systemPowerDown(void){
	fIsSystemOff=TRUE;
	clrAllSttsBeforeEntrySleep();
	Enter_DeepSleep();
}


void fucnPer50ms(void) {

}
void fucnPer100ms(void) {
}

void checkPairingTimeout(void){
	if(uvPairParams.fisPairing){
		if(uvPairParams.vPairingTimeOutCnt&&--uvPairParams.vPairingTimeOutCnt==0){
			pairedResult(FAILED);
		}
	}
}


void fucnPer500ms(void) {
	checkPairingTimeout();
}
/***********************************************************************
 *
 * 	get  system  voltage
 *
 ************************************************************************/
float getBattVolt(void){
	u16	vDaValue=0;
	vDaValue=getSignalChlADC(ADC_Channel7_ENABLE);
	return	(SYSTEM_VCAP_VOLT*ADC_CONST/vDaValue);
}

/***********************************************************************
 *
 * 	get  system  temperature
 *
 ************************************************************************/
//float getSystemperature(float vdd) {
//	u16	vDaValue=0;
//	//fIsSystemTempGot = 1;
//	vDaValue=getSignalChlADC(ADC_TEMP_CHL);
//	return ((vDaValue*vdd)/ADC_CONST);
//}
//void checkSystemHot(void){
//	if (fIsLightActive==ON){
//		vSystemVdd=getBattVolt();
//		vSystemTemperature=getSystemperature(vSystemVdd);
//		vSystemTemperature=(vSystemTemperature/vSystemVdd)*SYSTEM_VCAP_VOLT;			//折算成用Vcap分压的模式
//	}
//}


void UVcountDownFunc(void) {
	if (!fIsTurnOffByException) {								//发生错误时不进行计时
		if(vBreakVoltDectCnt)
			vBreakVoltDectCnt--;
		if (!uvParams.vTimeToTurnUV) {
			if (uvParams.fIsUVFuncOn || IsUVPowerON) {
				if (!uvParams.vUVTimeOutCnt) {
					systemOffByManual();
				} else {
					if (--uvParams.vUVTimeOutCnt == 0) {
						systemOffByManual();
					} else if (3== uvParams.vUVTimeOutCnt) {
						genEndTone();
					}
				}
			}
		} else {
			if (--uvParams.vTimeToTurnUV == 0) {
				genConfrimTone();
				UV_PowerOn;
				vBreakVoltDectCnt=BREAK_AD_DET_CONST;
				if(!uvParams.vUVTimeOutCnt){					//防止意外情况发生,造成时间到达后不关闭灯光
					startUvFunc();
					uvParams.vTimeToTurnUV =0;
				}
			} else if ((10 == uvParams.vTimeToTurnUV) || (5 == uvParams.vTimeToTurnUV)) {
				genKeyTone();
			}
		}
	}
}

void fucnPer1s(void) {
//	checkSystemHot();
	vSystemErrorCheck();
	UVcountDownFunc();
}

void entrySleepCheck(void) {
	if (vTimeToSleep && !--vTimeToSleep) {
		if (fIsSystemOff) {
			//Enter_DeepSleep();
			systemPowerDown();
		} else {
			fIsSystemOff=TRUE;
			systemPowerDown();
			//Enter_DeepSleep();
		}
	}
}

void fucnPer5ms(void ){
		if(fIsUartReceiving||(ON==fIsLightActive)||!GET_POWER_KEY_PIN_STTS){
			vTimeToSleep=2;
		}
		if(vSkipCommKeyTimer){
			vSkipCommKeyTimer--;
		}
		lightEffectFunc();
		voiceFunc();
//		entrySleepCheck();
		if(fTime50ms==1){
					fTime50ms=0;
					fucnPer50ms();
		}
		if(fTime100ms==1){
					fTime100ms=0;
					fucnPer100ms();
		}
		if(fTime500ms==1){
					fTime500ms=0;
					fucnPer500ms();
		}
		if(fTime1s==1){
					fTime1s=0;
					vSystem1s+=1;
					fucnPer1s();
		}
}
void	selectTimeIndicatior(u8 vtIndex){
	if(Timer15mins==vFunctionIndex){
			setTimer15mLedEffect();
			uvParams.vUVTimeOutCnt=TIMER_15MIN;
	}
	else if(Timer30mins==vFunctionIndex){
			uvParams.vUVTimeOutCnt=TIMER_30MIN;
			setTimer30mLedEffect();
	}
	else{
			uvParams.vUVTimeOutCnt=TIMER_60MIN;
			setTimer60mLedEffect();
	}
}

/***************************************************************
 *
 * 开始UV指示灯,并进入倒计时,但未真正开启UV电源
 *
 ****************************************************************/
void	startUvFunc(void){
	uvParams.fIsUVFuncOn=TRUE;
	turnOffAllLightEffect();
		setPowerLed;
		if (Timer15mins == vFunctionIndex)
			setTimer15mLed;
		else if (Timer30mins == vFunctionIndex)
			setTimer30mLed;
		else
			setTimer60mLed;
		uvParams.vTimeToTurnUV = STARTUP_TIMER;
}
/*****************************************************************
 *
 * 从错误中恢复
 *
 ******************************************************************/
void chkSystemResume(void){
	if(fIsTurnOffByException){
		startUvFunc();
	}
	fIsTurnOffByException=FALSE;
	vSystemStts = SystemOK;
}
/*****************************************************************
 * 	对码结果处理
 * 	PASSED:对码成功
 * 	FAILED:对码失败
 ******************************************************************/

void pairedResult(TestStatus vtResult){
	if(PASSED==vtResult)
		genConfrimTone();
	else
		genErrorTone();
	if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
		turnOffAllLightEffect();
		uvPairParams.fisPairing=FALSE;
		if(!fIsSystemOff)
			selectTimeIndicatior(vFunctionIndex);
	}
}
/**********************************************************************
 *
 * if time keys by remote process and return TRUE ,else return FALSE
 *
 ***********************************************************************/
int 	checkRemoteTimerKey(void){
	if (vKeyValue == TIMER_15MIN_PRESSED) {
		genKeyTone();
		if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
			vFunctionIndex = Timer15mins;
			selectTimeIndicatior(vFunctionIndex);
		}
		return	TRUE;
	}
	if (vKeyValue == TIMER_30MIN_PRESSED) {
		genKeyTone();
		if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
			vFunctionIndex = Timer30mins;
			selectTimeIndicatior(vFunctionIndex);
		}

		return	TRUE;
	}
	if (vKeyValue == TIMER_60MIN_PRESSED) {
		genKeyTone();
		if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
			vFunctionIndex = Timer60mins;
			selectTimeIndicatior(vFunctionIndex);
		}
		return	TRUE;
	}
	return	FALSE;
}



void MenuFunction(void ){
	if (!fIsSystemOff) {
		if (vKeyValue == FUNC_KEY_SHORT_PRESSED) {
			if(!uvParams.fIsUVFuncOn){
				startUvFunc();
				if (SYSTEM_OK == vSystemErrorCheck()) {
					genConfrimTone();
				}
			}else{
				clrAllSttsBeforeEntrySleep();
				genKeyTone();
				fIsSystemOff=TRUE;
				resetEntrySleepTime();				//响完tone 后再进入睡眠
				//systemOffByManual();
			}
		}
		if (vKeyValue == TIMER_KEY_SHORT_PRESSED) {
			genKeyTone();
			if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
				if (++vFunctionIndex > MAX_FUNCTION_INDEX) {
					vFunctionIndex = Timer15mins;
				}
				selectTimeIndicatior(vFunctionIndex);
			}
		}
//		if (vKeyValue == TIMER_15MIN_PRESSED) {
//			genKeyTone();
//			if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
//				vFunctionIndex = Timer15mins;
//				selectTimeIndicatior(vFunctionIndex);
//			}
//		}
//		if (vKeyValue == TIMER_30MIN_PRESSED) {
//			genKeyTone();
//			if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
//				vFunctionIndex = Timer30mins;
//				selectTimeIndicatior(vFunctionIndex);
//			}
//
//		}
//		if (vKeyValue == TIMER_60MIN_PRESSED) {
//			genKeyTone();
//			if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
//				vFunctionIndex = Timer60mins;
//				selectTimeIndicatior(vFunctionIndex);
//			}
//		}
		checkRemoteTimerKey();
		if (vKeyValue == Pairing_code) {
			genKeyTone();
			if (!fIsTurnOffByException&&!uvParams.fIsUVFuncOn) {
				turnOffAllLightEffect();
				setPairingLedEffect();
				uvPairParams.fisPairing=TRUE;
				uvPairParams.vPairingTimeOutCnt=PAIRING_TIME_OUT_CONST;
			}
		}
		if (vKeyValue == Paired_code) {
			pairedResult(PASSED);
		}
		if (vKeyValue == Paired_fail) {
			pairedResult(FAILED);
		}

	}else{								//system is off
		if ((vKeyValue & 0xF0) != Pairing_code) {					//对码系列键不唤醒系统
			fIsSystemOff = FALSE;
			if(FALSE==checkRemoteTimerKey()){
				setPowerLedEffect();
				selectTimeIndicatior(vFunctionIndex);
				uvParams.fIsUVFuncOn = FALSE;
				UV_PowerOff;
				genKeyTone();
			}
		}
	}
	resetEntrySleepTime();
	vKeyValue = 0;
}

void	powerDataInit(void){
	adcThresholdGenerate();
	initLEDStyleParams();
	DDL_ZERO_STRUCT(uvPairParams);
	uvParams.fIsUVFuncOn=FALSE;
	uvParams.vUVTimeOutCnt=0;
}

void systemOffByManual(void){
	systemPowerDown();
}

void commandExcute(void){

}
void	addCheckToSendBuff(void){
	u8	vtCheckTemp=0,len=0,index=0;
	len=UART_ACK_BUF[0];
	for(;index<len-1;index++){
		vtCheckTemp^=UART_ACK_BUF[index];
	}
	UART_ACK_BUF[len-1]=vtCheckTemp;
}



