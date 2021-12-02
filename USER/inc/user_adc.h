#ifndef __ADC_H
#define	__ADC_H


#include "cx32l003_adc.h"
#include "cx32l003_rcc.h"
#include "cx32l003_gpio.h"
#include "cx32l003_spi.h"
#include "cx32l003_lpuart.h"
#include "cx32l003_uart.h"
#include "cx32l003_uart.h"
#include "const.h"
#include "user_menu.h"

// ADC 编号选择
// 可以是 ADC1/2，如果使用ADC3，中断相关的要改成ADC3的
#define    DEBUG_ADCx         				ADC
#define   _ADC_CIRCLEMODE     				ADC_Mode_Independent
#define	  _ADC_CTMODE         				ADC_Ct_Contine
#define	  _ADC_SETADCCNT      			0x00002f00//0x00000100
#define	  _ADC_SETADCCNT_SIGNAL      		0x00000300//0x00000100
#define   _ADC_TRIGS0SEL      				ADC_Trigs0_DISABLE
#define 	_ADC_TRIGS1SEL      				ADC_Trigs1_DISABLE
	
#define   _ADC_ChannelSel     				ADC_Channel0
#define   _ADC_CLKSEL         				ADC_Prescaler_Div1
#define   _ADC_SAMSEL         				ADC_SAMPLE_4CYCLE

// ADC GPIO宏定义
#define    ADC_GPIOx                     			GPIOC
#define    ADC_PIN_SOURCE                		GPIO_PinSource6
#define    ADC_AF_VALUE                  			GPIO_AF_AIN0_PC6


#define    ADC_IT_FLAG                   			ADC_TICHANNEL0_FLAG
#define    ADC_IT_STATE                  			DISABLE

#define    ADC_SOFTWARECONV_ENABLE       ENABLE
#define    ADC_SOFTWARECONV_CYCLE           12

#define    ADC_EXITTRIE_SEL                         	0x01

#define     ADC_CHANNEL_EN                		ADC_Channel0_ENABLE


// ADC 中断相关宏定义
#define    DEBUG_ADC_IRQ                       		ADC0_IRQn
#define    DEBUG_ADC_IRQHandler                   ADC0_IRQHandler



//-----------------define function--------------
void ADC_MutiMode_Config(u8 vtADCChls);
void ADC_SignalMode_Config(u8 vtADCChl);
void ADC_NVIC_Config(void);
void mutiChannesADC(UserADCTypeDef *adcStruct);
//u16 readADCResultFromMutiChls(ADCChlDefType ch);
u16 readADCResultFromMutiChls(u8 ch);
u16 getSignalChlADC(u8 channel);
u32 adcChlCMD2adcAdcChl(u32 chlCMD);
extern	returnStatus vSystemErrorCheck(void);
extern	void	 adcThresholdGenerate(void);
#endif /* __ADC_H */

