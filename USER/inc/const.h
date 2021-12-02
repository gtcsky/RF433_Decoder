/*
 * const.h
 *
 *  Created on: 2019年8月12日
 *      Author: Bough_004
 */

#ifndef USER_INC_CONST_H_
#define USER_INC_CONST_H_

typedef signed char 			i8;
typedef signed char 			I8;
typedef unsigned char 		u8;
typedef unsigned char 		U8;
typedef unsigned char 		UINT8;
typedef short	 				i16;
typedef short	 				I16;
typedef unsigned short 		u16;
typedef unsigned short 		U16;
typedef unsigned short 		UINT16;
typedef int 					i32;
typedef int 					I32;
typedef unsigned 				u32;
typedef unsigned 				U32;
typedef unsigned 				UINT32;
typedef long long 			i64;
typedef long long 			I64;
typedef unsigned long long 	u64;
typedef unsigned long long 	U64;
typedef unsigned long long 	UINT64;
#define TRUE        ((uint8_t) 1u)
#define FALSE       ((uint8_t) 0u)
typedef void         (*func_ptr_t)(void);




#define 	HIRC_24M_ADDR				0X180000C0
#define	HIRC_22M_ADDR				0X180000C2
#define	HIRC_16M_ADDR				0X180000C4
#define	HIRC_8M_ADDR				0X180000C6
#define	HIRC_4M_ADDR				0X180000C8
#define	LIRC_32K768_ADDR			0X180000D0
#define	LIRC_38K4_ADDR				0X180000D4

#define 	SYSTEM_VDD	3.3
#define	ADC_CONST			4096
#define 	vA2D_Coe			(ADC_CONST/SYSTEM_VDD)			//模数转换系数	2.0v*vA2D_Coe=2.0v对应的AD值
#define 	vD2A_Coe			(SYSTEM_VDD/ADC_CONST)			//数模转换系数	0x0136*vD2A_Coe=0x0136对应的电压
#define	SYSTEM_VCAP_VOLT	2.53

#define	SOFTWARE_VERSION				"SW:2020-02-14"
#define	SOFTWARE_VERSION_LENGTH		13
#define	HARDWARE_VERSION				"HW:VER07"
#define	HARDWARE_VERSION_LENGTH	8
#define	PROTOCOL_VERSION				"protocol V03"
#define	PROTOCOL_VERSION_LENGTH		12

#define	UNLOCK_RAM_CONST		0x55AA6699
#define	LOCK_RAM_CONST		0x55AA6698

#define	USER_DOG_CONST		1600				//1600*5ms=8s

#define	PWM_PERIOD_CONST			3000			//PWM frequency	24M/1200=20Khz
#define	PWM_FRQ_CONST			3000			//PWM frequency	24M/1200=20Khz

#define	BREAK_AD_DET_CONST				2

#define	MAX_LightEffect				1

#define	PAIRING_TIME_OUT_CONST	20//	500ms *n

#define	NORMAL_MODE_TIMEOUT				30*20			//60s
#define	POWER_DOWN_MODE_TIMEOUT		4				//4*50ms=200ms
//#define	POWER_DONW_LCD_TIMEOUT			60				//3S
#define	POWER_DONW_LCD_TIMEOUT			3				//350ms

#define	TIMER_15MIN		900			//900s
#define	TIMER_30MIN		1800		//1800s
#define	TIMER_60MIN		3600		//3600s
#define	STARTUP_TIMER		15			//15秒后启动
#define	MAX_FUNCTION_INDEX			Timer60mins

