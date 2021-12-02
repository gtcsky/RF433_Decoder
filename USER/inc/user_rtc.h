#ifndef __RTC_H
#define	__RTC_H

#include "cx32l003_rcc.h"
#include "cx32l003_rtc.h"
//#include "user_calendar.h"
//#include "user_date.h"


//是否使用LCD显示日期
//#define USE_LCD_DISPLAY

#define       DEBUG_RTCx            RTC

#define      _RTC_FORMAT            RTC_Format_BCD
#define      _RTC_HOURFORMAT        RTC_HourFormat_24
#define      _RTC_CLKSELECT         RTC_CLK_LIRC
#define      _RTC_ASYNCHPREDIV      0x1ff
#define      _RTC_ASYNCHPREDIV_OFF      0x0000

#define      _RTC_YEAR              0x12
#define      _RTC_CENTURY           0x01 //2000年
#define	     _RTC_MONTH             RTC_Month_September //九月
#define      _RTC_DATE              0x15 //21号
	
#define	     _RTC_H12               _RTC_HOURFORMAT
#define      _RTC_HOURS             0x02
#define      _RTC_MINUTES           0x20
#define      _RTC_SECONDS           0x20
#define      _RTC_WEEKDAY           RTC_Weekday_Friday

#define      _RTC_BYPSHADSTATE_ENABLE      ENABLE

#define	    _RTC_NEWSTATUSALM1     DISABLE
#define	    _RTC_NEWSTATUSALM2     DISABLE
#define	    _RTC_NEWSTATUSALMEN    DISABLE

#define	    _RTC_CALIBOUTPUTEN           ENABLE
#define     _RTC_SMOOTHCALIBPERIOD       RTC_SmoothCalibPeriod_6sec
#define     _RTC_SMOOTHCALIBTRMINGVALUE  0xff

#define     _RTC_1HZOUTPUT_GPIOx         GPIOA
#define     _RTC_1HZOUTPUT_PIN_SOURCE    GPIO_PinSource3     
#define     _RTC_1HZOUTPUT_AF_VALUE      GPIO_AF_RTC_OUT1HZ_PA3     


#define     DEBUG_RTC_IRQ                		RTC_MATCH0_IRQn
#define     DEBUG_RTC_IRQHandler         	RTC_MATCH0_IRQHandler

#define     DEBUG_RTC_RCCx               RCC
#define     _RTC_LXT_LXAON               	0x01
#define     _RTC_LXT_LXPORT              	0x01
#define     _RTC_LXT_LXTBYP              	0x00
#define     _RTC_LXT_LXTDIV              		0x0F
#define     _RTC_LXT_LXTEN               		0x01
#define     _RTC_LXT_LXTSTARTUP          	0x00


/*Function Define*/
void RTC_NVIC_Config(void);
void RTC_Configuration(void);
void TEST_RTC1MHZOUTPUT_Config(void);

/**
  * @brief  RTC 周期中断设置结构体
  */
typedef struct
{
  uint32_t RTC_ALM2PR_Ctrl;								//控制开关RTC ALM2周期中断
  uint32_t RTC_ALM2PR_PRD;							//RTC ALM2周期中断的周期设定
}RTC_PRTypeDef;


#define 	RESET_ALM2PR_INT		0xFFFFFFDF
#define 	_RTC_ALM2PR_ENABLE	0x00000020
#define 	RESET_ALM2PR_PERIOD	0xFFFFFFF0
#define 	_RTC_ALM2PR_PERIOD	0x00000008			//1/128=7.8125MS
#define	RESET_ALM2_F			0xFFFFFFDF
#endif /* __XXX_H */
