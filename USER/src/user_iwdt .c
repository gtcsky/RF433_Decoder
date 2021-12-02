/**
  ***************************************************************
  * @file    test_iwdt.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   
  ***************************************************************
  */

/*Includes ----------------------------*/
#include "user_iwdt.h"

uint32_t IWDG_FLAG;

// WWDG 中断优先级初始化
static void IWDG_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_IWDG_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/* WWDG 配置函数
 */
void IWDG_Config(void)
{	
	NVIC_EnableIRQ(DEBUG_IWDG_IRQ); /*打开ARM中断使能*/
	 /*打开ARM中断使能*/
	 IWDG_NVIC_Config();
   /*打开写保护*/
	 IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
	 IWDG_SetWdtMode(DEBUG_IWDG_MODE);
	 IWDG_WdtITShieldCmd(DEBUG_IWDG_MASK);
	 IWDG_SetReload(IWDG_LOAD_1S);
	 IWDG_RELOAD();
	 IWDG_Cmd();
	 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

}

// 喂狗
void IWDG_Feed(void)
{
	// 喂狗，刷新递减计数器的值
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
	IWDG_SetReload(IWDG_LOAD_1S);
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
}


/**
  * @brief  This function handles SPI0COMB_IRQn interrupt request.
  * @param  None
  * @retval None
  */
void DEBUG_IWDG_IRQHandler(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
	 IWDG_WdtITClear();
	 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	 IWDG_FLAG =0x1;
}


/************************ (C) COPYRIGHT to CX32L003 *****END OF FILE****/