//NTC=47K  上拉47K
//#define TEMPERATURE_50C		1081
//#define TEMPERATURE_50C_VOLT	1320	//1.320V
//#define TEMPERATURE_55C		937
//#define TEMPERATURE_55C_VOLT	1144	//1.144V
//#define TEMPERATURE_60C		810
//#define TEMPERATURE_60C_VOLT	989		//0.989V
//#define TEMPERATURE_65C		699
//#define TEMPERATURE_65C_VOLT	854		//0.854V
//#define TEMPERATURE_66C		679
//#define TEMPERATURE_66C_VOLT	823		//0.823V
//#define TEMPERATURE_67C		659
//#define TEMPERATURE_67C_VOLT	805		//0.805V
//#define TEMPERATURE_68C		639
//#define TEMPERATURE_68C_VOLT	781		//0.781V
//#define TEMPERATURE_69C		621
//#define TEMPERATURE_69C_VOLT	754		//0.754V
//#define TEMPERATURE_70C		603
//#define TEMPERATURE_70C_VOLT	726		//0.726V
//#define TEMPERATURE_71C		585
//#define TEMPERATURE_71C_VOLT	715		//0.715V
//#define TEMPERATURE_72C		568
//#define TEMPERATURE_72C_VOLT	694		//0.694V
//#define TEMPERATURE_73C		551
//#define TEMPERATURE_73C_VOLT	673		//0.673V
//#define TEMPERATURE_74C		535
//#define TEMPERATURE_74C_VOLT	654		//0.654V
//#define TEMPERATURE_75C		519
//#define TEMPERATURE_75C_VOLT	635		//0.635V
//#define TEMPERATURE_76C		504
//#define TEMPERATURE_76C_VOLT	616		//0.616V
//#define TEMPERATURE_77C		489
//#define TEMPERATURE_77C_VOLT	598		//0.598V
//#define TEMPERATURE_78C		475
//#define TEMPERATURE_78C_VOLT	580		//0.580V
//#define TEMPERATURE_79C		461
//#define TEMPERATURE_79C_VOLT	563		//0.563V
//#define TEMPERATURE_80C		448
//#define TEMPERATURE_80C_VOLT	547		//0.547V
//NTC=470K  上拉分压=100K		分压源=VCAP
#define TEMPERATURE_35C_VOLT	1.857	//1.857V
#define TEMPERATURE_40C_VOLT	1.740	//1.740V
#define TEMPERATURE_45C_VOLT	1.614	//1.614V
#define TEMPERATURE_50C_VOLT	1.484	//1.484V
#define TEMPERATURE_55C_VOLT	1.348	//1.348V
#define TEMPERATURE_60C_VOLT	1.218	//1.218V
#define TEMPERATURE_65C_VOLT	1.088	//1.088V
#define TEMPERATURE_70C_VOLT	0.970	//0.970V
#define TEMPERATURE_75C_VOLT	0.859	//0.859V
#define TEMPERATURE_80C_VOLT	0.753	//0.753V
#define 	OVER_TEMPERATURE_VOLT_Lv1	TEMPERATURE_70C_VOLT//TEMPERATURE_40C_VOLT//80
#define 	OVER_TEMPERATURE_VOLT_Lv0	TEMPERATURE_65C_VOLT//TEMPERATURE_35C_VOLT//70
#define 	NORMAL_TEMPERATURE_VOLT		TEMPERATURE_60C_VOLT//TEMPERATURE_30C_VOLT//60
//#define VOLT_AC240V			3300		//240*1.414*0.971%			240*1.414=AC->DC   .    *0.971%= 10k/1030k分压=3.30V即3300mV
//#define VOLT_AC185V			2540		//185*1.414*0.971%			185*1.414=AC->DC   .    *0.971%= 10k/1030k分压=2.54V即2540mV
//#define VOLT_AC150V			2060		//150*1.414*0.971%			150*1.414=AC->DC   .    *0.971%= 10k/1030k分压=2.06V即2060mV
//#define VOLT_AC160V			2197		//160*1.414*0.971%			160*1.414=AC->DC   .    *0.971%= 10k/1030k分压=2.19V即2190mV
#define VOLT_AC240V			3000		//240*1.414*0.884%			240*1.414=AC->DC   .    *0.884%= 9.1k/1029.1.k分压=3.00V即3000mV
#define VOLT_AC185V			2313		//185*1.414*0.884%			185*1.414=AC->DC   .    *0.884%= 10k/510k分压=2.313V即2313mV
#define VOLT_AC160V			2000		//160*1.414*0.884%			160*1.414=AC->DC   .    *0.884%= 10k/510k分压=2.00V即2000mV


