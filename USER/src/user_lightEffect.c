/*
 * user_lightEffect.c
 *
 *  Created on: 2019年10月23日
 *      Author: Bough_004
 */

#include "user_lightEffect.h"
#include "io_define.h"
#include "user_color.h"
#include "user_lptimer.h"
#include "user_menu.h"
#include "user_key.h"
#include "user_exti.h"
#include "user_adc.h"
#include "user_advtime.h"
#include "user_color.h"
#include "user_ddl.h"
#include "user_tone.h"
//#include "string.h"
u8 	fIsLightEffectOn=0;					//是否开启光效模式
LEDParametersStruct	PwLedStruct;
LEDParametersStruct	*pPwLedStruct=&PwLedStruct;

LEDParametersStruct	Timer15mLedStruct;
LEDParametersStruct	*p15mLedStruct=&Timer15mLedStruct;

LEDParametersStruct	Timer30mLedStruct;
LEDParametersStruct	*p30mLedStruct=&Timer30mLedStruct;

LEDParametersStruct	Timer60mLedStruct;
LEDParametersStruct	*p60mLedStruct=&Timer60mLedStruct;

#define		MAX_POWER_LED_INDEX	1
const u8 		flashPowerLedTimerArray[MAX_POWER_LED_INDEX+1]={50,150};
const u8  	flashPowerLedSttsArray[MAX_POWER_LED_INDEX+1]={  1,0};

#define		MAX_15MIN_LED_INDEX	1
const u8 		flash15mLedTimerArray[MAX_15MIN_LED_INDEX+1]={50,150};
const u8  	flash15mLedSttsArray[MAX_15MIN_LED_INDEX+1]={  1,0};

#define		MAX_30MIN_LED_INDEX	1
const u8 		flash30mLedTimerArray[MAX_30MIN_LED_INDEX+1]={50,150};
const u8  	flash30mLedSttsArray[MAX_30MIN_LED_INDEX+1]={  1,0};

#define		MAX_60MIN_LED_INDEX	1
const u8 		flash60mLedTimerArray[MAX_60MIN_LED_INDEX+1]={50,150};
const u8  	flash60mLedSttsArray[MAX_60MIN_LED_INDEX+1]={  1,0};

#define		MAX_VOLT_ERROR_LED_INDEX	3
const u8 		voltErrorLedTimerArray[MAX_VOLT_ERROR_LED_INDEX+1]={50,50,250,250};
const u8  	voltErrorLedSttsArray[MAX_VOLT_ERROR_LED_INDEX+1]={  0,1,0,0};

#define		MAX_TEMP_ERROR_LED_INDEX	2
const u8 		temperatureErrorLedTimerArray[MAX_TEMP_ERROR_LED_INDEX+1]={50,50,100};
const u8  	temperatureErrorLedSttsArray[MAX_TEMP_ERROR_LED_INDEX+1]={  0,1,0};

#define		MAX_PAIRING_LED_INDEX  1
const u8 		pairingLedTimerArray[MAX_PAIRING_LED_INDEX+1]={30,10};
const u8  	pairingLedSttsArray[MAX_PAIRING_LED_INDEX+1]={  0,1};


void  initLEDStyleParams(void){

	DDL_ZERO_STRUCT(PwLedStruct);
	DDL_ZERO_STRUCT(Timer15mLedStruct);
	DDL_ZERO_STRUCT(Timer30mLedStruct);
	DDL_ZERO_STRUCT(Timer60mLedStruct);

}

void setLEDFunc(LEDParametersStruct * ledStruct){
	UINT8 vtCurLED;
	ledStruct->vLEDStepCtrlTimeCnt=*(ledStruct->timeArray+ledStruct->currentIndex);
	vtCurLED=*(ledStruct->sttsArray+ledStruct->currentIndex);
	if (!vtCurLED)
		ledStruct->pfnOffCallBack();
	else
		ledStruct->pfnOnCallBack();
}


