/*
 * user_lightEffect.h
 *
 *  Created on: 2019年10月23日
 *      Author: Bough_004
 */

#ifndef SOURCE_INC_USER_LIGHTEFFECT_H_
#define SOURCE_INC_USER_LIGHTEFFECT_H_
#include	"const.h"
extern	LEDParametersStruct	PwLedStruct;
extern	LEDParametersStruct	*pPwLedStruct;

extern	LEDParametersStruct	Timer15mLedStruct;
extern	LEDParametersStruct	*p15mLedStruct;

extern	LEDParametersStruct	Timer30mLedStruct;
extern	LEDParametersStruct	*p30mLedStruct;

extern	LEDParametersStruct	Timer60mLedStruct;
extern	LEDParametersStruct	*p60mLedStruct;
extern	u8 	fIsLightEffectOn;		//是否开启光效模式

extern	void  	initLEDStyleParams(void);
extern	void 	lightEffectFunc(void);
extern	void 	turnOffAllLightEffect(void);
extern	void	 	setPowerLedEffect(void);
extern	void	 	setTimer15mLedEffect(void);
extern	void	 	setTimer30mLedEffect(void);
extern	void	 	setTimer60mLedEffect(void);
extern	void	 	setVoltErrorLed(void);
extern	void	 	setHotLed(void);
extern	void	 	setPairingLedEffect(void);
#endif /* SOURCE_INC_USER_LIGHTEFFECT_H_ */
