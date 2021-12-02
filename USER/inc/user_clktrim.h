#ifndef _USER_CLKTRIM_H
#define _USER_CLKTRIM_H

#include "cx32l003_clktrim.h"
#include "cx32l003_gpio.h"
#include "cx32l003_uart.h"
#include "cx32l003_rcc.h"


#define     DEBUG_CLKTRIMx        			CLKTRIM
#define     _CLKTRIM_REFCLK       			REFCLK_RCH
#define     _CLKTRIM_CALCLK       			CALCLK_RCL
#define     _CLKTRIM_REFVALUE     			0xffff
#define     _CLKTRIM_CALVALUE     			0xffff
#define     _CLKTRIM_MONTIOR_EN   		DISABLE

#define  DEBUG_CLKTRIM_IRQ                		CLKTRIM_IRQn
#define  DEBUG_CLKTRIM_IRQHandler         	CLKTRIM_IRQHandler

/*-------------define function------------------*/
void TEST_CLKTRIM_Config(void);


#endif
