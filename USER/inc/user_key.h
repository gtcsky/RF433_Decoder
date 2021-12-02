/*
 * user_key.h
 *
 *  Created on: 2019年8月15日
 *      Author: Bough_004
 */

#ifndef USER_INC_USER_KEY_H_
#define USER_INC_USER_KEY_H_
#include "const.h"
#include "user_exti.h"
#include "cx32l003_gpio.h"

#define FUNC_KEY_SHORT_PRESSED    	0x51
#define FUNC_KEY_LONG_PRESSED    	0x52
#define FUNC_KEY_DOUBLE_CLICK    	0x53

#define POWER_KEY_SHORT_PRESSED    	0x01
#define POWER_KEY_LONG_PRESSED    	0x02

#define TIMER_KEY_SHORT_PRESSED    	0x11
#define TIMER_KEY_LONG_PRESSED    	0x12

#define	TIMER_15MIN_PRESSED		0x21
#define	TIMER_30MIN_PRESSED		0x22
#define	TIMER_60MIN_PRESSED		0x23


#define SHORT_PRESSED_TIME   	2  		//4*5ms=20ms
#define LONG_PRESSED_0S3     		60		//60*5=300ms
#define LONG_PRESSED_0S5     		100		//100*5=500ms
#define LONG_PRESSED_1S			200		//200*5ms=1s
#define LONG_PRESSED_2S			400		//400*5ms=2s
#define LONG_PRESSED_3S			600		//600*5ms=3s
#define LONG_PRESSED_4S			800		//800*5ms=4s
#define LONG_PRESSED_5S			1000	//1000*5ms=5s

#define DOUBLE_CLICK_CONST					100;   		//100*5ms  在第一次按键释放候,倒计时500ms以内,如果右第二次按键产生,就当成是双击
extern	u8	vKeyValue;
extern	u8 	vIsKeyPressed;
extern	u8 	vIsFuncKeyGod;
extern	u8	vDoubleClickCountDown;
extern	u16	vFuncKeyTimer;

extern	u8 	vIsPowerKeyGod;
extern	u16	vPowerKeyTimer;

extern	u8 	vIsIncKeyGod;
extern	u16	vIncKeyTimer;

#define	FUNC_KEY_SHOT_PRRESS_GOD		0X01
#define	FUNC_KEY_LONG_PRRESS_GOD		0X02
#define	POWER_KEY_SHOT_PRRESS_GOD	0X01
#define	POWER_KEY_LONG_PRRESS_GOD	0X02

#define	TIMER_KEY_SHOT_PRRESS_GOD		0X01
#define	TIMER_KEY_LONG_PRRESS_GOD	0X02



extern	void funcKeyTask(void);
extern	void keyDoubleClickChk(void);
extern	void setPowerKeyPressedFlag(void);
extern	void closedReleasedFunc(void);
extern	void setTimerKeyPressedFlag(void);
#endif /* USER_INC_USER_KEY_H_ */
