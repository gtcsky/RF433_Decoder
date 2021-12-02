/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------*/
#include "user_exti.h"

#include "../inc/communication_customize.h"
#include "user_key.h"
#include "user_menu.h"
#include "user_uart.h"
#include "io_define.h"
#include "const.h"
//#include "misc.h"
uint8_t 	EXTI_IT_FLAG = 0;
/******************************************************************************
 *
 *
 *
 */
void userNVICPrioirySetting(NVIC_InitTypeDef* NVIC_InitStruct) {
	u32 vtIndex = 0, vtGroup = 0, vtTemp = 0, vtValue = 0, vtMask = 0;
	vtIndex = NVIC_InitStruct->NVIC_IRQChannel % 4;
	vtGroup = NVIC_InitStruct->NVIC_IRQChannel / 4;
	vtTemp = vtIndex * 8 + 6;
	if (!NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority){
		vtValue = 0x00;
	}
	else {
		vtValue = (NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority - 1) << vtTemp;		//兼容原厂优先级设置
	}
	vtMask = ~(0x03 << vtTemp);
	NVIC->IP[vtGroup] &= vtMask;
	NVIC->IP[vtGroup] |= vtValue;
}

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void GPIOA_NVIC_Configuration(void)
 {
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 配置NVIC为优先级组1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* 配置中断源：按键1 */
	NVIC_InitStructure.NVIC_IRQChannel = GPIOA_IRQn;
	/* 配置抢占优先级 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 配置子优先级 */
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断通道 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	userNVICPrioirySetting(&NVIC_InitStructure);
}

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void GPIOB_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* 配置中断源：按键1 */
  NVIC_InitStructure.NVIC_IRQChannel = GPIOB_IRQn;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void GPIOC_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* 配置中断源：按键1 */
  NVIC_InitStructure.NVIC_IRQChannel = GPIOC_IRQn;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
 // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void GPIOD_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = GPIOD_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
 // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
 /**
  * @brief  配置 IO为EXTI中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */

///***************************************************************
// *
// * 	设置过零检测Pin触发类型
// * 	edge=0:  下降沿
// *		=1:	上升沿
// ****************************************************************/
//void	setZeroDectIntEdge(extIntEdge  edge){
//	GPI0_IRQ_InitTypeDef  GPI0_IRQ_InitStruct;
//	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Enable = ENABLE;			//GPIOx_INTEN	0/1 :disable/enable 外部中断
//	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Type = DISABLE;			//GPIOx_INTTYPCR  设置中断触发类型    0/1 :边沿触发/电平触发
//	if(edge)
//		GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Polarity = ENABLE;		//GPIOx_INTPOLCR   0/1 :下降或低电平触发/上升或高电平触发
//	else
//		GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Polarity = DISABLE;	//GPIOx_INTPOLCR   0/1 :下降或低电平触发/上升或高电平触发
//	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Edge =  DISABLE;			//GPIOx_INTANY 设置边沿触发类型,   0/1 :由PxIVAL5决定/双沿触发
//	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Clear = ENABLE;			//GPIOx_INTCLR  0/1:保留/清除中断标志
//	GPIO_EXTILineConfig(zeroCrossDetPort,&GPI0_IRQ_InitStruct, zeroCrossDetPin);		//配置旋钮/编码器功能选择口
//}

void	disableRXInt(void){
	GPI0_IRQ_InitTypeDef  GPI0_IRQ_InitStruct;
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Enable = DISABLE;			//GPIOx_INTEN	0/1 :disable/enable 外部中断
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Type = DISABLE;			//GPIOx_INTTYPCR  设置中断触发类型    0/1 :边沿触发/电平触发
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Polarity = DISABLE;		//GPIOx_INTPOLCR   0/1 :下降或低电平触发/上升或高电平触发
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Edge =  DISABLE;			//GPIOx_INTANY 设置边沿触发类型,   0/1 :由PxIVAL5决定/双沿触发
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Clear = ENABLE;			//GPIOx_INTCLR  0/1:保留/清除中断标志
	/* 选择EXTI的信号源 */
	GPIO_EXTILineConfig(UART_RX_GPIO_PORT,&GPI0_IRQ_InitStruct, UART_RX_GPIO_PIN);
}

