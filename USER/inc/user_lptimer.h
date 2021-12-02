#ifndef _TEST_LPTIMER_H
#define _TEST_LPTIMER_H

#include "cx32l003_lptimer.h"
#include "cx32l003_syscon.h"
#include  "cx32l003_gpio.h"
#include	"const.h"

#define   DEBUG_LPTIMERx        LPTIMER
#define   _LPTIMER_Mode         LPTIMER_MODE2
#define   _LPTIMER_CTEN         LPTIMER_TIMER
#define   _LPTIMER_TCLK         LPTIMER_TCLK_LIRC
#define   _LPTIMER_GATEEN       LPTIMER_NGATE
#define   _LPTIMER_GATEPOLE     LPTIMER_GATE_HIGH
#define   _LPTIMER_TCLKCUTEN    LPTIMER_TICK_CUTENABLE
#define   _LPTIMER_TOG_EN       DISABLE

#define   _LPTIMER_GPIOx                 GPIOD
#define   _LPTIMER_EXT_PIN_SOURCE        GPIO_PinSource6
#define   _LPTIMER_TOG_PIN_SOURCE        GPIO_PinSource2
#define   _LPTIMER_TOGN_PIN_SOURCE       GPIO_PinSource3
#define   _LPTIMER_EXT_AF_VALUE          GPIO_AF_LPTIMER_EXT_PD6
#define   _LPTIMER_TOG_AF_VALUE          GPIO_AF_LPTIMER_TOG_PD2
#define   _LPTIMER_TOGN_AF_VALUE         GPIO_AF_LPTIMER_TOGN_PD3

#define   _LPTIMER_IT_STATUS             ENABLE
#define   _LPTIMER_IT_LOADVALUE          0xffff-192//0xffff-384//0x1ff
#define   _LPTIMER_IT_BGLOADVALUE     0xffff-192//0xffff-384  // 0x1ff
#define   _LPTIMER_IT_GATEPIN            0x00  //0x00:TIM11_GATE  0x01:UART0_RXD 0x02:UART1_RXD 0x03:LPUART_RXD

#define   _LPTIMER_SLEEP_MODE            0x00    //0x00: active; 0x01 sleepmode  0x02:deepsleepmode


#define   DEBUG_LPTIMER_IRQ                LPTIMER_IRQn
#define   DEBUG_LPTIMER_IRQHandler         LPTIMER_IRQHandler

//----------------define function----------------

extern	u16 vSystem5ms;
extern	u16 vSystemLIRC5ms;
void LPTIMER_Config(void);
void Enter_DeepSleep(void);
void Enter_Sleep(void);

#endif
