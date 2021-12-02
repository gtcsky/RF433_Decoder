#include "user_lptimer.h"
#include "user_basetime.h"
#include "misc.h"
#include "const.h"
#include "user_led.h"
#include "io_define.h"
#include "user_awk.h"
#include "user_exti.h"
#include "user_ddl.h"
u8 fTestFlag;
u16 vSystemLIRC5ms;
u16 vSystem5ms;
u8	vTimerCnt;
u8	fTime50ms;
u8	fTime100ms;
u8	fTime500ms;
u8	fTime1s;
uint8_t  lPTIMER_FLAG  = 0;

//u32 counterArray[10]={0};
u8 vTimerTest=0;
/** @defgroup Enter_DeepSleep
  * @{ 
  */
void Enter_DeepSleep(void)
{
	/*
	 *配置AWK功能
	 */
//	AWK_Config();
	EXTI_Key_Config();									//设置UART RX为普通IO唤醒口
//	NVIC_EnableIRQ(AWK_IRQn); 							/*打开ARM中断使能*/
	LPTIMER_Cmd(DEBUG_LPTIMERx,DISABLE);				//关闭LPT 防止唤醒
	SCB->SCR |= 0x04;   
	__WFI();
}

/** @defgroup Enter_Sleep
  * @{ 
  */
void Enter_Sleep(void)
{
	LPTIMER_Cmd(DEBUG_LPTIMERx,DISABLE);
	SCB->SCR &= (~0x04);  
	__WFI();
}


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_LPTIMER_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
  userNVICPrioirySetting(&NVIC_InitStructure);
}


/** @ test_basetime_timer 
  * @{  
  */
void  TEST_SETLPTIMERGATE(uint8_t Gate_pin)
{
			if(Gate_pin == 0x00) //gate = TIM11_GATE
			{
			  GPIO_PinAFConfig(GPIOB,0x04,0x01); //GATE
				SYSCTRL_IPTIM_GateConfig(SYSCTRL,(uint32_t)0x0000);
			}
			else if(Gate_pin == 0x01) //gate = UART0_RXD
			{
				GPIO_PinAFConfig(GPIOD,0x03,0x05);
				SYSCTRL_IPTIM_GateConfig(SYSCTRL,(uint32_t)0x100);
			}
			else if(Gate_pin == 0x02) //gate = UART1_RXD
			{
				GPIO_PinAFConfig(GPIOD,0x06,0x05);
				SYSCTRL_IPTIM_GateConfig(SYSCTRL,(uint32_t)0x200);
			}
			else {
				if(Gate_pin == 0x03)
				{
					GPIO_PinAFConfig(GPIOC,0x06,0x05); //LPUART_RXD
					SYSCTRL_IPTIM_GateConfig(SYSCTRL,(uint32_t)0x300);
				}
			}
}

/** @ test_timer_ini 
  * @{  
  */
void LPTIMER_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
//	GPIO_InitTypeDef GPIO_InitStruct;
	LPTIMER_InitTypeDef LPTIM_InitStruct;
//	DDL_ZERO_STRUCT(GPIO_InitStruct);
	DDL_ZERO_STRUCT(LPTIM_InitStruct);
	/*LPTIM 时钟参数设置*/
	LPTIM_InitStruct.LPTIMER_Mode     =     _LPTIMER_Mode;				//LPTIM_CR.MODE		0/1:  定时器不重载/自动重载模式
	LPTIM_InitStruct.LPTIMER_CTEN     =     _LPTIMER_CTEN;				//LPTIM_CR.CT_SEL		0/1:	定时/计数模式
	LPTIM_InitStruct.LPTIMER_TCLK     =     _LPTIMER_TCLK;				//TCK_SEL[1:0]   LPTIM定时器时钟选择	00:PCLK   01:LXT   11:LIRC
	LPTIM_InitStruct.LPTIMER_GATEEN   =     _LPTIMER_GATEEN;			//LPTIM_CR.GATE_EN	  定时器门控  0/1:  无/有门控
	LPTIM_InitStruct.LPTIMER_GATEPOLE =     _LPTIMER_GATEPOLE;		//LPTIM_CR.GATE_P	门控极性  0/1 :  高/低电平有效
	LPTIM_InitStruct.LPTIMER_TCLKCUTEN =    _LPTIMER_TCLKCUTEN;		//LPTIM_CR.TCK_EN	LPTIM 计数时钟使能
	LPTIMER_Init(DEBUG_LPTIMERx, &LPTIM_InitStruct);
	
	/*是否开启TOG功能*/
//	LPTIMER_TogCmd(DEBUG_LPTIMERx,_LPTIMER_TOG_EN);
	

//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
//	GPIO_Init(_LPTIMER_GPIOx,&GPIO_InitStruct);
	/*设置复用端口*/
//	GPIO_PinAFConfig(_LPTIMER_GPIOx,_LPTIMER_EXT_PIN_SOURCE,_LPTIMER_EXT_AF_VALUE); //EXT
//	GPIO_PinAFConfig(_LPTIMER_GPIOx,_LPTIMER_TOG_PIN_SOURCE,_LPTIMER_TOG_AF_VALUE); //TOG	 enable		PD.2
//	GPIO_PinAFConfig(_LPTIMER_GPIOx,_LPTIMER_TOGN_PIN_SOURCE,_LPTIMER_TOGN_AF_VALUE); //TOGN
	
		/*配置复用管脚*/
//	TEST_SETLPTIMERGATE(_LPTIMER_IT_GATEPIN);
	
	NVIC_Configuration();
	
	/*配置LPTIMER功能参数*/
	LPTIMER_LoadConfig(DEBUG_LPTIMERx, _LPTIMER_IT_LOADVALUE);			//配置立即重载值为:192  ,溢出值为0xFFFF  所以定时周期为(FFFF-192)*1/38400=5ms
	LPTIMER_BGloadConfig(DEBUG_LPTIMERx,_LPTIMER_IT_BGLOADVALUE);		//配置周期重载值为:192
	LPTIMER_ITConfig(DEBUG_LPTIMERx,_LPTIMER_IT_STATUS);					//enable interrupt
	LPTIMER_Cmd(DEBUG_LPTIMERx,ENABLE);								//LPTIM_CR.TIM_RUN 定时器开始工作
	
	/*进入低功耗模式*/
//	if(_LPTIMER_SLEEP_MODE == 0x01)
//		Enter_Sleep();
//	else if(_LPTIMER_SLEEP_MODE == 0x02)
//		Enter_DeepSleep();
//	else
//	{;}   //active 状态
		
//	return ;
}


/** @ test_timer_ini 
  * @{  
  */
void DEBUG_LPTIMER_IRQHandler(void)
{
//	if(vTimerTest<=9){
//		counterArray[vTimerTest++]=TIM_GetCountRegister(BASIC_TIM);
//	}else{
//		vTimerTest=15;
//	}

	LPTIMER_ClearITFlag(LPTIMER,LPTIMER_IT_FLAG);					//设定为5ms中断一次
	vSystemLIRC5ms++;
	vSystem5ms++;
	vTimerCnt++;
	if(vTimerCnt%10==0){
		fTime50ms=1;
	}
	if(vTimerCnt%20==0){
		fTime100ms=1;
	}
	if(vTimerCnt%100==0){
		fTime500ms=1;
	}
	if(vTimerCnt%200==0){
		fTime1s=1;
		vTimerCnt=0;
	}
	if(vSystem5ms>=USER_DOG_CONST){
		NVIC_SystemReset();
	}
	lPTIMER_FLAG = 0x01;
}