void EXTI_Key_Config(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct;
	GPI0_IRQ_InitTypeDef  GPI0_IRQ_InitStruct;

										
	/* 配置 NVIC 中断*/
	GPIOA_NVIC_Configuration();
	GPIOB_NVIC_Configuration();
	GPIOC_NVIC_Configuration();
	GPIOD_NVIC_Configuration();

/*--------------------------KEY配置-----------------------------*/
//
//

	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Enable = ENABLE;			//GPIOx_INTEN	0/1 :disable/enable 外部中断
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Type = DISABLE;			//GPIOx_INTTYPCR  设置中断触发类型    0/1 :边沿触发/电平触发
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Polarity = DISABLE;		//GPIOx_INTPOLCR   0/1 :下降或低电平触发/上升或高电平触发
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Edge =  DISABLE;			//GPIOx_INTANY 设置边沿触发类型,   0/1 :由PxIVAL5决定/双沿触发
	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Clear = ENABLE;			//GPIOx_INTCLR  0/1:保留/清除中断标志
	/* 选择EXTI的信号源 */

	GPIO_EXTILineConfig(KeyPower_Port,&GPI0_IRQ_InitStruct, KeyPower_Pin);
	GPIO_EXTILineConfig(KeyTimer_Port,&GPI0_IRQ_InitStruct, KeyTimer_Pin);

	GPI0_IRQ_InitStruct.GPI0_IRQ_Pin_Edge =  ENABLE;			//GPIOx_INTANY 设置边沿触发类型,   0/1 :由PxIVAL5决定/双沿触发
	GPIO_EXTILineConfig(CommunPort,&GPI0_IRQ_InitStruct, CommunPin);
//	GPIO_PinAFConfig(UART_RX_GPIO_PORT,UART_RX_PIN_SOURCE,0); //RX
//	uartRXPortAsNormalIoInput();
//	GPIO_EXTILineConfig(UART_RX_GPIO_PORT,&GPI0_IRQ_InitStruct, UART_RX_GPIO_PIN);
}

/**
  * @brief  This function handles  GPIO_IRQHandler.
  * @param  None
  * @retval None
  */
static void GPIO_IRQHandler(GPIO_TypeDef* GPIOx)
{
	entryNormalModeChk();
	if((GPIOx->RIS&GPIO_Pin_3)&&(GPIOx->MIS&GPIO_Pin_3))
	{
		GPIOx->ICLR |= GPIO_Pin_3;
		if(GPIOx==GPIOD){
			setPowerKeyPressedFlag();
		}
	}
	else if((GPIOx->RIS&GPIO_Pin_5)&&(GPIOx->MIS&GPIO_Pin_5))
	{
		GPIOx->ICLR |= GPIO_Pin_5;
//		if(GPIOx==GPIOB){
//			dataReceiveFunc();
//		}
	}
	else if((GPIOx->RIS&GPIO_Pin_0)&&(GPIOx->MIS&GPIO_Pin_0))
	{
		GPIOx->ICLR |= GPIO_Pin_0;

	}
	else if((GPIOx->RIS&GPIO_Pin_1)&&(GPIOx->MIS&GPIO_Pin_1))
	{
		GPIOx->ICLR |= GPIO_Pin_1;
		if(GPIOx==GPIOC){
		   	   ;//						UART 唤醒
		}
	}
	else if((GPIOx->RIS&GPIO_Pin_2)&&(GPIOx->MIS&GPIO_Pin_2))
	{
		GPIOx->ICLR |= GPIO_Pin_2;
	}
	else if((GPIOx->RIS&GPIO_Pin_4)&&(GPIOx->MIS&GPIO_Pin_4))
	{
		GPIOx->ICLR |= GPIO_Pin_4;
		if(GPIOx==GPIOB){
			dataReceiveFunc();
		}
	}
//	else if((GPIOx->RIS&GPIO_Pin_5)&&(GPIOx->MIS&GPIO_Pin_5))
//	{
//		GPIOx->ICLR |= GPIO_Pin_5;
//		if(GPIOx==GPIOB){
//			dataReceiveFunc();
//		}
//	}
	else if((GPIOx->RIS&GPIO_Pin_6)&&(GPIOx->MIS&GPIO_Pin_6))
	{
		GPIOx->ICLR |= GPIO_Pin_6;
	}
	else if((GPIOx->RIS&GPIO_Pin_7)&&(GPIOx->MIS&GPIO_Pin_7))
	{
		GPIOx->ICLR |= GPIO_Pin_7;
	}
}

/**
  * @brief  This function handles GPIOA Handler.
  * @param  None
  * @retval None
  */
void GPIOA_IRQHandler(void)
{
	EXTI_IT_FLAG = 0x01;//置位中断标志位
	GPIO_IRQHandler(GPIOA);
}

/**
  * @brief  This function handles GPIOB Handler.
  * @param  None
  * @retval None
  */
void GPIOB_IRQHandler(void)
{
	EXTI_IT_FLAG = 0x01;//置位中断标志位
	GPIO_IRQHandler(GPIOB);
}

/**
  * @brief  This function handles GPIOC Handler.
  * @param  None
  * @retval None
  */
void GPIOC_IRQHandler(void)
{
	EXTI_IT_FLAG = 0x01;//置位中断标志位
	GPIO_IRQHandler(GPIOC);
}

/**
  * @brief  This function handles GPIOD Handler.
  * @param  None
  * @retval None
  */
void GPIOD_IRQHandler(void)
{
	EXTI_IT_FLAG = 0x01;//置位中断标志位
	GPIO_IRQHandler(GPIOD);
}
/*********************************************END OF FILE**********************/

