#include "user_adc.h"
#include "const.h"
#include "misc.h"
#include "user_menu.h"
#include "io_define.h"
#include "user_lightEffect.h"
#include "user_tone.h"
//volatile UINT16  vTempThreshold;								//存储温度阈值对应的AD值
//volatile UINT16  vTempThresholdHi;						//存储马达温度停止阈值对应的AD值
//volatile UINT16  vTempThresholdLow;						//存储马达温度启动阈值对应的AD值
//volatile UINT16  vVoltThresholdHi;								//存储AC电压阈值上限对应的AD值
//volatile UINT16  vWorkingVoltThresholdLow;						//存储AC电压阈值下限(马达已经启动情况下)对应的AD值
//volatile UINT16  vVoltThresholdLow;								//存储AC电压阈值下限(马达未启动情况下)对应的AD值
UINT16		vTempThreshold;					//TEMPERATURE_70C_VOLT=726即0.726v,  vTempThreshold为0.726v对应的AD值
UINT16		vTempThresholdHi;
UINT16		vTempThresholdLow;
UINT16		vVoltThresholdHi;					//240v AC电压所对应的的AD检测口的AD值
UINT16		vVoltThresholdLow;				//185v AC电压所对应的的AD检测口的AD值
//UINT16		vWorkingVoltThresholdLow;			//185v AC电压所对应的的AD检测口的AD值
/********************************************************************************************************
 * 根据开启的通道把对应的IO复用模式 改为ADC模式
 *********************************************************************************************************/
void ADCPinAFSet(u8 vtADCChls){
	if(vtADCChls&((u8)ADC_Channel0_ENABLE))
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,ADC_AF_VALUE); 		//AIN0 PC6
	if(vtADCChls&((u8)ADC_Channel1_ENABLE))
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource3,ADC_AF_VALUE); 		//AIN1 PC3
	if(vtADCChls&((u8)ADC_Channel2_ENABLE))
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource4,ADC_AF_VALUE); 		//AIN2 PC4
	if(vtADCChls&((u8)ADC_Channel3_ENABLE))
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,ADC_AF_VALUE); 	//AIN3 PD2
	if(vtADCChls&((u8)ADC_Channel4_ENABLE))
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource3,ADC_AF_VALUE); 	//AIN4 PD3
	if(vtADCChls&((u8)ADC_Channel5_ENABLE))
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,ADC_AF_VALUE); 	//AIN5 PD5
	if(vtADCChls&((u8)ADC_Channel6_ENABLE))
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,ADC_AF_VALUE); 	//AIN6 PD6
}

void ADC_SignalMode_Config(u8 vtADCChl){
	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	u16 channelSel;
	assert_param(	IS_ADC_CHANNEL_CMD(vtADCChl));
	channelSel=adcChlCMD2adcAdcChl(vtADCChl);
	/*初始化ADC通信结构体*/
	ADC_CommonInitStruct.ADC_CircleMode = _ADC_CIRCLEMODE;					//ADC 非循环模式    0/1:非循环/循环模式
	ADC_CommonInitStruct.ADC_CtMode = ADC_Ct_Single;							//ADC_CR1.CT 设置为单次转换    0/1:单次转换/连续转换		//连续转换为依次从AIN0~AIN7
	ADC_CommonInitStruct.ADC_SetAdcCnt = _ADC_SETADCCNT_SIGNAL;				//连续转换次数 15次 ,结果不累加,结果为最后次的值
	ADC_CommonInitStruct.ADC_Trigs0Sel = _ADC_TRIGS0SEL;						//TRIGS0[4:0]	禁止自动触发ADC转换0
	ADC_CommonInitStruct.ADC_Trigs1Sel = _ADC_TRIGS1SEL;						//TRIGS1[4:0]	禁止自动触发ADC转换1

	/*初始化ADC结构体*/
	ADC_InitStruct.ADC_ChannelSel = channelSel;									//设置ADC channel
	if((vtADCChl==ADC_TEMP_CHL)||(ADC_VOLT_CHL==vtADCChl)){
		ADC_InitStruct.ADC_ClkSel = ADC_Prescaler_Div16;                                      		//设置ADC时钟分频	为16
		ADC_InitStruct.ADC_SamSel = ADC_SAMPLE_16CYCLE;						//ADC 采样周期选择
	}else{
		ADC_InitStruct.ADC_ClkSel = ADC_Prescaler_Div1;                                      		//设置ADC时钟分频	为0
		ADC_InitStruct.ADC_SamSel = ADC_SAMPLE_16CYCLE;						//ADC 采样周期选择
	}
	/*初始化ADC*/
	ADC_Init(DEBUG_ADCx, &ADC_InitStruct);
	ADC_CommonInit(DEBUG_ADCx,&ADC_CommonInitStruct);

	/*GPIO 管脚复用配置*/
	ADCPinAFSet(vtADCChl);

	ADC_ITCmd(DEBUG_ADCx, vtADCChl, ADC_IT_STATE);

	// 开启ADC ，
	ADC_Cmd(DEBUG_ADCx, ENABLE);
//	//开始单次转换							改成函数由外部开启转换
//	ADC_SoftwareStartConv(DEBUG_ADCx);

}