void lightEffectProcess(LEDParametersStruct * ledStruct){
	if (ledStruct->currentEffectOn) {
		if (ledStruct->vLEDStepCtrlTimeCnt == 0) {	//Flash Lamp function executing
			if (ledStruct->currentIndex >=ledStruct->indicatorMaxIndex) {
				ledStruct->currentIndex = 0;
			} else {
				ledStruct->currentIndex++;
			}
			setLEDFunc(ledStruct);
		} else {
			ledStruct->vLEDStepCtrlTimeCnt--;
		}
	}
}

void lightEffectFunc(void) {
	if(fIsLightEffectOn){
		lightEffectProcess(pPwLedStruct);
		lightEffectProcess(p15mLedStruct);
		lightEffectProcess(p30mLedStruct);
		lightEffectProcess(p60mLedStruct);
	}
}

void turnOffAllLightEffect(void) {
	fIsLightEffectOn = 0;
	clrTimer15mLed;
	clrTimer30mLed;
	clrTimer60mLed;
	clrPowerLed;
	initLEDStyleParams();
}
/*********************************************************************
 *
 * 	闪烁模式
 *
 **********************************************************************/
void setFlashEffectPub(LEDParametersStruct * ledStruct){
	fIsLightEffectOn = 1;
	ledStruct->currentIndex=0;
	ledStruct->currentEffectOn=ON;
	ledStruct->currentIndex=0;
	setLEDFunc(ledStruct);
}

void offPowerLedCb(void){
	clrPowerLed;
}
void onPowerLedCb(void){
	setPowerLed;
}
void off15mLedCb(void){
	clrTimer15mLed;
}
void on15mLedCb(void){
	setTimer15mLed;
}
void off30mLedCb(void){
	clrTimer30mLed;
}
void on30mLedCb(void){
	setTimer30mLed;
}
void off60mLedCb(void){
	clrTimer60mLed;
}
void on60mLedCb(void){
	setTimer60mLed;
}

/*********************************************************************
 * 	power led 闪烁模式
 **********************************************************************/
void	 setPowerLedEffect(void){
	pPwLedStruct->indicatorMaxIndex=MAX_POWER_LED_INDEX;
	pPwLedStruct->timeArray=flashPowerLedTimerArray;
	pPwLedStruct->sttsArray=flashPowerLedSttsArray;
	pPwLedStruct->pfnOffCallBack=offPowerLedCb;
	pPwLedStruct->pfnOnCallBack=onPowerLedCb;
	setFlashEffectPub(pPwLedStruct);
}
/*********************************************************************
 * 	对码指示灯模式
 **********************************************************************/
void	 setPairingLedEffect(void){
	pPwLedStruct->indicatorMaxIndex=MAX_PAIRING_LED_INDEX;
	pPwLedStruct->timeArray=pairingLedTimerArray;
	pPwLedStruct->sttsArray=pairingLedSttsArray;
	pPwLedStruct->pfnOffCallBack=offPowerLedCb;
	pPwLedStruct->pfnOnCallBack=onPowerLedCb;
	setFlashEffectPub(pPwLedStruct);
}
/*********************************************************************
 * 	15min  led 指示闪烁模式
 **********************************************************************/
void	 setTimer15mLedEffect(void){
	Timer60mLedStruct.currentEffectOn=OFF;
	clrTimer60mLed;
	Timer30mLedStruct.currentEffectOn=OFF;
	clrTimer30mLed;
	setPowerLedEffect();
	p15mLedStruct->indicatorMaxIndex=MAX_15MIN_LED_INDEX;
	p15mLedStruct->timeArray=flash15mLedTimerArray;
	p15mLedStruct->sttsArray=flash15mLedSttsArray;
	p15mLedStruct->pfnOffCallBack=off15mLedCb;
	p15mLedStruct->pfnOnCallBack=on15mLedCb;
	setFlashEffectPub(p15mLedStruct);
}
/*********************************************************************
 * 	30min  led 闪烁模式
 **********************************************************************/