#define	TONE_DUTY	0.3

//typedef enum{
//	ConfirmTone=0,
//	EndTone=1,
//	KeyTone=2,
//	ErrorTone=3
//}toneIdEnum;




typedef enum{
	Timer15mins=0,
	Timer30mins=1,
	Timer60mins=2
}functionOffEnum;


typedef enum{
	OFF=0,
	ON=1
}lightSttsEnum;

typedef struct{
//	toneIdEnum 	toneID;
	u8	toneProcessIndex;
	u8	toneMaxIndex;
	u8 	tongProcessCnt;
	lightSttsEnum 	tongStts;
	const 	UINT8 *	timeArray;
	const	UINT8 *	sttsArray;
	func_ptr_t  pfnToneFuncCallBack;
}voiceParamStruct;

typedef enum{
	IdleIamgeDisplay=0,
	ModeTDisplay=1,
	CountDownDisplay=2,
	ChargingAtPowerDown=3
}displayModeEnum;

typedef enum{
	HuesSetting=0,
	SaturationSetting=1,
	BrightnessSetting=2,
	ColorTempSetting=3,
	PreinstallEffect=4,
	CustomizeEffect=5
}settingIndexEnum;

typedef enum{
	DefaultChannelON=0x0000,
	LeftChannelOn=0x8000,
	RightChannelOn=0x4000,
	LeftRightChannelOn=0xC000
}rgbPowerChannelEnum;

typedef enum{
	ReadStatus=0,
	ReadHSB=1,
	ReadBrightness=2,
	ReadColorTemperature=3,
	ReadPreinstallEffectNo=4,
	ReadCustomizeEffectInfo=5,
	ReadTemperature=6,
	ReadSwVersion=16,
	ReadHwVersion=17,
	ReadProtocolVersion=18
}uartReadingType;




typedef struct{
	UINT8	indicatorMaxIndex;
	UINT8	currentIndex;
	const 	UINT8 *	timeArray;
	const	UINT8 *	sttsArray;
	func_ptr_t  pfnOffCallBack;					//OFF状态回调
	func_ptr_t  pfnOnCallBack;					//ONf状态回调
	lightSttsEnum	 currentEffectOn;				//当前灯光效果是否开启
	u8		vLEDStepCtrlTimeCnt;
}LEDParametersStruct;

typedef enum{
	HIRC_24M=0,
	HIRC_22M=1,
	HIRC_16M=2,
	HIRC_8M=3,
	HIRC_4M=4
}SystemHIRCType;
typedef enum{
	LIRC_32K768=0,
	LIRC_38K4=1
}SystemLIRCType;

typedef enum{
	HIRC_SEL=1,
	HXT_SEL=2,
	LIRC_SEL=4,
	LXT_SEL=8
}SystemClkSelectType;

typedef enum{
	EXT_PORTA=1,
	EXT_PORTB=2,
	EXT_PORTC=4,
	EXT_PORTD=8
}ExtIntPortType;

typedef enum{
	PWM_CH1=1,
	PWM_CH2=2,
	PWM_CH3=4,
	PWM_CH4=8,
	PWM_CH1N=0X10,
	PWM_CH2N=0X20,
	PWM_CH3N=0X40,
	PWM_CH4N=0X80
}PwmChlDefType;

typedef enum{
	ADC_CH0=0,
	ADC_CH1=1,
	ADC_CH2=2,
	ADC_CH3=3,
	ADC_CH4=4,
	ADC_CH5=5,
	ADC_CH6=6,
	ADC_CH7=7
}ADCChlDefType;


typedef struct{
	UINT8 	length;
	UINT16 	flag;
	UINT8 	cmd;
	UINT8	preinstallEffectNo;
	UINT8	brightness;
	UINT8	colorTemperature;
	UINT16	hues;
	UINT8	saturation;
	UINT8	customizeEffectMode;
	UINT8	customizeEffectTimes;
	UINT8	customizeEffectFreq;
	UINT8	fIsMasterWrite;					//	0/1主控读取/写入命令
//	UINT8	checksum;
}UARTCommandStruct;