/*****************************************************************************
  * @brief  配置ADC工作模式
  * @param  无
  * @retval 无
  */
void ADC_MutiMode_Config(u8 vtADCChls)
{
	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
//	vtADCChls=0x7f;					// AIN0~6开启
	/*初始化ADC通信结构体*/
	ADC_CommonInitStruct.ADC_CircleMode = _ADC_CIRCLEMODE;		//ADC 非循环模式    0/1:非循环/循环模式
	ADC_CommonInitStruct.ADC_CtMode = _ADC_CTMODE;				//ADC_CR1.CT 设置为连续转换    0/1:单次转换/连续转换		//连续转换为依次从AIN0~AIN7
	ADC_CommonInitStruct.ADC_SetAdcCnt = _ADC_SETADCCNT;			//连续转换次数16次		(并非累加, 8个通道(如果都激活总计转换16次,每个通道平均2次) 结果中是每个通道最后一次的值)
	ADC_CommonInitStruct.ADC_Trigs0Sel = _ADC_TRIGS0SEL;			//TRIGS0[4:0]	禁止自动触发ADC转换0
	ADC_CommonInitStruct.ADC_Trigs1Sel = _ADC_TRIGS1SEL;			//TRIGS1[4:0]	禁止自动触发ADC转换1
	
	/*初始化ADC结构体*/
	ADC_InitStruct.ADC_ChannelSel = _ADC_ChannelSel;					//设置ADC channel 0
	ADC_InitStruct.ADC_ClkSel = _ADC_CLKSEL;						//设置ADC时钟分频	为0
	ADC_InitStruct.ADC_SamSel = _ADC_SAMSEL;						//ADC 采样周期选择
	/*初始化ADC*/
	ADC_Init(DEBUG_ADCx, &ADC_InitStruct);
	ADC_CommonInit(DEBUG_ADCx,&ADC_CommonInitStruct);
	
	/*GPIO 管脚复用配置*/

	ADCPinAFSet(vtADCChls);
	ADC_ClearFlag(DEBUG_ADCx, vtADCChls);								//ADC_INTCLR ADC 中断清除寄存器

	ADC_ContinuousConverRstCmd(DEBUG_ADCx,ENABLE);
	ADC_ContinuousConverRstCmd(DEBUG_ADCx,DISABLE);
	
	ADC_ContinuousConverChannelCmd(ADC,vtADCChls, ENABLE);
		
	// 开启ADC ，并开始转换
	ADC_Cmd(DEBUG_ADCx, ENABLE);
}

//void ADC_NVIC_Config(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//	// 优先级分组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//
//	// 配置中断优先级
// 	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_ADC_IRQ;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init(&NVIC_InitStructure);
//}
/****************************************************************************************************************
 *  转换各个已在形参结构体中定义的channel的值,
 *
 * 获取结果通过调用readADCResultFromMutiChls(ADCChlDefType ch)实现
 * 	调用范例
 * 	userAdcStruct.channels=(u8)ADC_NTC_CHL|ADC_MOTOR_CHL|ADC_BATTDET_CHL|ADC_5V_CHL;
* 	mutiChannesADC(&userAdcStruct);
* 	vDaValue=readADCResultFromMutiChls(ADC_MOTOR_CHL);
* 	vDaVolt=vDaValue*vD2A_Coe;
 *****************************************************************************************************************/
