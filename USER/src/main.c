#include "communication.h"
#include "user_exti.h"
#include "user_led.h"
#include "user_advtime.h" 
#include "user_internalFlash.h"
#include "user_SysClock.h"
#include "user_rtc.h"
#include "user_lptimer.h"
#include "user_key.h"
#include "user_menu.h"
#include "user_adc.h"
#include "io_define.h"
#include "user_basetime.h"
#include "user_awk.h"
#include "user_iwdt.h"
#include "user_color.h"
#include "user_ddl.h"
#include "user_uart.h"
#include "user_internalFlash.h"

extern	u16 vSystem5ms;
extern	u8	vKeyValue;
#define	NON_EMULATE_GPIO 1			//NON_EMULATE_GPIO 未设置时 PC7,PD1用作仿真口,   设置时分别用作LED指示灯
u16 vDaValue;
float vDaVolt;
//u8 fIsNotMaskCodingFunc;
//u8	vTemp1U8;
//u8	vTemp2U8;
//u16	vTemp1U16;
//u16	vTemp2U16;
//u32	vTemp1U32;
//u32	vTemp2U32;
 /**
  * @brief   main
  * @param   无
  * @retval 无
  */
int main( void )
{
//	u32	iCNTVAL=0;
//	GPIO_InitTypeDef GPIO_InitStruct;
	RCC->AHBCLKEN =  0xffffffef; //flash,gpioa/b/c/d    ,CRC disable
// 	RCC->APBCLKEN =  0xffffffff; //uart,i2c,spi,pca,tim,btim, pwm? iwdt,dwdt,rtc,awk,trim
	//b31~21 reserve| b20 debug clk/b19 beep/b18 LVD/17 iWDG/16 trim/15 RTC /14 AWK /13 ADC /12 WWDG /11 TIM2/10 TIM1/9 1-wire/8 pca/7 pclk/6 basic time/5 LPT/4 SPI/3 LPTUART/2 i2c/1 UART1/0 UART0
//	0b11111111 111             1                  0                0             1               1    | |   0             1             1              1                 1              1              0           0    ||    1           1               1          0              0          0          1                 1
 	RCC->APBCLKEN =  0xfff37CE3; //uart,i2c,spi,pca,tim,btim, pwm? iwdt,dwdt,rtc,awk,trim
// 	RCC->APBCLKEN =  0xffffffff; //uart,i2c,spi,pca,tim,btim, pwm? iwdt,dwdt,rtc,awk,trim
	
		/*CLK TRIMING*/
//	RCC->REGLOCK =  UNLOCK_RAM_CONST;
//	RCC->HIRCCR = 0x5a690EE4;
//	RCC->CLKCON  |= 0x5a690005;
//	RCC->REGLOCK =  LOCK_RAM_CONST;
	
	//P47 时钟主频设置
	systemClkSet();
	fIsSystemInitialing=1;
	FlashInit();
	powerOnIoInit();
	powerDataInit();
	/*配置外部中断管脚*/
	EXTI_Key_Config();
	/*配置lptimer模块*/
	LPTIMER_Config();													//32.768K/38.4K时钟中断配置
	BASIC_TIM_Mode_Config(TIM10);										//basic定时器开启1ms定时中断
	BASIC_TIM_Mode_Config(TIM11);										//basic定时器开启1.33us/step 不中断

	/*串口初始化 */
//	UART_Config();
	
	/*配置PWM 模式*/
	userPwmParaStruct.period=ADVICE_TIM_PERIOD;
	ADVTIM_PWMMODE_Config(&userPwmParaStruct,ADVTIM1);
	resetEntrySleepTime();
	  /*Config IWDG Parameters*/
		//IWDG_Config();
	fIsSystemInitialing=0;
	fIsSystemOff=TRUE;
	while(1){
		funcKeyTask();
		dataReceivedProcess();
		if(vKeyValue){
			MenuFunction();
		}
//		uartReceivedDataProcess();
//		uartSendDataProcess();
		if(fIsNewCMDGod){
			fIsNewCMDGod=0;
			commandExcute();
		}
		if (vSystem5ms != 0) {
			vSystem5ms--;
			fucnPer5ms();

			//iCNTVAL=IWDG_GetReload();
//			IWDG_GetReload();
//			IWDG_Feed();
//			IWDG_RELOAD();
		}
	}
}//main




