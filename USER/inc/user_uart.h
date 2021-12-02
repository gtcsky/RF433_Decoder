#ifndef __CX32LOO3_USER_UART_H
#define __CX32LOO3_USER_UART_H


/* Includes --------------------------*/
#include "cx32l003_uart.h"
#include "cx32l003_gpio.h"
#include "cx32l003_rcc.h"
#include "const.h"


//// 串口0-UART0
#define  UARTx                   			UART0
#define  UART_BAUDRATE           	57600

#define  RATEDBAUD_ENABLE    	ENABLE
#define  RATETIMER_ENABLE    	DISABLE
#define  UART_TX_GPIO_PORT       	GPIOA
#define  UART_TX_GPIO_PIN        	GPIO_Pin_2
#define  UART_TX_PIN_SOURCE      	GPIO_PinSource2
#define  UART_RX_GPIO_PORT       	GPIOA
#define  UART_RX_GPIO_PIN        	GPIO_Pin_1
#define  UART_RX_PIN_SOURCE      	GPIO_PinSource1

#define  UART_RX_AF_VALUE         	GPIO_AF_UART0_RX_PA1
#define  UART_TX_AF_VALUE         	GPIO_AF_UART0_TX_PA2

#define  UART_MODE               		UART_MODE1
#define  UART_IRQ                		UART0_IRQn
#define  UART_IRQHandler         	UART0_IRQHandler
#define  TIMx      					TIM10


#define	UART_TIME_OUT_CONST		3	//3ms
#define	UART_CMD_MIN_LEN			3//5
#define	UART_BUFFER_SIZE			20
#define	UART_ACK_BUFFER_SIZE		20

#define	UART_START_BYTE			0XAA
#define	UART_ACK_BYTE				0XBA
#define	UART_READ_START_BYTE		0XA5

extern	u8 	UART_ACK_BUF[UART_ACK_BUFFER_SIZE];

extern	UARTCommandStruct  uartCMDStruct;
extern	u8 	FlagState ;
extern	u8	vReceivedByte;
extern	u8	fIsUartSending;
void 	UART_Config(void);
void 	Uart_SendByte( UART_TypeDef * pUARTx, uint8_t ch);
void 	Uart_SendString( UART_TypeDef * pUSARTx, unsigned char *str,UINT8 len);
void 	Uart_SendHalfWord( UART_TypeDef * pUARTx, uint16_t ch);
void 	Uart_GetString(UART_TypeDef * pUARTx, uint8_t* g_cmd_buf);
void 	Uart_SendArray( UART_TypeDef * pUARTx, uint8_t *array, uint16_t num);
void		uartReceivedDataProcess(void);
void		uartSendDataProcess(void);

#endif