void mutiChannesADC(UserADCTypeDef *adcStruct){
		ADC_MutiMode_Config(adcStruct->channels);
		ADC_SoftwareStartConv(DEBUG_ADCx);
		while(ADC_GetRISFlagStatus(DEBUG_ADCx, ADC_TICONT_FLAG) == RESET);
		adcStruct->DaValues[0]=DEBUG_ADCx->RESULT0;
		adcStruct->DaValues[1]=DEBUG_ADCx->RESULT1;
		adcStruct->DaValues[2]=DEBUG_ADCx->RESULT2;
		adcStruct->DaValues[3]=DEBUG_ADCx->RESULT3;
		adcStruct->DaValues[4]=DEBUG_ADCx->RESULT4;
		adcStruct->DaValues[5]=DEBUG_ADCx->RESULT5;
		adcStruct->DaValues[6]=DEBUG_ADCx->RESULT6;
		adcStruct->DaValues[7]=DEBUG_ADCx->RESULT7;
		// 关闭ADC
		ADC_Cmd(DEBUG_ADCx, DISABLE);
}
/****************************************************************************************************************
 *  转换指定通道的ADC结果并返回,
 *
 * 实参取值范围见  IS_ADC_CHANNEL_CMD
 *****************************************************************************************************************/
u16 getSignalChlADC(u8 channel){
		u8 i=8;				//转换9次
		u32 vtMin=0xffff;
		u32 vtMax=0;
		u32 vtTemp;
		u32 vResultACC=0;
		assert_param(	IS_ADC_CHANNEL_CMD(channel));
		ADC_SignalMode_Config(channel);
		//clr_FlashLED;
		do{
		//开始单次转换

		ADC_SoftwareStartConv(DEBUG_ADCx);
		while(ADC_GetSoftwareStartConvStatus(DEBUG_ADCx) == SET);			//等待单次转换完成

			if(i--<8){			//丢弃  第1,2次的数据
				vtTemp=ADC_GetConversionValue(DEBUG_ADCx);
				if(vtTemp<=vtMin){
					vtMin=vtTemp;
				}
				if(vtTemp>=vtMax){
					vtMax=vtTemp;
				}
				vResultACC+=vtTemp;
			}
		}while(i);
		// 关闭ADC
		ADC_Cmd(DEBUG_ADCx, DISABLE);					//关闭ADC模块
		vResultACC-=vtMin;		//去除一次最小值
		vResultACC-=vtMax;		//去除一次最大值
		//set_FlashLED;
		return	vResultACC/5;
}
/****************************************************************************************************************
 *
 *  IS_ADC_CHANNEL_CMD  格式转换成  ADC通道编号
 *
 *****************************************************************************************************************/
u8 adcChlCMD2adcIndex(u32 chlCMD){
	u8 i=0;
	assert_param(	IS_ADC_CHANNEL_CMD(chlCMD));
	do{
		if(chlCMD&0x01)
			break;
		chlCMD>>=1;
		i++;
	}while(i<8);
	return i;
}
/****************************************************************************************************************
 *
 *  IS_ADC_CHANNEL_CMD  格式转换成  IS_ADC_CHANNEL
 *
 *****************************************************************************************************************/
u32 adcChlCMD2adcAdcChl(u32 chlCMD){
	u32 vtAdcChl=adcChlCMD2adcIndex(chlCMD);
	vtAdcChl<<=8;
	return vtAdcChl;
}
/********************************************************
 *
 * 获取多通道转换后指定通道的数据
 *
 * * 	调用范例
 * 	userAdcStruct.channels=(u8)ADC_NTC_CHL|ADC_MOTOR_CHL|ADC_BATTDET_CHL|ADC_5V_CHL;
 * 	mutiChannesADC(&userAdcStruct);
 * 	vDaValue=readADCResultFromMutiChls(ADC_MOTOR_CHL);
 * 	vDaVolt=vDaValue*vD2A_Coe;
 *********************************************************/
