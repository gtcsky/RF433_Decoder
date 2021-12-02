/*
 * user_menu.h
 *
 *  Created on: 2019年8月15日
 *      Author: Bough_004
 */

#ifndef USER_INC_USER_MENU_H_
#define USER_INC_USER_MENU_H_
#include "const.h"

extern	UserPwmInitTypeDef  userPwmParaStruct;
extern	UserADCTypeDef	userAdcStruct;
extern	u8 fIsMotorStartup;
extern	float vTemperatureCoe;
extern	u8	vLightEfftectVoltDectCnt;
extern	u8	fIsSystemTempGot;
extern	u8 	fIsSystemInitialing;
extern	u8 	fIsSystemOff;
extern	u8	fIsNewCMDGod;
extern	u8 	fIsLightActive;
extern	u8	fTimerToPowerOnLED;
extern	u8	vPowerOnLEDCnt;
extern	u8	fIsCh3ForCW;		//0/1: chi3用于蓝色/冷光
//extern	u32 vSystemTemperature;
extern	u8	fIsUartReceiving;
extern	uVUSturctDef	uvParams;
extern	systemErrorEnum vSystemStts;
extern	uPairStructDef uvPairParams;
extern	U8	fIsTurnOffByException;
extern	U8	vBreakVoltDectCnt;
void 	pairedResult(TestStatus vtResult);
void		startUvFunc(void);
extern	void chkSystemResume(void);
extern	void MenuFunction(void );
extern	void checkBattFunc(void);
extern	float getBattVolt(void);
extern	void fucnPer5ms(void );
extern	void resetEntrySleepTime(void);
extern	void entryNormalModeChk(void);
extern	void powerOnIoInit(void);
extern	void	uartRXPortAsNormalIoInput(void);
extern	void	powerDataInit(void);
extern	void systemOffByManual(void);
extern	void checkRealEntryPowerDownMode(void);
extern	void	 setBlueOutputLow(void);
extern	void	 setCoolOutputLow(void);
void 	colorTemperatureAdjustSlowFunc(void);
void 	commandExcute(void);
void 	turnOffAllLightEffect(void);
void		addCheckToSendBuff(void);
void 	chkLightEffectModeVoltCompensation(float *volt);
#endif /* USER_INC_USER_MENU_H_ */
