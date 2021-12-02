#include "user_advtime.h"
#include "io_define.h"
#include "misc.h"
#include "user_menu.h"
#include "user_exti.h"
uint8_t ucIntCC1Flag = 0;
uint8_t ucIntCC2Flag = 0;
uint8_t ucIntCC3Flag = 0;
uint8_t ucIntCC4Flag = 0;
uint8_t ucIntCOMFlag = 0;
uint8_t ucIntTriggerFlag = 0;
uint8_t ucIntBreakFlag = 0;
uint8_t ucIntServedFlag = 0;


uint32_t ulIntCntTmp = 0;
uint32_t CaptureValue = 0;
uint32_t ulFrequencyCH1 = 0;
uint32_t ulFrequencyCH2 = 0;
uint32_t ulFrequencyCH3 = 0;
uint32_t ulFrequencyCH4 = 0;
uint32_t ulCaptureCC1Old = 0;
uint32_t ulCaptureCC2Old = 0;
uint32_t ulCaptureCC3Old = 0;
uint32_t ulCaptureCC4Old = 0;


//static void DELAYCELL(uint32_t count)
//{
//	uint32_t i,j;
//	for(i=0; i<count; i++)
//		for(j=0; j<count; j++);
//}



//static void ADVTIM1_Reset(void)
//{
//	RCC->REGLOCK = 0x55AA6699;	//reg write protect diable
//	RCC->RERIRST |= 1<<10;				//ADVTIM1 reset
//	RCC->REGLOCK = 0x55AA669A;	//reg write protect diable
//}

//static void ADVTIM1_ReleaseReset(void)
//{
//	RCC->REGLOCK = 0x55AA6699;	//reg write protect diable
//	RCC->RERIRST &= ~(1<<10);				//ADVTIM1 reset
//	RCC->REGLOCK = 0x55AA669A;	//reg write protect diable
//}


//static void GPIO_Reset(void)
//{
//	RCC->REGLOCK = 0x55AA6699;			//reg write protect diable
//	RCC->RERIRST |= 0x0F<<24;				//GPIO reset
//	RCC->REGLOCK = 0x55AA669A;			//reg write protect diable
//}
//
//static void GPIO_ReleaseReset(void)
//{
//	RCC->REGLOCK = 0x55AA6699;			//reg write protect diable
//	RCC->RERIRST &= ~(0x0F<<24);		//GPIO reset
//	RCC->REGLOCK = 0x55AA669A;			//reg write protect diable
//}

///** @defgroup
//  * @{
//  */
//
//static void ADVTIM2_Reset(void)
//{
//	RCC->REGLOCK = 0x55AA6699;	//reg write protect diable
//	RCC->RERIRST |= 1<<11;				//ADVTIM2 reset
//	RCC->REGLOCK = 0x55AA669A;	//reg write protect diable
//}
//
//static void ADVTIM2_ReleaseReset(void)
//{
//	RCC->REGLOCK = 0x55AA6699;	//reg write protect diable
//	RCC->RERIRST &= ~(1<<11);				//ADVTIM2 reset
//	RCC->REGLOCK = 0x55AA669A;	//reg write protect diable
//}




//static void DeepSleep(void)
//{
//	RCC->REGLOCK = 0x55AA6699;			//reg write protect diable
//	NVIC_EnableIRQ(IWDT_IRQn);
//	*(unsigned int*)(0xE000ED10) = 0x04;
//	RCC->CLKCON = 0x5A69C006;	// enable LIRC clock
//	while((RCC->LIRCCR&0x1000) != 0x1000);
//	RCC->CLKSEL = 0x5a690004;
//	RCC->CLKCON = 0x5A69C004;
//
//	IWDG->LOCK = 0x55AA6699;
//	IWDG->CFG = 0x01;
//	IWDG->RLOAD = 0x800;
//	IWDG->COMMAND = 0x55;
//	__wfi();
//	RCC->CLKSEL = 0x5a690004;	//clock change to LIRC
//	while(1);
//
//}

// 中断优先级配置
//static void ADVANCE_TIM_NVIC_Config(void)
// {
//	NVIC_InitTypeDef NVIC_InitStructure;
//	// 设置中断组为0
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	// 设置中断来源
//	NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ;
//	// 设置主优先级为 0
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	// 设置抢占优先级为3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	NVIC_Init(&NVIC_InitStructure);
//	userNVICPrioirySetting(&NVIC_InitStructure);
//}

///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */
void TEST_TIM_Mode_Config(void)
 {
//	ADVTIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//
//	/*复位高级TIM*/
//	ADVTIM1_Reset();
//	ADVTIM1_ReleaseReset();
//	ADVTIM2_Reset();
//	ADVTIM2_ReleaseReset();
//
//	/*配置高级TIM*/
//	TIM_TimeBaseStructure.TIM_Period = ADVICE_TIM_PERIOD;
//	TIM_TimeBaseStructure.TIM_Prescaler = ADVICE_TIM_PRESCALER;
//	TIM_TimeBaseStructure.TIM_ClockDivision = ADVICE_TIM_CLKDIV;
//	TIM_TimeBaseStructure.TIM_CounterMode = ADVICE_TIM_COUNTERMODE;
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = ADVICE_TIM_REPETITONCOUNTER;
//	ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//
//	/*打开自动装载功能*/
//	ADVTIM_ARRPreloadConfig(ADVICE_TIMx, ADVTIM_ARRPRELOAD_EN);
//
//	/*清除中断标志位*/
//	ADVTIM_ClearFlag(ADVICE_TIMx, ADVTIM_UPDATA_FLAG);
//
//	/*配置中断*/
//	ADVANCE_TIM_NVIC_Config();
//	ADVTIM_ITConfig(ADVICE_TIMx, ADVTIM_IT_FLAG, ADVTIM_IT_UPDATE_EN);
//
////    /*打开高级TIM功能*/
////    ADVTIM_Cmd(ADVICE_TIMx, ENABLE);
//
}

/** @defgroup 
  * @{  
  */

