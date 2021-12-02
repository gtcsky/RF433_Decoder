
// 基本定时器TIMx,x[6,7]定时初始化函数

#include "user_basetime.h"
#include "const.h"
#include "misc.h"
#include "user_exti.h"
#include "io_define.h"

uint32_t BASIC_TIMFLag = 0;
u16 vTime1msCnt;
// 中断优先级配置
static void TIM_NVIC_Config(IRQn_Type IRQn)
 {
	NVIC_InitTypeDef NVIC_InitStructure;
	// 设置中断组为0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	// 设置中断来源
//	NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ;
	NVIC_InitStructure.NVIC_IRQChannel = IRQn;
	// 设置主优先级为 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	// 设置抢占优先级为3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	userNVICPrioirySetting(&NVIC_InitStructure);
}


/** @ TIM MODE Config
  * @{  
  */
void BASIC_TIM_Mode_Config(TIM_TypeDef* TIMx)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;							//TIMx_CR

	TIM_TimeBaseInitStruct.TIM_ClockDivision = BASIC_TIM_ClKDIV;				//分频设置: 1.即不分频
//	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_Prescale_DIV32;				//分频设置: 32分频
	TIM_TimeBaseInitStruct.TIM_TMROS  = BASIC_TIM_TMROS;					//设置为重复模式
	TIM_TimeBaseInitStruct.TIM_TMRSZ = BASIC_TIM_TMRSZ;					//使用32位计数器,最大值为:0xFFFFFFFF
//	TIM_TimeBaseInitStruct.TIM_TMRSZ = TIM_Counter_TMRSZ_16BIT;				//使用16位计数器,最大值为:0xFFFF
	TIM_TimeBaseInitStruct.TIM_TMRMS = BASIC_TIM_TMRMS;					//定时器工作模式:自动重载计数器/定时器
	TIM_TimeBaseInitStruct.TIM_CounterMode = BASIC_TIM_COUNTERMODE;		//工作模式:定时器
	TIM_TimeBaseInitStruct.TIM_GATE = BASIC_TIM_GATE;						//disable GATE,  定时器工作不与否,仅仅由TR位决定
	TIM_TimeBaseInitStruct.TIM_GATE_Polarity = BASIC_TIM_GATE_POLARITY;		//GATE位 低电平有效
	if(TIM10==TIMx){
		TIM_TimeBaseInit(TIMx,&TIM_TimeBaseInitStruct);
		TIM_SetTimerLoadRegister(TIMx,BASIC_TIM_LOAD_VALUE);				//设置定时器重载值   0xFFFFA240.  定时周期(100000000-0xFFFFA240)*1/24M=1.00ms
	}else{
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_Prescale_DIV32;				//分频设置: 32分频
		TIM_TimeBaseInitStruct.TIM_TMRSZ = TIM_Counter_TMRSZ_16BIT;				//使用16位计数器,最大值为:0xFFFF
		TIM_TimeBaseInit(TIMx,&TIM_TimeBaseInitStruct);
		TIM_SetTimerLoadRegister(TIMx,0);									//设置定时器重载值   0X0000000.  定时周期(10000-0x0000)*1*32/24M=87ms周期重载,但不开打s中断时不产生中断
																		// 1.33us/step
//		TIM_NVIC_Config(TIMER11_IRQn);
//		TIM_ITConfig(TIMx,BASIC_TIM_TI_ENABLE);							//中断使能
		TIM_Cmd(TIMx,ENABLE);
		return;
	}

//	TEST_TIMGATE(BASIC_TIM,BASIC_TIM_GATE_PIN);							//设置定时器GATE 脚位
//	TEST_TIM_TOG();

	TIM_SetTimerLoadRegister(TIMx,BASIC_TIM_LOAD_VALUE);				//设置定时器重载值   0xFFFFA240.  定时周期(100000000-0xFFFFA240)*1/24M=1.00ms
//	TIM_SetTimerLoadRegister(BASIC_TIM,0);				//设置定时器重载值   0X0000000.  定时周期(10000-0x0000)*1*32/24M=87ms周期重载,但不开打中断时不产生中断
													// 1.33us/step
//	TIM_SetTimerLoadRegister(BASIC_TIM,0);				//设置定时器重载值   0X0000000.  定时周期(1000000000-0x00000000)*1/24M=178s周期重载,但不开打中断时不产生中断
													// 41ns/step
	TIM_NVIC_Config(TIMER10_IRQn);
	TIM_ITConfig(TIMx,BASIC_TIM_TI_ENABLE);							//中断使能
	TIM_Cmd(TIMx,ENABLE);
	return ;
}

/**
  * @brief  This function handles TIMER0_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void BASIC_TIM_IRQHandler(void)
{															//1MS一次中断
  TIM_ClearITFlag(BASIC_TIM,TIM_IT_FLAG);
  vTime1msCnt++;
  if(vTime1msCnt>=10000){
	  vTime1msCnt=0;
  }
	//BASIC_TIMFLag = 0x01;
}
//void TIMER11_IRQHandler(void)
//{															//1MS一次中断
//  TIM_ClearITFlag(TIM11,TIM_IT_FLAG);
//	//BASIC_TIMFLag = 0x01;
//  	  if(getDebugPinStts)
//  		  clr_Debug_Pin;
//  	  else
//  		  set_Debug_Pin;
//}


