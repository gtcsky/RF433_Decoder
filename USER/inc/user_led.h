#ifndef __USER_LED_H
#define __USER_LED_H

/* Includes ------------------------*/
#include "cx32l003_gpio.h"
#include "cx32l003.h"
#include "cx32l003_conf.h"


//#define      LED1_GPIO_PORT                      		GPIOA
//#define      LED1_GPIO_PORT_PIN                  		GPIO_Pin_1
//#define      LED1_GPIO_PORT_PIN_SOURCE           	GPIO_PinSource1
//
//
//#define      LED2_GPIO_PORT                      		GPIOC
//#define      LED2_GPIO_PORT_PIN                  		GPIO_Pin_1
//#define      LED2_GPIO_PORT_PIN_SOURCE           	GPIO_PinSource1
//
//
//
//#define      LED1_OFF     GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PORT_PIN)
//#define      LED1_ON      GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PORT_PIN)
//
//#define      LED2_OFF     GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PORT_PIN)
//#define      LED2_ON      GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PORT_PIN)


//#define  	RED_LED_PORT					GPIOD
//#define  	RED_LED_PIN						GPIO_Pin_1
//#define  	RED_LED_PIN_SOURCE				GPIO_PinSource1
//#define	clr_Red_LED						GPIO_ResetBits(RED_LED_PORT, RED_LED_PIN)
//#define	set_Red_LED						GPIO_SetBits(RED_LED_PORT, RED_LED_PIN)
//
//#define  	BLUE_LED_PORT					GPIOC
//#define  	BLUE_LED_PIN					GPIO_Pin_7
//#define  	BLUE_LED_PIN_SOURCE				GPIO_PinSource7
//#define	clr_Blue_LED						GPIO_ResetBits(BLUE_LED_PORT, BLUE_LED_PIN)
//#define	set_Blue_LED						GPIO_SetBits(BLUE_LED_PORT, BLUE_LED_PIN)

/* define ------------------------*/
void LED_GPIO_Config(void);

#endif