void TEST_ADVTIM_MULTICHANEEL_Config(void)
{
//	uint16_t PrescalerValue;
//	ADVTIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	ADVTIM_OCInitTypeDef TIM_OCInitStructure;
//
//	/* Compute the prescaler value */
//	PrescalerValue = (uint16_t) (SystemCoreClock / 10000) - 1;
//
//	/* Time base configuration */
//	TIM_TimeBaseStructure.TIM_Period = ADVICE_TIM_PERIOD;
//	TIM_TimeBaseStructure.TIM_Prescaler = ADVICE_TIM_PRESCALER;
//	TIM_TimeBaseStructure.TIM_ClockDivision = ADVICE_TIM_CLKDIV;
//	TIM_TimeBaseStructure.TIM_CounterMode = ADVICE_TIM_COUNTERMODE;
//
//	ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//
//	/* Prescaler configuration */
//	ADVTIM_PrescalerConfig(ADVICE_TIMx, PrescalerValue, TIM_PSCReloadMode_Immediate);
//
//	/* Output Compare Timing Mode configuration: Channel1 */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = ADVTIM_CCR1_VALUE;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//
//	ADVTIM_OC1Init(ADVTIM1, &TIM_OCInitStructure);
//
//	ADVTIM_OC1PreloadConfig(ADVICE_TIMx, TIM_OCPreload_Disable);
//
//	/* Output Compare Timing Mode configuration: Channel2 */
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = ADVTIM_CCR2_VALUE;
//
//	ADVTIM_OC2Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//	ADVTIM_OC2PreloadConfig(ADVICE_TIMx, TIM_OCPreload_Disable);
//
//	/* Output Compare Timing Mode configuration: Channel3 */
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = ADVTIM_CCR3_VALUE;
//
//	ADVTIM_OC3Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//	ADVTIM_OC3PreloadConfig(ADVICE_TIMx, TIM_OCPreload_Disable);
//
//	/* Output Compare Timing Mode configuration: Channel4 */
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = ADVTIM_CCR4_VALUE;
//
//	ADVTIM_OC4Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//	ADVTIM_OC4PreloadConfig(ADVICE_TIMx, TIM_OCPreload_Disable);
//
//	/* TIM IT enable */
//	ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
//
////  /* ADVTIM1 enable counter */
////  ADVTIM_Cmd(ADVICE_TIMx, ENABLE);
////
////	while(ucIntCC1Flag == 0);
////	ucIntCC1Flag = 0;
////	while(ucIntCC2Flag == 0);
////	ucIntCC2Flag = 0;
////	while(ucIntCC3Flag == 0);
////	ucIntCC3Flag = 0;
////	while(ucIntCC4Flag == 0);
////	ucIntCC4Flag = 0;
//
////	uart_puts(pUARTx,"multichannel compare function interrupt ok\n");
//	return;
}


/** @defgroup 
  * @{  
  */