typedef enum{
	GradualMode=1,
	FlashMode=2
}customizeEffectModeType;

typedef enum{
	INCLUDE_CMD=1,
	INCLUDE_MODE=2,
	INCLUDE_BRIGHTNESS=4,
	INCLUDE_COLOR_TEMPERTURE=8,
	INCLUDE_HUES=0X10,
	INCLUDE_SATURATION=0X20,
	INCLUDE_CUSTOMIZE_EFFECT_MODE=0X40,
	INCLUDE_CUSTOMIZE_EFFECT_TIMES=0X80,
	INCLUDE_CUSTOMIZE_EFFECT_FREQ=0X100
}uartCommandDefType;
typedef enum{
	BIT_CMD=0,
	BIT_MODE=1,
	BIT_BRIGHTNESS=2,
	BIT_COLOR_TEMPERTURE=3,
	BIT_HUES=4,
	BIT_SATURATION=5,
	BIT_CUSTOMIZE_EFFECT_MODE=6,
	BIT_CUSTOMIZE_EFFECT_TIMES=7,
	BIT_CUSTOMIZE_EFFECT_FREQ=8
}uartCommandBitDefType;

typedef enum{
	OFF_CMD=0,
	ON_CMD=1,
	PREINSTALL_EFFECT=2,
	CUSTOMIZE_EFFECT=3,
}payloadCMDType;
typedef enum{
	NORMAL_LIGHT_MODE=0
}payloadModeType;

typedef enum
{
	FAILED = 0,
	PASSED = !FAILED
} TestStatus;


//typedef struct
//{
//  u16 period;				//PWM频率=系统频率/(vPWMPeriod+1);
//  u8 channels;				//channel可以是	BUZZER_CHANNEL|MOTOR_CHANNEL|DISCHARGE_CHANNEL|CHARGE_CHANNEL以及他们的子集
//  float buzzerDuty;
//  float motorDuty;
//  float chargeDuty;
//  float dischargeDuty;
//} UserPwmInitTypeDef;
typedef struct
{
  u16 period;					//PWM频率=系统频率/(vPWMPeriod+1);
  u8 channels;					//channel可以是	BUZZER_CHANNEL|MOTOR_CHANNEL|DISCHARGE_CHANNEL|CHARGE_CHANNEL以及他们的子集
  float dutyArray[5];			//dutyArray[0] 不存储,1~4存储对应的4个PWM channel的duty
} UserPwmInitTypeDef;

typedef struct{
	UINT16	vUVTimeOutCnt;
	U8		fIsUVFuncOn;
	U8		vTimeToTurnUV;
}uVUSturctDef;


typedef struct{
	U8		fisPairing;
	U8		vPairingTimeOutCnt;		//500ms*n
}uPairStructDef;

typedef struct
 {
	u8 channels;			//b0~b7分别对应AIN0~AIN7,对应位置1,则表示需要转换该通道
	u16 DaValues[8];
//	u16 DaValueAIN0;		//AIN0 转换结果的存储位置
//	u16 DaValueAIN1;
//	u16 DaValueAIN2;
//	u16 DaValueAIN3;
//	u16 DaValueAIN4;
//	u16 DaValueAIN5;
//	u16 DaValueAIN6;
//	u16 DaValueAIN7;
} UserADCTypeDef;

typedef	enum{
	FALLING=0,
	RISING=1
}extIntEdge;

typedef enum{
//	MCU_RESET =0,						//马达工作时有效
//	NTC_NORMAL=0,						//马达不工作时有效
	SystemOK=0,
//	ERROR_CURRENT =1,
	SystemHot=2,
	OVER_VOLTAGE=3,
	UNDER_VOLTAGE=4,
}systemErrorEnum;

//typedef struct{
//	U8 	fIsSystemHot;
//	U8	fIsSystemVoltError;
//}systemErrorStruct;


typedef enum{
	SYSTEM_ERROR=-1,
	SYSTEM_OK=0
}returnStatus;

#endif /* USER_INC_CONST_H_ */