//u16 readADCResultFromMutiChls(ADCChlDefType ch){
//	return userAdcStruct.DaValues[ch];
//}
u16 readADCResultFromMutiChls(u8 ch){
	u8 i=0;
	assert_param(	IS_ADC_CHANNEL_CMD(chlCMD));
	i=adcChlCMD2adcIndex(ch);
	return userAdcStruct.DaValues[i];
}
/*************************************
 * 异常处理
 **************************************/
returnStatus exception(systemErrorEnum exc){
	UV_PowerOff;
	uvParams.vTimeToTurnUV=STARTUP_TIMER;		//恢复后,从15秒倒计时开始
	fIsTurnOffByException=TRUE;
	if(exc==vSystemStts){
		return SYSTEM_ERROR;
	}
	if((OVER_VOLTAGE==exc)||(UNDER_VOLTAGE==exc)){

		setVoltErrorLed();

	}else if(SystemHot==exc){

		setHotLed();

	}
	vSystemStts = exc;
	return SYSTEM_ERROR;
}

void	 adcThresholdGenerate(void){
	vTempThreshold=(u16)TEMPERATURE_70C_VOLT/(vD2A_Coe*1000);		//TEMPERATURE_70C_VOLT=726即0.726v,  vTempThreshold为0.726v对应的AD值
	vTempThresholdHi=(u16)TEMPERATURE_75C_VOLT/(vD2A_Coe*1000);
	vTempThresholdLow=(u16)TEMPERATURE_60C_VOLT/(vD2A_Coe*1000);
//	vVoltThresholdHi=(u16)VOLT_AC240V/(vD2A_Coe*1000);					//240v AC电压所对应的的AD检测口的AD值
//	vVoltThresholdLow=(u16)VOLT_AC185V/(vD2A_Coe*1000);				//185v AC电压所对应的的AD检测口的AD值
//	vWorkingVoltThresholdLow=(u16)VOLT_AC160V/(vD2A_Coe*1000);		//185v AC电压所对应的的AD检测口的AD值
}


/***********************************************************************
 *
 * 	get  system  temperature
 *
 ************************************************************************/
float getSystemperature(float vdd) {
	u16	vDaValue=0;
	//fIsSystemTempGot = 1;
	vDaValue=getSignalChlADC(ADC_TEMP_CHL);
	return ((vDaValue*vdd)/ADC_CONST);
}

returnStatus vSystemErrorCheck(void){
	float vtSystemTemperature=0;
	float vtSystemVdd=0;
	if (uvParams.fIsUVFuncOn&&!vBreakVoltDectCnt) {
		vtSystemVdd=getBattVolt();
		vtSystemTemperature=getSystemperature(vtSystemVdd);
		vtSystemTemperature=(vtSystemTemperature/vtSystemVdd)*SYSTEM_VCAP_VOLT;			//折算成用Vcap分压的模式

		if (vtSystemTemperature <= TEMPERATURE_75C_VOLT) {		//马达冷启动时,温度低于75度才能启动
			return exception(SystemHot);
		}
		if(SystemHot==vSystemStts){				//已经处于高温状态
			if (vtSystemTemperature >= TEMPERATURE_60C_VOLT){	//温度低于60度,则回复工作
				if(fIsTurnOffByException){
					genConfrimTone();
				}
				chkSystemResume();
				return SYSTEM_OK;
			}
		}
//		if ((powerValue >= vVoltThresholdHi)) {	//如果ADC值大于4.10v对应的电压或小于1.10对应的电压
//			return exception(OVER_VOLTAGE);
//		} else if (powerValue <= vVoltThresholdLow) {
//				return exception(UNDER_VOLTAGE);
//		}

		if(fIsTurnOffByException){
			genConfrimTone();
		}
		chkSystemResume();
	}
	return SYSTEM_OK;
}

/*********************************************END OF FILE**********************/
