#ifndef __EXTI_H
#define	__EXTI_H


/* Includes ------------------------*/
#include "cx32l003_gpio.h"
#include "cx32l003.h"
#include "cx32l003_conf.h"
#include "cx32l003_exti.h"
#include "const.h"
#include "misc.h"

extern	u16	vClosedKeyTimer;
extern	u16	vFuncKeyTimer;

//引脚定义

#define KEY1_IRQ_Pin_Enable     ENABLE
#define KEY1_IRQ_Pin_Type       ENABLE
#define KEY1_IRQ_Pin_Polarity   ENABLE
#define KEY1_IRQ_Pin_Edge       ENABLE
#define KEY1_IRQ_Pin_Clear      ENABLE
	
#define KEY1_INT_GPIO_PORT         GPIOC
#define KEY1_INT_GPIO_PIN          GPIO_Pin_3
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource3
#define KEY1_INT_EXTI_IRQ          GPIOC_IRQn
#define KEY1_IRQHandler            GPIOC_IRQHandler


#define KEY2_IRQ_Pin_Enable     ENABLE;
#define KEY2_IRQ_Pin_Type       DISABLE;
#define KEY2_IRQ_Pin_Polarity   ENABLE;
#define KEY2_IRQ_Pin_Edge       DISABLE;
#define KEY2_IRQ_Pin_Clear      ENABLE;

#define KEY2_INT_GPIO_PORT         GPIOC
#define KEY2_INT_GPIO_PIN          GPIO_Pin_4
#define KEY2_INT_EXTI_PINSOURCE    GPIO_PinSource4
#define KEY2_INT_EXTI_IRQ          GPIOC_IRQn
#define KEY2_IRQHandler            GPIOC_IRQHandler


//#define KEY3_IRQ_Pin_Enable     ENABLE;
//#define KEY3_IRQ_Pin_Type       DISABLE;
//#define KEY3_IRQ_Pin_Polarity   ENABLE;
//#define KEY3_IRQ_Pin_Edge       DISABLE;
//#define KEY3_IRQ_Pin_Clear      ENABLE;

//#define KEY3_INT_GPIO_PORT         GPIOC
//#define KEY3_INT_GPIO_PIN          GPIO_Pin_5
//#define KEY3_INT_EXTI_PINSOURCE    GPIO_PinSource5
//#define KEY3_INT_EXTI_IRQ          GPIOC_IRQn
//#define KEY3_IRQHandler            GPIOC_IRQHandler

#define FUNC_KEY_INT_GPIO_PORT         		GPIOA
#define FUNC_KEY_INT_GPIO_PIN          		GPIO_Pin_2
#define FUNC_KEY_INT_EXTI_PINSOURCE    	GPIO_PinSource2
#define FUNC_KEY_INT_EXTI_IRQ          		GPIOA_IRQn
#define FUNC_KEY_IRQHandler            		GPIOA_IRQHandler

#define FUNC_KEY_IRQ_Pin_Enable     		ENABLE;
#define FUNC_KEY_IRQ_Pin_Type       		DISABLE;
#define FUNC_KEY_IRQ_Pin_Polarity   		DISABLE;
#define FUNC_KEY_IRQ_Pin_Edge       		DISABLE;
#define FUNC_KEY_IRQ_Pin_Clear      			ENABLE;

#define CLOSED_KEY_INT_GPIO_PORT         		GPIOA
#define CLOSED_KEY_INT_GPIO_PIN          		GPIO_Pin_1
#define CLOSED_KEY_INT_EXTI_PINSOURCE    	GPIO_PinSource1
#define CLOSED_KEY_INT_EXTI_IRQ          			GPIOA_IRQn
#define CLOSED_KEY_IRQHandler            			GPIOA_IRQHandler

#define CLOSED_KEY_IRQ_Pin_Enable     		ENABLE;
#define CLOSED_KEY_IRQ_Pin_Type       		DISABLE;
#define CLOSED_KEY_IRQ_Pin_Polarity   		DISABLE;
#define CLOSED_KEY_IRQ_Pin_Edge       		DISABLE;
#define CLOSED_KEY_IRQ_Pin_Clear      		ENABLE;

//#define KEY4_IRQ_Pin_Enable     ENABLE;
//#define KEY4_IRQ_Pin_Type       DISABLE;
//#define KEY4_IRQ_Pin_Polarity   ENABLE;
//#define KEY4_IRQ_Pin_Edge       DISABLE;
//#define KEY4_IRQ_Pin_Clear      ENABLE;
//
//#define KEY4_INT_GPIO_PORT         GPIOC
//#define KEY4_INT_GPIO_PIN          GPIO_Pin_6
//#define KEY4_INT_EXTI_PINSOURCE    GPIO_PinSource6
//#define KEY4_INT_EXTI_IRQ          GPIOC_IRQn
//#define KEY4_IRQHandler            GPIOC_IRQHandler


/* define------------------------*/
void 	EXTI_Key_Config(void);
void		disableRXInt(void);
extern	void transferZeroDect(void);
extern	void userNVICPrioirySetting(NVIC_InitTypeDef* NVIC_InitStruct);
#endif /* __EXTI_H */
