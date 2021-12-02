/**
  ************************************************************************
  * @file    test_iwdt.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   This file contains all the functions prototypes for the iwdt
  ************************************************************************
  */

#ifndef __USER_WWDG_H
#define	__USER_WWDG_H

/* Includes --------------------------*/
#include "cx32l003_iwdt.h"
#include "misc.h"
#include "const.h"

// IWDG 参数设置
//#define  DEBUG_IWDG_MODE      COMMAND_WDT_INT
#define  DEBUG_IWDG_MODE      COMMAND_WDT_RESET
#define  DEBUG_IWDG_MASK      DISABLE
//#define  DEBUG_IWDG_LOAD      0x0002FFFF
#define  IWDG_LOAD_1S      	0x0000963E			//26us*0x963E=1s
#define  DEBUG_IWDG_IRQ                IWDT_IRQn
#define  DEBUG_IWDG_IRQHandler         IWDT_IRQHandler



//define function
void IWDG_Config(void);
void IWDG_Feed(void);
#endif
/************************ (C) COPYRIGHT To CX32L003 *****END OF FILE****/
