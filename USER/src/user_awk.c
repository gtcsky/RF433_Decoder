#include "user_awk.h"
#include "const.h"
#include "user_lptimer.h"
#include "user_menu.h"
uint32_t AWK_flg;

// WWDG 中断优先级初始化
static void IWDG_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = AWK_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/* WWDG 配置函数
 */
/* *********************************************************************************
 *
 *clkDIV : 唤醒时钟分频  取值:0x00~0x0f   分频比2^(clkDIV+1)
 *		clkDIV=0x0e时: 分频比=2^(14+1)=32768
 *
 *awakeValue: 唤醒计数器
 *		awakeValue=0x100-35时
 *		唤醒周期: 35*(32768/38400)=29.867s
 **********************************************************************************/
void AWK_Config(void)
{	
	AWK_InitTypeDef AWK_InitStruct;
	
	AWK_InitStruct.AWK_XTLPRSC = DEBUG_AWK_XTLPRSC;
	AWK_InitStruct.AWK_SeleteClkSource = DEBUG_AWK_SELETECLKSOURCE;			//使用LIRC 不分频
	AWK_InitStruct.AWK_CounterClkDiv = AWK_COUNTERCLKDIV;						//分频2^(15+1)=65535
	AWK_Init(AWK,&AWK_InitStruct);
	
	IWDG_NVIC_Config(); //开启ARM中断使能
	AWK_SetRldval(DEBUG_AWK,AWK_VALUE);									//设置自动重置计数器	((0X100-255)*1/38400)*(AWK_COUNTERCLKDIV对应的值)
	AWK_Cmd(DEBUG_AWK,DEBUG_AWK_CMD);									//使能AWK功能
	AWK_SelClk(DEBUG_AWK,AWK_CLKLIRC);										//设置AWK使用时钟为LIRC
}

// 喂狗
void AWK_Feed(void)
{
	// 设置唤醒时间
	AWK_SetRldval(DEBUG_AWK,AWK_VALUE);									//唤醒周期=((0X100-AWK_VALUE)*1/38400)*(AWK_COUNTERCLKDIV 对应的值)
}



/**
  * @brief  This function handles SPI0COMB_IRQn interrupt request.
  * @param  None
  * @retval None
  */
void DEBUG_AWK_IRQHandler(void)
 {
	AWK_ClearITFlag(DEBUG_AWK);
	entryNormalModeChk();
//	LPTIMER_Cmd(DEBUG_LPTIMERx, ENABLE);			//醒来后重启LPT定时器
//	resetEntrySleepTime();
	AWK_flg = 0x01;
}




/*********************************************END OF FILE**********************/