void	 setTimer30mLedEffect(void){
	Timer60mLedStruct.currentEffectOn=OFF;
	clrTimer60mLed;
	Timer15mLedStruct.currentEffectOn=OFF;
	clrTimer15mLed;
	setPowerLedEffect();
	p30mLedStruct->indicatorMaxIndex=MAX_30MIN_LED_INDEX;
	p30mLedStruct->timeArray=flash30mLedTimerArray;
	p30mLedStruct->sttsArray=flash30mLedSttsArray;
	p30mLedStruct->pfnOffCallBack=off30mLedCb;
	p30mLedStruct->pfnOnCallBack=on30mLedCb;
	setFlashEffectPub(p30mLedStruct);
}
/*********************************************************************
 * 	60min  led 闪烁模式
 **********************************************************************/
void	 setTimer60mLedEffect(void){
	Timer15mLedStruct.currentEffectOn=OFF;
	clrTimer15mLed;
	Timer30mLedStruct.currentEffectOn=OFF;
	clrTimer30mLed;
	setPowerLedEffect();
	p60mLedStruct->indicatorMaxIndex=MAX_60MIN_LED_INDEX;
	p60mLedStruct->timeArray=flash60mLedTimerArray;
	p60mLedStruct->sttsArray=flash60mLedSttsArray;
	p60mLedStruct->pfnOffCallBack=off60mLedCb;
	p60mLedStruct->pfnOnCallBack=on60mLedCb;
	setFlashEffectPub(p60mLedStruct);
}


void	 allLedEffectModeCb(void){
//	pPwLedStruct->pfnOnCallBack=onPowerLedCb;
	onPowerLedCb();
	genErrorTone();
}


void	syncAllLedEffect(u8 maxIndex,const UINT8 * timeArray,const UINT8 * sttsArray){

	pPwLedStruct->indicatorMaxIndex=maxIndex;
	pPwLedStruct->timeArray=timeArray;
	pPwLedStruct->sttsArray=sttsArray;
	pPwLedStruct->pfnOffCallBack=offPowerLedCb;
//	pPwLedStruct->pfnOnCallBack=onPowerLedCb;
	pPwLedStruct->pfnOnCallBack=allLedEffectModeCb;
	setFlashEffectPub(pPwLedStruct);

	p60mLedStruct->indicatorMaxIndex=maxIndex;
	p60mLedStruct->timeArray=timeArray;
	p60mLedStruct->sttsArray=sttsArray;
	p60mLedStruct->pfnOffCallBack=off60mLedCb;
	p60mLedStruct->pfnOnCallBack=on60mLedCb;
	setFlashEffectPub(p60mLedStruct);

	p30mLedStruct->indicatorMaxIndex=maxIndex;
	p30mLedStruct->timeArray=timeArray;
	p30mLedStruct->sttsArray=sttsArray;
	p30mLedStruct->pfnOffCallBack=off30mLedCb;
	p30mLedStruct->pfnOnCallBack=on30mLedCb;
	setFlashEffectPub(p30mLedStruct);

	p15mLedStruct->indicatorMaxIndex=maxIndex;
	p15mLedStruct->timeArray=timeArray;
	p15mLedStruct->sttsArray=sttsArray;
	p15mLedStruct->pfnOffCallBack=off15mLedCb;
	p15mLedStruct->pfnOnCallBack=on15mLedCb;
	setFlashEffectPub(p15mLedStruct);

}

void	 setVoltErrorLed(void){
	syncAllLedEffect(MAX_VOLT_ERROR_LED_INDEX,voltErrorLedTimerArray,voltErrorLedSttsArray);
}

void	 setHotLed(void){

	syncAllLedEffect(MAX_TEMP_ERROR_LED_INDEX,temperatureErrorLedTimerArray,temperatureErrorLedSttsArray);
}