void ADVTIM_PWMMODE_Config(UserPwmInitTypeDef *pwmStruct ,ADVTIM_TypeDef* TIMx)
{
	ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	ADVTIM_OCInitTypeDef  TIM_OCInitStructure;
//	GPIO_InitTypeDef GPIO_InitStruct;
//	vPWMPeriod=vtPeriod;
//	RCC->REGLOCK = 0x55AA6699;
//	RCC->IOMUX = 0x5A690000;			//set swdio			b0=0/1   普通IO/仿真端口
//	RCC->REGLOCK = 0x55AA6698;
	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;						//Output 模式
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;							//GPIOx_OTYPER   0/1 推挽输出/开漏输出
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;						//设置.3 .4
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;							//上拉
//	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
//	GPIO_Init(GPIOC,&GPIO_InitStruct);									//配置PC3和PC4
//
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;						//Output 模式
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;							//GPIOx_OTYPER   0/1 推挽输出/开漏输出
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_4;						//设置.4 .6
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;							//上拉
//	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
//	GPIO_Init(GPIOD,&GPIO_InitStruct);									//配置PD6和PD4

//	GPIOC->AFR&=0xFFF0FFFF;
//	GPIOC->AFR|=0x00010000;											//GPIOC 复用配置 		PC3 as PWM CH3 ,PC4 as PWM CH4
//	GPIOD->AFR&=0xF0F0FFFF;
//	GPIOD->AFR|=0x01010000;											//GPIOD 复用配置 		PD4 as PWM CH1 , PD6 as PWM CH2
//	GPIOA->AFR&=0xFFFF0FFF;
//	GPIOA->AFR|=0x00001000;											//GPIOA 复用配置 		PA3 as PWM CH3N
//	GPIOD->AFR&=0xFFFF00FF;
//	GPIOD->AFR|=0x00001100;											//GPIOD 复用配置 		PD3 as PWM CH3N
		
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = ADVICE_TIM_PRESCALER;						//预分频 1
  TIM_TimeBaseStructure.TIM_CounterMode = ADVICE_TIM_COUNTERMODE;			//TIM1_CR1.b4  设置计数器向上计数  CMS[1:0]  00时为边沿对齐,其它时候为中央对齐
  TIM_TimeBaseStructure.TIM_Period = pwmStruct->period;							//TIM1_ARR  自动重载寄存器,在PWM模式用于确定PWM的频率.   PWM频率=系统时钟/(TIM1_ARR+1) 用TIM1_CCRx确定占空比   占空比为:   TIM1_CCRx/(TIM1_ARR+1)
  TIM_TimeBaseStructure.TIM_ClockDivision = ADVICE_TIM_CLKDIV;					//CKD[1:0]    00：tDTS = tCK_INT
  TIM_TimeBaseStructure.TIM_RepetitionCounter = ADVICE_TIM_REPETITONCOUNTER;	//TIM1_RCR	如果使用了重复计数器功能，在向上计数达到设置的重复计数次数(TIM1_RCR)时，产生更新事件(UEV)； 00 则每次溢出产生更新事件
  ADVTIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			//OC1M[2:0]  110：PWM 模式 1－ 在向上计数时，一旦 TIM1_CNT<TIM1_CCR1  时通道 1 为有效电平，否则为无效电平；
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		//设置TIM1_CCER.CC1E  CC1 通道配置为输出时	0/1：关闭/开启输出到对应的引脚
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	//设置TIM1_CCER.CC1NE 输入/捕获 1 互补输出使能   0/1：关闭/开启输出到对应的引脚
  TIM_OCInitStructure.TIM_Pulse = ADVTIM_TIM_CHANNEL1PULSE;		//设置PWM channel1  占空比相关参数//CCR1[15:0] 包含了装入当前捕获/比较 1 寄存器的值(预装载值) 当前捕获/比较寄存器参与同计数器 TIM1_CNT 的比较，并在OC1 端口上产生输出信号  ADVTIM_TIM_CHANNEL4PULSE/(ADVICE_TIM_PERIOD+1)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//TIM1_CCER.CC1P=1.输出模式时,低电平有效
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;       	//设置CC1NP 输入/捕获 1 互补输出极性  0/1:	OC1 高/低电平有效；
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;		//设置OIS1  输出空闲状态 1(OC1 输出)    0/1:	OC1=0/1;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Set;		//设置OIS1N  输出空闲状态 1(OC1N 输出)    0/1:	OC1N=0/1;
  ADVTIM_OC1Init(TIMx, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = ADVTIM_TIM_CHANNEL2PULSE;		//设置PWM channel2  占空比相关参数//CCR2[15:0] 包含了装入当前捕获/比较 2 寄存器的值(预装载值) 当前捕获/比较寄存器参与同计数器 TIM1_CNT 的比较，并在OC2 端口上产生输出信号   ADVTIM_TIM_CHANNEL4PULSE/(ADVICE_TIM_PERIOD+1)
  ADVTIM_OC2Init(TIMx, &TIM_OCInitStructure);


  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;       	//设置CC1NP 输入/捕获 1 互补输出极性  0/1:	OC1 高/低电平有效；
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Set;		//设置OIS1N  输出空闲状态 1(OC1N 输出)    0/1:	OC1N=0/1;
  TIM_OCInitStructure.TIM_Pulse = ADVTIM_TIM_CHANNEL3PULSE;		//设置PWM channel3  占空比相关参数//CCR3[15:0] 包含了装入当前捕获/比较 3 寄存器的值(预装载值) 当前捕获/比较寄存器参与同计数器 TIM1_CNT 的比较，并在OC3 端口上产生输出信号   ADVTIM_TIM_CHANNEL4PULSE/(ADVICE_TIM_PERIOD+1)
  ADVTIM_OC3Init(TIMx, &TIM_OCInitStructure);
	
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;       		//设置CC1NP 输入/捕获 1 互补输出极性  0/1:	OC1 高/低电平有效；
//   TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;		//设置OIS1  输出空闲状态 1(OC1 输出)    0/1:	OC1=0/1;
  TIM_OCInitStructure.TIM_Pulse = ADVTIM_TIM_CHANNEL4PULSE;		//设置PWM channel4  占空比相关参数//CCR4[15:0] 包含了装入当前捕获/比较 4 寄存器的值(预装载值) 当前捕获/比较寄存器参与同计数器 TIM1_CNT 的比较，并在OC4 端口上产生输出信号    ADVTIM_TIM_CHANNEL4PULSE/(ADVICE_TIM_PERIOD+1)
  ADVTIM_OC4Init(TIMx, &TIM_OCInitStructure);
  /* TIM1 counter enable */
  ADVTIM_Cmd(TIMx, ENABLE);
			
  /* TIM1 Main Output Enable */
  ADVTIM_CtrlPWMOutputs(TIMx, ENABLE);
	
//	RCC->REGLOCK = 0x55AA6699;
//	RCC->IOMUX =   0x5A690001;			//set swdio
//	RCC->REGLOCK = 0x55AA6698;
	
}
/**********************************************************************
 * 开启或关闭 某个或几个PWM输出口
 ***********************************************************************/
void switchPwmChannel(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin,FunctionalState NewState)
{
	uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	/* ------------------------- Configure the port pins ---------------- */
	/*-- GPIO Mode Configuration --*/
	RCC->REGLOCK = 0x55AA6699;
	for (pinpos = 0x00; pinpos < 0x08; pinpos++)
	{
		pos = ((uint32_t)0x01) << pinpos;
		/* Get the port pins position */
		currentpin = GPIO_Pin & pos;

		if (currentpin == pos)
		{
			GPIOx->AFR  &= ~(GPIO_MODER_MODER0 << (pinpos * 4));
			if(NewState==ENABLE){
				GPIOx->AFR  |= GPIO_MODER_MODER0_1 << (pinpos * 4);
			}
		}
	}
	RCC->REGLOCK = 0x55AA6698;
}



//void updatePWMChlDuty(PwmChlDefType Channel,float vtDuty){
void updatePWMChlDuty(PwmChlDefType Channel,float vtDuty,ADVTIM_TypeDef* TIMx){
	if(vtDuty>1)
		vtDuty=1;
	if(Channel==PWM_CH1){
		TIMx->CCR1 = (u32)(vtDuty*(userPwmParaStruct.period+1));
	}
	else if(Channel==PWM_CH2){
		TIMx->CCR2 = (u32)(vtDuty*(userPwmParaStruct.period+1));
	}
	else if(Channel==PWM_CH3){
		TIMx->CCR3 = (u32)(vtDuty*(userPwmParaStruct.period+1));
	}
	else if(Channel==PWM_CH4){
		TIMx->CCR4 = (u32)(vtDuty*(userPwmParaStruct.period+1));
	}else if(Channel==PWM_CH3N){
		TIMx->CCR3 = (u32)(PWM_PERIOD_CONST-vtDuty*(userPwmParaStruct.period+1));
	}
}

//void  updateBuzzerDuty(float vtDuty){
//	updatePWMChlDuty(BUZZER_CHANNEL, vtDuty);
//}
//void  updateMotorDuty(float vtDuty){
//	updatePWMChlDuty(CW_LED_CHANNEL, vtDuty);
//}
//void  updateDischargeDuty(float vtDuty){
//	updatePWMChlDuty(DISCHARGE_CHANNEL, vtDuty);
//}
//void  updateChargeDuty(float vtDuty){
//	updatePWMChlDuty(CHARGE_CHANNEL, vtDuty);
//}
//void  updateMotorDuty(float vtDuty){
//	updatePWMChlDuty(CW_LED_CHANNEL, vtDuty);
//}
//void  updateMotorDuty(){
//	if(fIsMotorStartup){
//		updatePWMChlDuty(CW_LED_CHANNEL, vPWMStartupDuty);
//	}else{
//		updatePWMChlDuty(CW_LED_CHANNEL, vMotorDriverLv);
//	}
//}
/************************************************************
 *vPWMPeriod;				//PWM频率=系统频率/(vPWMPeriod+1);
 *channel可以是	BUZZER_CHANNEL|CW_LED_CHANNEL|DISCHARGE_CHANNEL|CHARGE_CHANNEL
 *				以及他们的子集
 *调用函数前先选定好与channel对应的全局变量duty
 *
 *************************************************************/
//void updatePwmFreq(u16 vtPeriod,u8 channels){
//	vPWMPeriod=vtPeriod;
//	ADVICE_TIMx->ARR = vPWMPeriod;												//TIM1_ARR  自动重载寄存器,在PWM模式用于确定PWM的频率.    用TIM1_CCRx确定占空比
//
//	if(channels&BUZZER_CHANNEL){
//		updatePWMChlDuty(BUZZER_CHANNEL, vBuzzerDuty);
//	}
//	if(channels&CW_LED_CHANNEL){
//		updatePWMChlDuty(CW_LED_CHANNEL, vMotorDuty);
//	}
//	if(channels&DISCHARGE_CHANNEL){
//		updatePWMChlDuty(DISCHARGE_CHANNEL, vDischargeDuty);
//	}
//	if(channels&CHARGE_CHANNEL){
//		updatePWMChlDuty(CHARGE_CHANNEL, vChargeDuty);
//	}
//}
/************************************************************
 *vPWMPeriod;				//PWM频率=系统频率/(vPWMPeriod+1);
 *channel可以是	BUZZER_CHANNEL|CW_LED_CHANNEL|DISCHARGE_CHANNEL|CHARGE_CHANNEL
 *				以及他们的子集
 *调用函数前先设定好与channel对应的PWM结构体中的duty
 *
 *************************************************************/
//void updatePwmFreq(UserPwmInitTypeDef *pwmStruct,ADVTIM_TypeDef* TIMx){
//	TIMx->ARR = pwmStruct->period;				//TIM1_ARR  自动重载寄存器,在PWM模式用于确定PWM的频率.    用TIM1_CCRx确定占空比

//	if(!(pwmStruct->channels&CW_LED_CHANNEL))
//		pwmStruct->dutyArray[CW_LED_DUTY_INDEX]=0;
//	updatePWMChlDuty(CW_LED_CHANNEL, pwmStruct->dutyArray[CW_LED_DUTY_INDEX],TIMx);
//}

/** @defgroup test_advtim1_capture_mode
  * @{ 
  */
void TEST_ADVTIM_CAPTUREMODE_Config(void)
{	
//   	ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	  ADVTIM_ICInitTypeDef  TIM_ICInitStructure;
//
//		/* Time Base configuration */
//		TIM_TimeBaseStructure.TIM_Prescaler = ADVICE_TIM_PRESCALER;
//		TIM_TimeBaseStructure.TIM_CounterMode = ADVICE_TIM_COUNTERMODE;
//		TIM_TimeBaseStructure.TIM_Period = ADVICE_TIM_PERIOD;
//		TIM_TimeBaseStructure.TIM_ClockDivision = ADVICE_TIM_CLKDIV;
//		TIM_TimeBaseStructure.TIM_RepetitionCounter = ADVICE_TIM_REPETITONCOUNTER;
//		ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//
//		/*配置ICInitStructure结构体*/
//		TIM_ICInitStructure.TIM_Channel = ADVTIM_TIM_Channel1;
//		TIM_ICInitStructure.TIM_ICPolarity = ADVTIM_TIM_ICPolarity;
//		TIM_ICInitStructure.TIM_ICSelection = ADVTIM_TIM_ICSelection;
//		TIM_ICInitStructure.TIM_ICPrescaler = ADVTIM_TIM_ICPrescaler;
//		TIM_ICInitStructure.TIM_ICFilter = ADVTIM_TIM_ICFilter;
//
//
//
//		ADVTIM_ICInit(ADVICE_TIMx, &TIM_ICInitStructure);
//
//		TIM_ICInitStructure.TIM_Channel = ADVTIM_TIM_Channel2;
//		ADVTIM_ICInit(ADVICE_TIMx, &TIM_ICInitStructure);
//
//		TIM_ICInitStructure.TIM_Channel = ADVTIM_TIM_Channel3;
//		ADVTIM_ICInit(ADVICE_TIMx, &TIM_ICInitStructure);
//
//		TIM_ICInitStructure.TIM_Channel = ADVTIM_TIM_Channel4;
//		ADVTIM_ICInit(ADVICE_TIMx, &TIM_ICInitStructure);
//
//	  /*配置管脚复用*/
//	  GPIO_PinAFConfig(ADVTIM_TIM_CAPTURE_GPIOx,ADVTIM_TIM_CAPTURE_PIN_SOURCE,ADVTIM_TIM_AF_VALUE);
//
//		/* Enable the CC1 Interrupt Request */
//		ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC1, ENABLE);
//		/* Enable the CC2 Interrupt Request */
//		ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC2, ENABLE);
//		/* Enable the CC3 Interrupt Request */
//		ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC3, ENABLE);
//		/* Enable the CC4 Interrupt Request */
//		ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC4, ENABLE);
//		ADVICE_TIMx->SR = 0x0000;
//
//		ADVANCE_TIM_NVIC_Config();
//
//		/* ADVTIM1 enable counter */
//		ADVTIM_Cmd(ADVICE_TIMx, ENABLE);
//
////		while(1)
////		{
////			delaycell(0xFFF);
//
////			for(ulStrCnt=0; ulStrCnt<4; ulStrCnt++)	{
////				HexToStr(&ucRegStr[ulStrCnt*2], (uint8_t *)(&ulFrequencyCH1)+3-ulStrCnt, 1);
////			}
////			uart_puts(pUARTx, "Channel1 frequency is 0x");
////			uart_puts(pUARTx, (char*)ucRegStr);
////			uart_puts(pUARTx, "\n");
////			ulFrequencyCH1 = 0;
////
////			for(ulStrCnt=0; ulStrCnt<4; ulStrCnt++)	{
////				HexToStr(&ucRegStr[ulStrCnt*2], (uint8_t *)(&ulFrequencyCH2)+3-ulStrCnt, 1);
////			}
////			uart_puts(pUARTx, "Channel2 frequency is 0x");
////			uart_puts(pUARTx, (char*)ucRegStr);
////			uart_puts(pUARTx, "\n");
////			ulFrequencyCH2 = 0;
////
////			for(ulStrCnt=0; ulStrCnt<4; ulStrCnt++)	{
////				HexToStr(&ucRegStr[ulStrCnt*2], (uint8_t *)(&ulFrequencyCH3)+3-ulStrCnt, 1);
////			}
////			uart_puts(pUARTx, "Channel3 frequency is 0x");
////			uart_puts(pUARTx, (char*)ucRegStr);
////			uart_puts(pUARTx, "\n");
////			ulFrequencyCH3 = 0;
////
////			for(ulStrCnt=0; ulStrCnt<4; ulStrCnt++)	{
////				HexToStr(&ucRegStr[ulStrCnt*2], (uint8_t *)(&ulFrequencyCH4)+3-ulStrCnt, 1);
////			}
////			uart_puts(pUARTx, "Channel4 frequency is 0x");
////			uart_puts(pUARTx, (char*)ucRegStr);
////			uart_puts(pUARTx, "\n");
////			ulFrequencyCH4 = 0;
////
////		}
////
//		return ;
}



/** @defgroup test_advtim1_single_capture_mode
  * @{ 
  */
void TEST_ADVTIM_SINGLECAPTUREMODE_Config(void)
{	
//		ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	  ADVTIM_ICInitTypeDef  TIM_ICInitStructure;
//
//		ADVTIM1_Reset();
//		ADVTIM1_ReleaseReset();
//
//		RCC->REGLOCK = 0x55aa6699;
//		RCC->CLKCON |= 0x5a690004;	//LRC enable
//		RCC->REGLOCK = 0x55aa669a;
//
//		GPIOA->AFR |= ADVTIM_TIM_Channel;
//		if(ADVICE_TIMx == ADVTIM1)
//		SYSCTRL->TIM1_CHINMUX |= ADVTIM_TIM_Channel;
//	  if(ADVICE_TIMx == ADVTIM2)
//    SYSCTRL->TIM2_CHINMUX |= ADVTIM_TIM_Channel;
//
//		/* Time Base configuration */
//		TIM_TimeBaseStructure.TIM_Prescaler = ADVICE_TIM_PRESCALER;
//		TIM_TimeBaseStructure.TIM_CounterMode = ADVICE_TIM_COUNTERMODE;
//		TIM_TimeBaseStructure.TIM_Period = ADVICE_TIM_PERIOD;
//		TIM_TimeBaseStructure.TIM_ClockDivision = ADVICE_TIM_CLKDIV;
//		TIM_TimeBaseStructure.TIM_RepetitionCounter = ADVICE_TIM_REPETITONCOUNTER;
//		ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//    /*配置ICInitStructure结构体*/
//		TIM_ICInitStructure.TIM_Channel = ADVTIM_TIM_Channel;
//		TIM_ICInitStructure.TIM_ICPolarity = ADVTIM_TIM_ICPolarity;
//		TIM_ICInitStructure.TIM_ICSelection = ADVTIM_TIM_ICSelection;
//		TIM_ICInitStructure.TIM_ICPrescaler = ADVTIM_TIM_ICPrescaler;
//		TIM_ICInitStructure.TIM_ICFilter = ADVTIM_TIM_ICFilter;
//		ADVTIM_ICInit(ADVICE_TIMx, &TIM_ICInitStructure);
//
//		switch(ADVTIM_TIM_Channel)
//		{
//			case 0x00:
//				/* Enable the CC1 Interrupt Request */
//				ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC1, ENABLE);
//				break;
//			case 0x04:
//				/* Enable the CC2 Interrupt Request */
//				ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC2, ENABLE);
//				break;
//			case 0x08:
//				/* Enable the CC3 Interrupt Request */
//				ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC3, ENABLE);
//				break;
//			case 0x0C:
//				/* Enable the CC4 Interrupt Request */
//				ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_CC4, ENABLE);
//				break;
//			default:
//				break;
//		}
//
//		ucIntCC1Flag = 0;
//		ADVICE_TIMx->SR = 0x0000;
//
//	  ADVANCE_TIM_NVIC_Config();
//
//		/* ADVTIM1 enable counter */
//		ADVTIM_Cmd(ADVICE_TIMx, ENABLE);
//
//		while(1)
//		{
//			while(ucIntCC1Flag == 0x00);
//			ucIntCC1Flag = 0x00;
//	//		k= 0;
//	//		for(i=0;i<19;i++)
//	//		{
//	//			if(advtim_buffer[i+1]>=advtim_buffer[i])
//	//			{
//	//			data=advtim_buffer[i+1]-advtim_buffer[i];
//	//			dec_val[k++] = (char)(data>>8);
//	//			dec_val[k++] = (char)(data);
//	//			}
//	//			else
//	//			{
//	//			data=(advtim_buffer[i+1]+0x10000)-advtim_buffer[i];
//	//			dec_val[k++] = (char)(data>>8);
//	//			dec_val[k++] = (char)(data);
//
//	//			}
//	//		}
//	//		ByteToHexStr(dec_val,buffer,38);
//	//		uart_puts(pUARTx, "\nrev:> ");
//	//		uart_puts(pUARTx, buffer);
////		return 0;
////			for(ulStrCnt=0; ulStrCnt<4; ulStrCnt++)	{
////				HexToStr(&ucRegStr[ulStrCnt*2], (uint8_t *)(&ulFrequencyCH2)+3-ulStrCnt, 1);
////			}
////			uart_puts(pUARTx, "Channel2 frequency is 0x");
////			uart_puts(pUARTx, (char*)ucRegStr);
////			uart_puts(pUARTx, "\n");
////			ulFrequencyCH2 = 0;
////
////			for(ulStrCnt=0; ulStrCnt<4; ulStrCnt++)	{
////				HexToStr(&ucRegStr[ulStrCnt*2], (uint8_t *)(&ulFrequencyCH3)+3-ulStrCnt, 1);
////			}
////			uart_puts(pUARTx, "Channel3 frequency is 0x");
////			uart_puts(pUARTx, (char*)ucRegStr);
////			uart_puts(pUARTx, "\n");
////			ulFrequencyCH3 = 0;
////
////			for(ulStrCnt=0; ulStrCnt<4; ulStrCnt++)	{
////				HexToStr(&ucRegStr[ulStrCnt*2], (uint8_t *)(&ulFrequencyCH4)+3-ulStrCnt, 1);
////			}
////			uart_puts(pUARTx, "Channel4 frequency is 0x");
////			uart_puts(pUARTx, (char*)ucRegStr);
////			uart_puts(pUARTx, "\n");
////			ulFrequencyCH4 = 0;
//
////		}
////
////		return 0;
//
//  }
//	//return ;
}



/** @defgroup test_advtim1_cascade_mode
  * @{ 
  */    
void TEST_ADVTIM_CASACADEMODE_Config(void)
{	
//	ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	ADVTIM_OCInitTypeDef  TIM_OCInitStructure;
//
//  /* Time base configuration */
//  TIM_TimeBaseStructure.TIM_Period = ADVICE_TIM_PERIOD;
//  TIM_TimeBaseStructure.TIM_Prescaler = ADVICE_TIM_PRESCALER;
//  TIM_TimeBaseStructure.TIM_ClockDivision = ADVICE_TIM_CLKDIV;
//  TIM_TimeBaseStructure.TIM_CounterMode = ADVICE_TIM_COUNTERMODE;
//  ADVTIM_TimeBaseInit(ADVTIM1, &TIM_TimeBaseStructure);
//
//  TIM_TimeBaseStructure.TIM_Period =   0x8000;
//  TIM_TimeBaseStructure.TIM_Prescaler = 0x8000;
//  ADVTIM_TimeBaseInit(ADVTIM2, &TIM_TimeBaseStructure);
//
//  /* Master Configuration in PWM1 Mode */
//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = 64;
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//
//  ADVTIM_OC1Init(ADVTIM1, &TIM_OCInitStructure);
//  ADVTIM_OC2Init(ADVTIM1, &TIM_OCInitStructure);
//  ADVTIM_OC3Init(ADVTIM1, &TIM_OCInitStructure);
//	ADVTIM_OC4Init(ADVTIM1, &TIM_OCInitStructure);
//
//	ADVTIM1->CCR1 = 0x1000;
//	ADVTIM1->CCR2 = 0x1500;
//	ADVTIM1->CCR3 = 0x1600;
//	ADVTIM1->CCR4 = 0x1700;
//  /* Select the Master Slave Mode */
//  ADVTIM_SelectMasterSlaveMode(ADVTIM1, TIM_MasterSlaveMode_Enable);
//
//  /* Master Mode selection */
//  ADVTIM_SelectOutputTrigger(ADVTIM1, ADVTIM_TIM_TRGOSOURCE);	//EGR bit0 reset ADVTIM2 count
////  ADVTIM_SelectOutputTrigger(ADVTIM1, TIM_TRGOSource_Enable);
////  ADVTIM_SelectOutputTrigger(ADVTIM1, TIM_TRGOSource_Update);
////  ADVTIM_SelectOutputTrigger(ADVTIM1, TIM_TRGOSource_OC1);
////  ADVTIM_SelectOutputTrigger(ADVTIM1, TIM_TRGOSource_OC1Ref);
////  ADVTIM_SelectOutputTrigger(ADVTIM1, TIM_TRGOSource_OC2Ref);
////  ADVTIM_SelectOutputTrigger(ADVTIM1, TIM_TRGOSource_OC3Ref);
////  ADVTIM_SelectOutputTrigger(ADVTIM1, TIM_TRGOSource_OC4Ref);
//
//  /* Slaves Configuration: PWM1 Mode */
//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = 1;
//
//  ADVTIM_OC1Init(ADVTIM2, &TIM_OCInitStructure);
//
//
//  /* Slave Mode selection: TIM2 */
////  ADVTIM_SelectSlaveMode(ADVTIM2, TIM_SlaveMode_Reset);
////  ADVTIM_SelectSlaveMode(ADVTIM2, TIM_SlaveMode_Gated);
////  ADVTIM_SelectSlaveMode(ADVTIM2, TIM_SlaveMode_Trigger);
//	ADVTIM_SelectSlaveMode(ADVTIM2, TIM_SlaveMode_External1);
//
//  ADVTIM_SelectInputTrigger(ADVTIM2, TIM_TS_ITR0);
//
//  /* TIM enable counter */
//  ADVTIM_Cmd(ADVTIM2, ENABLE);
//  ADVTIM_Cmd(ADVTIM1, ENABLE);
//
//	return ;
}



/** @defgroup test_advtim1_outputcompare
  * @{ 
  */
void TEST_ADVTIM_OUTPUTCOMPARE_Config(void)
{
//
//	ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	ADVTIM_OCInitTypeDef  TIM_OCInitStructure;
//	uint32_t PrescalerValue = PrescalerValue;
//
//  /*Compute the prescaler value */
//  PrescalerValue = (uint16_t) (SystemCoreClock / 2000) - 1;
//  /* Time base configuration */
//  TIM_TimeBaseStructure.TIM_Period = ADVICE_TIM_PERIOD;
//  TIM_TimeBaseStructure.TIM_Prescaler = ADVICE_TIM_PRESCALER;
//  TIM_TimeBaseStructure.TIM_ClockDivision = ADVICE_TIM_CLKDIV;
//  TIM_TimeBaseStructure.TIM_CounterMode = ADVICE_TIM_COUNTERMODE;
//  ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//
//  /* Output Compare Active Mode configuration: Channel1 */
//  TIM_OCInitStructure.TIM_OCMode = ADVTIM_TIM_OCMODE;			//seven mode
//  TIM_OCInitStructure.TIM_OutputState = ADVTIM_TIM_OUTPUTSTATE;
//  TIM_OCInitStructure.TIM_Pulse = ADVTIM_CCR1_VALUE;
//  TIM_OCInitStructure.TIM_OCPolarity = ADVTIM_TIM_ICPolarity;
//  ADVTIM_OC1Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//  ADVTIM_OC1PreloadConfig(ADVICE_TIMx, TIM_OCPreload_Disable);
//
//  /* Output Compare Active Mode configuration: Channel2 */
//  TIM_OCInitStructure.TIM_OutputState = ADVTIM_TIM_OUTPUTSTATE;
//  TIM_OCInitStructure.TIM_Pulse = ADVTIM_CCR2_VALUE;
//
//  ADVTIM_OC2Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//  ADVTIM_OC2PreloadConfig(ADVICE_TIMx, TIM_OCPreload_Disable);
//
//  /* Output Compare Active Mode configuration: Channel3 */
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = ADVTIM_CCR3_VALUE;
//
//  ADVTIM_OC3Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//  ADVTIM_OC3PreloadConfig(ADVICE_TIMx, TIM_OCPreload_Disable);
//
//  /* Output Compare Active Mode configuration: Channel4 */
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = ADVTIM_CCR4_VALUE;
//
//  ADVTIM_OC4Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//  ADVTIM_OC4PreloadConfig(ADVICE_TIMx, TIM_OCPreload_Disable);
//
//  ADVTIM_ARRPreloadConfig(ADVICE_TIMx, ENABLE);
//
//  /* ADVTIM1 enable counter */
//  ADVTIM_Cmd(ADVICE_TIMx, ENABLE);
//
//	return ;
}


/** @defgroup test_advtim1_onepulse
  * @{ 
  */
void TEST_ADVTIM_ONEPLUS_Config(void)
{
//	ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	ADVTIM_OCInitTypeDef  TIM_OCInitStructure;
//	ADVTIM_ICInitTypeDef  TIM_ICInitStructure;
//
//	ADVTIM1_Reset();
//	ADVTIM1_ReleaseReset();
//
//  /* Time base configuration */
//  TIM_TimeBaseStructure.TIM_Period = ADVICE_TIM_PERIOD;
//  TIM_TimeBaseStructure.TIM_Prescaler = ADVICE_TIM_PRESCALER;
//  TIM_TimeBaseStructure.TIM_ClockDivision = ADVICE_TIM_CLKDIV;
//  TIM_TimeBaseStructure.TIM_CounterMode = ADVICE_TIM_COUNTERMODE;
//  ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//
//  /* ADVTIM1 PWM2 Mode configuration: Channel1 */
//  TIM_OCInitStructure.TIM_OCMode = ADVTIM_TIM_OCMODE;
//  TIM_OCInitStructure.TIM_OutputState = ADVTIM_TIM_OUTPUTSTATE;
//  TIM_OCInitStructure.TIM_Pulse = 0x8ff;
//  TIM_OCInitStructure.TIM_OCPolarity = ADVTIM_TIM_0CPOLARITY;
//  ADVTIM_OC1Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//  /* ADVTIM1 configuration in Input Capture Mode */
//  ADVTIM_ICStructInit(&TIM_ICInitStructure);
//  TIM_ICInitStructure.TIM_Channel = ADVTIM_TIM_Channel;
//  TIM_ICInitStructure.TIM_ICPolarity = ADVTIM_TIM_ICPolarity;
//  TIM_ICInitStructure.TIM_ICSelection = ADVTIM_TIM_ICSelection;
//  TIM_ICInitStructure.TIM_ICPrescaler = ADVTIM_TIM_ICPrescaler;
//  TIM_ICInitStructure.TIM_ICFilter = ADVTIM_TIM_ICFilter;
//  ADVTIM_ICInit(ADVICE_TIMx, &TIM_ICInitStructure);
//
//  /*One Pulse Mode selection */
//  ADVTIM_SelectOnePulseMode(ADVICE_TIMx, TIM_OPMode_Single);
//
//  /* Input Trigger selection */
//  ADVTIM_SelectInputTrigger(ADVICE_TIMx, TIM_TS_TI2FP2);
//
//  /* Slave Mode selection: Trigger Mode */
//  ADVTIM_SelectSlaveMode(ADVICE_TIMx, TIM_SlaveMode_Trigger);
//	  /* TIM1 Main Output Enable */
//  ADVTIM_CtrlPWMOutputs(ADVICE_TIMx, ENABLE);
//	//PC6 config as ADVTIM1_CH1 onepulse output
//	//PD2 config as ADVTIM1_CH2 trigger input(TI2FP2)
//	GPIOC->AFR = 0x01000000;
//	GPIOD->AFR = 0x00000100;
//	return ;
}




/** @defgroup test_advtim1_deadtime_break
  * @{ 
  */
void TEST_ADVTIM_DEADTIME_BREAK(void)
{	
//	ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	ADVTIM_OCInitTypeDef  TIM_OCInitStructure;
//	ADVTIM_BDTRInitTypeDef TIM_BDTRInitStructure;
//
//	ADVTIM1_Reset();
//	ADVTIM1_ReleaseReset();
//
//	TIM_TimeBaseStructure.TIM_Period=  ADVICE_TIM_PERIOD;
//	TIM_TimeBaseStructure.TIM_Prescaler= ADVICE_TIM_PRESCALER;
//	TIM_TimeBaseStructure.TIM_ClockDivision=ADVICE_TIM_CLKDIV;
//	TIM_TimeBaseStructure.TIM_CounterMode=ADVICE_TIM_COUNTERMODE;
//	TIM_TimeBaseStructure.TIM_RepetitionCounter= ADVICE_TIM_REPETITONCOUNTER;
//	ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//
//	TIM_OCInitStructure.TIM_OCMode = ADVTIM_TIM_OCMODE;
//	TIM_OCInitStructure.TIM_OutputState = ADVTIM_TIM_OUTPUTSTATE;
//	TIM_OCInitStructure.TIM_OutputNState = ADVTIM_TIM_OUTPUTNSTATE;
//	TIM_OCInitStructure.TIM_Pulse = 0x60;
//	TIM_OCInitStructure.TIM_OCPolarity = ADVTIM_TIM_0CPOLARITY;
//	TIM_OCInitStructure.TIM_OCNPolarity = ADVTIM_TIM_0CNPOLARITY;
//	TIM_OCInitStructure.TIM_OCIdleState = ADVTIM_TIM_0CIDLESTATE;
//	TIM_OCInitStructure.TIM_OCNIdleState = ADVTIM_TIM_OCNIDLESTATE;
//	ADVTIM_OC1Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
////ADVTIM_OC1PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);
//	TIM_OCInitStructure.TIM_Pulse = 0x70;
//	ADVTIM_OC2Init(ADVICE_TIMx, &TIM_OCInitStructure);
//	TIM_OCInitStructure.TIM_Pulse = 0x80;
//	ADVTIM_OC3Init(ADVICE_TIMx, &TIM_OCInitStructure);
//	TIM_OCInitStructure.TIM_Pulse = 0x90;
//	ADVTIM_OC4Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//	/*配置BDTR寄存器*/
//  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
//  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
//  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
//  TIM_BDTRInitStructure.TIM_DeadTime = 50;
//  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
//  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
//  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
//  ADVTIM_BDTRConfig(ADVICE_TIMx, &TIM_BDTRInitStructure);
//
//	ADVTIM_Cmd(ADVICE_TIMx, ENABLE);
//	ADVTIM_CtrlPWMOutputs(ADVICE_TIMx, ENABLE);
//
//	//PC5&PB5 config as BRKIN input function
////	GPIOC->AFR |= 0x00100000;
//	//GPIOB->AFR |= 0x00100000;
//
////
////	RCC->REGLOCK = 0x55AA6699;
////	RCC->IOMUX = 0x5A690000;			//set swdio as gpio
//
//	GPIOD->AFR |= 0x01110000;
//	GPIOA->AFR |= 0x00001110;
//	GPIOC->AFR |= 0x01011000;
//	GPIOD->AFR |= 0x00001100;
//	
//	return ;
}


/** @defgroup test_advtim1_deadtime_break
  * @{ 
  */
void TEST_ADVTIM_DEADTIME_BREAK_DEEPSLEEP_Config(void)
{	
//	ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	ADVTIM_OCInitTypeDef  TIM_OCInitStructure;
//	ADVTIM_BDTRInitTypeDef TIM_BDTRInitStructure;
//
//	ADVTIM1_Reset();
//	ADVTIM1_ReleaseReset();
//	GPIO_Reset();
//	GPIO_ReleaseReset();
//
//	TIM_TimeBaseStructure.TIM_Period=0x01C0;
//	TIM_TimeBaseStructure.TIM_Prescaler= 0;
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
//	ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//
//
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = 0x60;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//	ADVTIM_OC1Init(ADVICE_TIMx, &TIM_OCInitStructure);
//	TIM_OCInitStructure.TIM_Pulse = 0x70;
//	ADVTIM_OC2Init(ADVICE_TIMx, &TIM_OCInitStructure);
//	TIM_OCInitStructure.TIM_Pulse = 0x80;
//	ADVTIM_OC3Init(ADVICE_TIMx, &TIM_OCInitStructure);
//	TIM_OCInitStructure.TIM_Pulse = 0x90;
//	ADVTIM_OC4Init(ADVICE_TIMx, &TIM_OCInitStructure);
//
//
//  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
//  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
//  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
//  TIM_BDTRInitStructure.TIM_DeadTime = 11;
//  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
//  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
//  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
//  ADVTIM_BDTRConfig(ADVICE_TIMx, &TIM_BDTRInitStructure);
//
//	ADVTIM_Cmd(ADVICE_TIMx, ENABLE);
//	ADVTIM_CtrlPWMOutputs(ADVICE_TIMx, ENABLE);
//
//	//PC5&PB5 config as BRKIN input function
////	GPIOC->AFR |= 0x00100000;
//	GPIOB->AFR |= 0x00100000;
//
//	GPIOD->AFR |= 0x01110000;
//	GPIOA->AFR |= 0x00001110;
//	GPIOC->AFR |= 0x11011000;
//	GPIOD->AFR |= 0x00001100;
//
//	DELAYCELL(0xFFF);
//	SYSCTRL->TIM1_CHINMUX |= 1<<21; 	//deep sleep break in enable
//	DeepSleep();
//
//	return ;
}

/** @defgroup test_advtim1_deadtime_break
  * @{ 
  */
void  TEST_ADVTIM_EVENT_GENERATION_Config(void)
{
//		ADVTIM1_Reset();
//		ADVTIM1_ReleaseReset();
//		ADVTIM1->CCER = 0x1111;
//
//		ADVICE_TIMx->DIER = 0xFF;
//		NVIC_EnableIRQ(ADVANCE_TIM_IRQ);
//		ADVTIM_GenerateEvent(ADVICE_TIMx, TIM_EventSource_Update);
//		while(ucIntServedFlag == 0);
//		ucIntServedFlag = 0;
//		ADVTIM_GenerateEvent(ADVICE_TIMx, TIM_EventSource_CC1);
//		while(ucIntCC1Flag == 0);
//		ucIntCC1Flag = 0;
//		ADVTIM_GenerateEvent(ADVICE_TIMx, TIM_EventSource_CC2);
//		while(ADVICE_TIMx == 0);
//		ucIntCC2Flag = 0;
//		ADVTIM_GenerateEvent(ADVICE_TIMx, TIM_EventSource_CC3);
//		while(ucIntCC3Flag == 0);
//		ucIntCC3Flag = 0;
//		ADVTIM_GenerateEvent(ADVICE_TIMx, TIM_EventSource_CC4);
//		while(ucIntCC4Flag == 0);
//		ucIntCC4Flag = 0;
//		ADVTIM_GenerateEvent(ADVICE_TIMx, TIM_EventSource_COM);
//		while(ucIntCOMFlag == 0);
//		ucIntCOMFlag = 0;
//		ADVTIM_GenerateEvent(ADVICE_TIMx, TIM_EventSource_Trigger);
//		while(ucIntTriggerFlag == 0);
//		ucIntTriggerFlag = 0;
//		ADVICE_TIMx->BDTR |= 0xB000;
//		ADVTIM_GenerateEvent(ADVICE_TIMx, TIM_EventSource_Break);
//		while(ucIntBreakFlag == 0);
//		ucIntBreakFlag = 0;
//		return ;
}


/** @defgroup test_advtim1_deadtime_break
  * @{ 
  */
void TEST_ADVTIM_ETR_FUNCTION_Config(void)
{
//		ADVTIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//		ADVTIM1_Reset();
//		ADVTIM1_ReleaseReset();
//		NVIC_EnableIRQ(ADVANCE_TIM_IRQ);
//
//	  /*配置TIM_TimeBaseStructure结构体*/
//		TIM_TimeBaseStructure.TIM_Period=ADVICE_TIM_PERIOD;
//		TIM_TimeBaseStructure.TIM_Prescaler= ADVICE_TIM_PRESCALER;
//		TIM_TimeBaseStructure.TIM_ClockDivision=ADVICE_TIM_CLKDIV;
//		TIM_TimeBaseStructure.TIM_CounterMode=ADVICE_TIM_COUNTERMODE;
//		TIM_TimeBaseStructure.TIM_RepetitionCounter=ADVICE_TIM_REPETITONCOUNTER;
//		ADVTIM_TimeBaseInit(ADVICE_TIMx, &TIM_TimeBaseStructure);
//
//	  //external clock enable
//		ADVICE_TIMx->SMCR |= 1<<14;
//	  ADVTIM_ITConfig(ADVICE_TIMx,TIM_IT_Update,ENABLE);
//		SYSCTRL->TIM1_CHINMUX = ADVTIM_TIM_Channel;
//		ADVTIM_Cmd(ADVICE_TIMx, ENABLE);
//		while(ucIntServedFlag == 0);
//		ucIntServedFlag = 0;
//		return ;
}


/** @defgroup 中断服务子程序
  * @{ 
  */
void ADVANCE_TIM_IRQHandler(void)
 {

	if (ADVTIM_GetITStatus(ADVICE_TIMx, TIM_IT_Update) != RESET) {
		ulIntCntTmp = ADVTIM1->CNT;
		ADVTIM_ClearITPendingBit(ADVICE_TIMx, TIM_FLAG_Update);
		ADVTIM_Cmd(ADVICE_TIMx, DISABLE);
		ADVTIM_ITConfig(ADVICE_TIMx, TIM_IT_Update, DISABLE);
		ucIntServedFlag = 1;
	}

	if (ADVTIM_GetITStatus(ADVICE_TIMx, TIM_IT_CC1) != RESET) {
		ADVTIM_ClearITPendingBit(ADVICE_TIMx, TIM_IT_CC1);
		ucIntCC1Flag = 1;
		CaptureValue = ADVTIM_GetCapture1(ADVICE_TIMx);
		ulFrequencyCH1 = 24000000 / (CaptureValue - ulCaptureCC1Old);
		ulCaptureCC1Old = CaptureValue;

//		  advtim_buffer[cnt++] = ADVTIM_GetCapture1(ADVANCE_TIM);;
//		  ADVTIM_ClearITPendingBit(ADVANCE_TIM, TIM_IT_CC1);
//		  if(cnt == 20)
//			{
//			  cnt = 0;
//        //ADVANCE_TIM->CCER &= ~0x0;
//					/*标志置1*/
//        ucIntCC1Flag = 0x01;
//			}
	} else if (ADVTIM_GetITStatus(ADVICE_TIMx, TIM_IT_CC2) != RESET) {
		ADVTIM_ClearITPendingBit(ADVICE_TIMx, TIM_IT_CC2);
		ucIntCC2Flag = 1;
		CaptureValue = ADVTIM_GetCapture2(ADVICE_TIMx);
		ulFrequencyCH2 = 24000000 / (CaptureValue - ulCaptureCC2Old);
		ulCaptureCC2Old = CaptureValue;
	} else if (ADVTIM_GetITStatus(ADVICE_TIMx, TIM_IT_CC3) != RESET) {
		ADVTIM_ClearITPendingBit(ADVICE_TIMx, TIM_IT_CC3);
		ucIntCC3Flag = 1;
		CaptureValue = ADVTIM_GetCapture3(ADVICE_TIMx);
		ulFrequencyCH3 = 24000000 / (CaptureValue - ulCaptureCC3Old);
		ulCaptureCC3Old = CaptureValue;
	} else if (ADVTIM_GetITStatus(ADVICE_TIMx, TIM_IT_CC4) != RESET) {
		ADVTIM_ClearITPendingBit(ADVICE_TIMx, TIM_IT_CC4);
		ucIntCC4Flag = 1;
		CaptureValue = ADVTIM_GetCapture4(ADVICE_TIMx);
		ulFrequencyCH4 = 24000000 / (CaptureValue - ulCaptureCC4Old);
		ulCaptureCC4Old = CaptureValue;
	}

	if (ADVTIM_GetITStatus(ADVICE_TIMx, TIM_IT_COM) != RESET) {
		ucIntCOMFlag = 1;
		ADVTIM_ClearITPendingBit(ADVICE_TIMx, TIM_IT_COM);
	}

	if (ADVTIM_GetITStatus(ADVICE_TIMx, TIM_IT_Trigger) != RESET) {
		ucIntTriggerFlag = 1;
		ADVTIM_ClearITPendingBit(ADVICE_TIMx, TIM_IT_Trigger);
	}

	if (ADVTIM_GetITStatus(ADVICE_TIMx, TIM_IT_Break) != RESET) {
		ucIntBreakFlag = 1;
		ADVTIM_ClearITPendingBit(ADVICE_TIMx, TIM_IT_Break);
	}

	ADVICE_TIMx->SR &= ~0xFFFF;
}
