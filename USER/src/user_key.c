/*
 * user_key.c
 *
 *  Created on: 2019-08-15
 *      Author: Bough_004
 */
#include "user_key.h"
#include "user_menu.h"
#include "user_lptimer.h"
#include "io_define.h"
#include "communication.h"
//#include "user_led.h"
//#include "main.h"

extern	u16 vSystemLIRC5ms;
u8	vKeyValue;
u8 	vIsKeyPressed=0;
u8 	vIsFuncKeyGod;
u8 	vIsClosedKeyGod;
u8	vDoubleClickCountDown;
u16		vFuncKeyTimer;

u8 	vIsPowerKeyGod;
u16	vPowerKeyTimer;

u16	vTimerKeyTimer;
u8 	vIsTimerKeyGod;


void	 funcPowerKeyReleased(void){
	clrPowerKeyPressed;
	vPowerKeyTimer=0;
	vIsPowerKeyGod&=~(POWER_KEY_SHOT_PRRESS_GOD|POWER_KEY_LONG_PRRESS_GOD);
}
void  funcTimerKeyReleased(void){
	clrTimerKeyPressed;
	vTimerKeyTimer=0;
	vIsTimerKeyGod&=~(TIMER_KEY_SHOT_PRRESS_GOD|TIMER_KEY_LONG_PRRESS_GOD);
}


void funcKeyTask(void) {

	// power Key 释放
	if (checkPowerKeyPressed && GET_POWER_KEY_PIN_STTS ){
		if((vIsPowerKeyGod&POWER_KEY_SHOT_PRRESS_GOD)&&!(vIsPowerKeyGod&POWER_KEY_LONG_PRRESS_GOD)){
			//vKeyValue = POWER_KEY_SHORT_PRESSED;
			vKeyValue = FUNC_KEY_SHORT_PRESSED;								//power key短按功能变成function功能
		}
		funcPowerKeyReleased();
	}
	// Inc Key 释放
	if (checkTimerKeyPressed && GET_TIMER_KEY_PIN_STTS ){
		if((vIsTimerKeyGod&TIMER_KEY_SHOT_PRRESS_GOD)&&!(vIsTimerKeyGod&TIMER_KEY_LONG_PRRESS_GOD)){
			vKeyValue = TIMER_KEY_SHORT_PRESSED;
		}
		funcTimerKeyReleased();
	}

	// power Key 检测
	if(!GET_POWER_KEY_PIN_STTS){
		if (checkPowerKeyPressed ) {
			if (!(vIsPowerKeyGod&POWER_KEY_SHOT_PRRESS_GOD)) {	
				if (((vPowerKeyTimer+vSystemLIRC5ms)&0xffff) > SHORT_PRESSED_TIME) {
					vIsPowerKeyGod|=POWER_KEY_SHOT_PRRESS_GOD;
					//vKeyValue = POWER_KEY_SHORT_PRESSED;
				}
			} else {
				if (!(vIsPowerKeyGod&POWER_KEY_LONG_PRRESS_GOD)) {
					if (((vPowerKeyTimer+vSystemLIRC5ms)&0xffff) > LONG_PRESSED_2S) {
						vKeyValue = POWER_KEY_LONG_PRESSED;
						vIsPowerKeyGod|=POWER_KEY_LONG_PRRESS_GOD;
						vPowerKeyTimer = 0;	//stop cnt
					}
				}
			}
		}else{
			setPowerKeyPressedFlag();
		}
	}


	// Inc Key 检测
	if(!GET_TIMER_KEY_PIN_STTS){
		if (checkTimerKeyPressed ) {
			if (!(vIsTimerKeyGod&TIMER_KEY_SHOT_PRRESS_GOD)) {
				if (((vTimerKeyTimer+vSystemLIRC5ms)&0xffff) > SHORT_PRESSED_TIME) {
					vIsTimerKeyGod|=TIMER_KEY_SHOT_PRRESS_GOD;
					//vKeyValue = TIMER_KEY_SHORT_PRESSED;
				}
			} else {
				if (!(vIsTimerKeyGod&TIMER_KEY_LONG_PRRESS_GOD)) {
					if (((vTimerKeyTimer+vSystemLIRC5ms)&0xffff) > LONG_PRESSED_3S) {
						//vKeyValue = TIMER_KEY_LONG_PRESSED;
						vKeyValue = Pairing_code;
						vIsTimerKeyGod|=TIMER_KEY_LONG_PRRESS_GOD;
						vTimerKeyTimer = 0;	//stop cnt
					}
				}
			}
		}else{
			setTimerKeyPressedFlag();
		}

	}
}



void setPowerKeyPressedFlag(void) {
//	funcPowerKeyReleased();
	vPowerKeyTimer = 0x10000 - vSystemLIRC5ms;
	vIsKeyPressed |= Power_KEY_PRESSED;
}
void setTimerKeyPressedFlag(void) {
	funcTimerKeyReleased();
	vTimerKeyTimer = 0x10000 - vSystemLIRC5ms;
	vIsKeyPressed |= Timer_KEY_PRESSED;
}

//void holdingKeyFunc(void) {
//	if (vIsTimerKeyGod&TIMER_KEY_LONG_PRRESS_GOD) {
//		vKeyValue = TIMER_KEY_SHORT_PRESSED;					//长按时每0.05秒触发一个按键
//	}
//	if (vIsDecKeyGod&DEC_KEY_LONG_PRRESS_GOD) {
//		vKeyValue = DEC_KEY_SHORT_PRESSED;					//长按时每0.05秒触发一个按键
//	}
//	if (vIsBrightnessUpKeyGod&BRIGHTNESS_UP_KEY_LONG_PRRESS_GOD) {
//		vKeyValue = BRIGHTNESS_UP_KEY_SHORT_PRESSED;		//长按时每0.05秒触发一个按键
//	}
//	if (vIsBrightnessDownKeyGod&BRIGHTNESS_DOWN_KEY_LONG_PRRESS_GOD) {
//		vKeyValue = BRIGHTNESS_DOWN_KEY_SHORT_PRESSED;		//长按时每0.05秒触发一个按键
//	}
//}
