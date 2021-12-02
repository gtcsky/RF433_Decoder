/*
 * io_define.h
 *
 *  Created on: 2019年8月13日
 *      Author: Bough_004
 */

#ifndef USER_INC_IO_DEFINE_H_
#define USER_INC_IO_DEFINE_H_
#include "const.h"
#include "user_menu.h"

#define 	PowerLED_PORT				GPIOC
#define 	PowerLED_PIN				GPIO_Pin_6
#define	setPowerLed					GPIO_SetBits(PowerLED_PORT, PowerLED_PIN)
#define	clrPowerLed					GPIO_ResetBits(PowerLED_PORT, PowerLED_PIN)


#define 	TimerLED_15m_PORT			GPIOC
#define 	TimerLED_15m_PIN			GPIO_Pin_5
#define	setTimer15mLed				GPIO_SetBits(TimerLED_15m_PORT, TimerLED_15m_PIN)
#define	clrTimer15mLed				GPIO_ResetBits(TimerLED_15m_PORT, TimerLED_15m_PIN)

#define 	TimerLED_30m_PORT			GPIOC
#define 	TimerLED_30m_PIN			GPIO_Pin_4
#define	setTimer30mLed				GPIO_SetBits(TimerLED_30m_PORT, TimerLED_30m_PIN)
#define	clrTimer30mLed				GPIO_ResetBits(TimerLED_30m_PORT, TimerLED_30m_PIN)

#define 	TimerLED_60m_PORT			GPIOC
#define 	TimerLED_60m_PIN			GPIO_Pin_3
#define	setTimer60mLed				GPIO_SetBits(TimerLED_60m_PORT, TimerLED_60m_PIN)
#define	clrTimer60mLed				GPIO_ResetBits(TimerLED_60m_PORT, TimerLED_60m_PIN)


#define	P_UV_Power_PORT			GPIOD
#define	P_UV_Power_PIN				GPIO_Pin_4
#define	UV_PowerOn					GPIO_ResetBits(P_UV_Power_PORT, P_UV_Power_PIN)
#define	UV_PowerOff					GPIO_SetBits(P_UV_Power_PORT, P_UV_Power_PIN)
#define	IsUVPowerON				(GPIO_ReadOutputDataBit(P_UV_Power_PORT,P_UV_Power_PIN)==FALSE)


#define	ADC_VOLT_CHL				ADC_Channel5_ENABLE
#define	Volt_Port					GPIOD
#define	Volt_Pin						GPIO_Pin_5

#define	ADC_TEMP_CHL				ADC_Channel6_ENABLE
#define 	Temperture_Port				GPIOD
#define 	Temperture_Pin				GPIO_Pin_6

#define	KeyPower_Port				GPIOD
#define	KeyPower_Pin				GPIO_Pin_3
#define 	Power_KEY_PRESSED   			0x08
#define	checkPowerKeyPressed		(vIsKeyPressed&Power_KEY_PRESSED)
#define	clrPowerKeyPressed			vIsKeyPressed&=~Power_KEY_PRESSED//0xFD
#define	setPowerKeyPressed			vIsKeyPressed|=Power_KEY_PRESSED
#define	GET_POWER_KEY_PIN_STTS	GPIO_ReadInputDataBit(KeyPower_Port, KeyPower_Pin)

#define	KeyTimer_Port				GPIOD
#define	KeyTimer_Pin					GPIO_Pin_2
#define 	Timer_KEY_PRESSED   			0x04
#define	checkTimerKeyPressed		(vIsKeyPressed&Timer_KEY_PRESSED)
#define	clrTimerKeyPressed			vIsKeyPressed&=~Timer_KEY_PRESSED//0xFD
#define	setTimerKeyPressed			vIsKeyPressed|=Timer_KEY_PRESSED
#define	GET_TIMER_KEY_PIN_STTS		GPIO_ReadInputDataBit(KeyTimer_Port, KeyTimer_Pin)

#define BUZZER_PORT					GPIOA
#define BUZZER_PIN					GPIO_Pin_3
#define BUZZER_CHANNEL			PWM_CH3N
#define BUZZER_DUTY_INDEX			0X03

//#define	CommunPort					GPIOB
//#define	CommunPin					GPIO_Pin_5
//#define	Get_Comm_Int_Stts				GPIO_ReadInputDataBit(CommunPort, CommunPin)
#define	CommunPort					GPIOB
#define	CommunPin					GPIO_Pin_4
#define	Get_Comm_Int_Stts			GPIO_ReadInputDataBit(CommunPort, CommunPin)

//#define	DebugPinPort				GPIOB
//#define	DebugPinPin					GPIO_Pin_4
//#define	set_Debug_Pin				GPIO_SetBits(DebugPinPort, DebugPinPin)
//#define	clr_Debug_Pin				GPIO_ResetBits(DebugPinPort, DebugPinPin)
//#define	getDebugPinStts				GPIO_ReadOutputDataBit(DebugPinPort,DebugPinPin)
#define	DebugPinPort				GPIOB
#define	DebugPinPin					GPIO_Pin_5
#define	set_Debug_Pin				GPIO_SetBits(DebugPinPort, DebugPinPin)
#define	clr_Debug_Pin				GPIO_ResetBits(DebugPinPort, DebugPinPin)
#define	getDebugPinStts				GPIO_ReadOutputDataBit(DebugPinPort,DebugPinPin)
#endif /* USER_INC_IO_DEFINE_H_ */
