#include "user_uart.h"
#include "user_menu.h"
#include "user_ddl.h"
#include "misc.h"
#include "stdio.h"
#include "user_exti.h"

extern	u16 vTime1msCnt;
uint8_t UART_RX_BUF[UART_BUFFER_SIZE]={0};    /*<interrupt recive data buffer*/
uint8_t UART_ACK_BUF[UART_ACK_BUFFER_SIZE]={0};    /*<interrupt recive data buffer*/
uint8_t FlagState = 0;  /*<interrupt recive data flag*/
//uint8_t RxCounter = 0;
u16	vUartRecevieOverCnt;
u8	fIsUartReceiving=FALSE;
u8	fIsUartStartRecevingValidData=FALSE;
u8	fIsMasterWritCmd=FALSE;					//是否是来自主控的写入命令
u8	vUartReceivedLength=0;
u8	fIsUartSending=FALSE;
u8	vUartSentLength=0;
UARTCommandStruct  uartCMDStruct;
u8	SendState=0;
u8	fIsHeaderSent=FALSE;
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
  NVIC_InitStructure.NVIC_IRQChannel = UART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
  userNVICPrioirySetting(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void UART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	UART_InitTypeDef UART_InitStructure;

	//将USART Rx的GPIO配置为推挽复用模式
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = UART_RX_GPIO_PIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(UART_RX_GPIO_PORT,&GPIO_InitStruct);


	//将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = UART_RX_GPIO_PIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(UART_TX_GPIO_PORT,&GPIO_InitStruct);


	  //uart GPIO管脚配置
	GPIO_PinAFConfig(UART_RX_GPIO_PORT,UART_RX_PIN_SOURCE,UART_RX_AF_VALUE); //RX
	GPIO_PinAFConfig(UART_TX_GPIO_PORT,UART_TX_PIN_SOURCE,UART_TX_AF_VALUE); //TX


	// 配置串口的工作参数
	// 配置波特率
	UART_InitStructure.UART_BaudRate = UART_BAUDRATE;
	// 配置 针数据字长
	UART_InitStructure.UART_BaudRateDbaud_Enable = ENABLE;
	// 配置停止位
	UART_InitStructure.UART_BaudRateTimer_Selected = DISABLE;
	// 配置校验位
	UART_InitStructure.UART_Mode = UART_MODE1 ;

	// 完成串口的初始化配置
	UART_Init(UART0,TIMx, &UART_InitStructure);

	// 串口中断优先级配置
	NVIC_Configuration();


	// 使能串口中断*/
	UART_ITConfig(UART0,UART_RIEN_EABLE,ENABLE);
	UART_ITConfig(UART0,UART_TIEN_EABLE,ENABLE);


	// 使能串口
	UART_Cmd(UART0,UART_RXEN_EABLE,ENABLE);
}

///*****************  发送一个字节 **********************/
//void Uart_SendByte( UART_TypeDef * pUSARTx, uint8_t ch)
//{
//	/* 发送一个字节数据到USART */
//	UART_SendData(pUSARTx,ch);
//	while(FlagState != 0x01);
//	FlagState = 0x00;
//}

///****************** 发送8位的数组 ************************/
//void Uart_SendArray( UART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
//{
//  uint8_t i;
//
//	for(i=0; i<num; i++)
//  {
//	    /* 发送一个字节数据到USART */
//	    Uart_SendByte(pUSARTx,array[i]);
//
//  }
//
//}
///*****************  发送一个16位数 **********************/
//void Uart_SendHalfWord( UART_TypeDef * pUSARTx, uint16_t ch)
//{
//	uint8_t temp_h, temp_l;
//
//	/* 取出高八位 */
//	temp_h = (ch&0XFF00)>>8;
//	/* 取出低八位 */
//	temp_l = ch&0XFF;
//
//	/* 发送高八位 */
//	UART_SendData(pUSARTx,temp_h);
//	//while (UART_GetITStatus(pUSARTx, UART_ISR_TI) == RESET);
//	while(FlagState != 0x01);
//	FlagState = 0x00;
//
//	/* 发送低八位 */
//	UART_SendData(pUSARTx,temp_l);
//	//while (UART_GetITStatus(pUSARTx, UART_ISR_TI) == RESET);
//	while(FlagState != 0x01);
//	FlagState = 0x00;
//}

//
///*****************  发送字符串 **********************/
//void Uart_SendString( UART_TypeDef * pUSARTx, unsigned char *str)
//{
//	unsigned int k=0;
//  do
//  {
//      Uart_SendByte( pUSARTx, *(str + k) );
//      k++;
//  } while(*(str + k)!='\0');
//
//}
//
//
/////重定向c库函数printf到串口，重定向后可使用printf函数
//int fputc(int ch, FILE *f)
// {
//	/* 发送一个字节数据到串口 */
//	UART_SendData(UART0, (uint8_t) ch);
//	while (FlagState != 0x01);
//	FlagState = 0x00;
//	return (ch);
//}
//
////重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//int fgetc(FILE *f)
// {
//	/* 等待串口输入数据 */
//	while (FlagState != 0x01)
//		;
//	FlagState = 0x00;
//	return (int) UART_ReceiveData(UART0);
//}

///*****************  发送字符串 **********************/
void Uart_SendString( UART_TypeDef * pUSARTx, unsigned char *str,UINT8 len)
{
	unsigned int k=0;
  do
  {
      Uart_SendByte( pUSARTx, *(str + k) );
      k++;
//  } while(*(str + k)!='\0');
  } while(k<len);

}

/*****************  发送一个字节 **********************/
void Uart_SendByte( UART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	SendState = 0x01;
	UART_SendData(pUSARTx,ch);
//	while(SendState == 0x01);
}


void resetUartRecTimer(void){
	vUartRecevieOverCnt=10000-vTime1msCnt;		//vTime1msCnt上限是:10000,即10s
}
void uartReceivedDataProcess(void) {
	u8 vtParseIndex = 0;
	u8 vtLpIndex = 0;
	u16 vtFlag = 0;
	u8 vtLength = 0;
	u8 vtChksum = 0;
	if (fIsUartReceiving) {
		vtLength = UART_RX_BUF[0];
		if( ((vUartRecevieOverCnt + vTime1msCnt - 10000) > UART_TIME_OUT_CONST)||(vtLength&&(vUartReceivedLength==vtLength))) {
			fIsUartReceiving = 0;
			if (fIsUartStartRecevingValidData) {
				fIsUartStartRecevingValidData = FALSE;
				vtParseIndex = 0;
				vtFlag = 0;
				if ((vtLength == vUartReceivedLength) && (vUartReceivedLength >= UART_CMD_MIN_LEN)) {	//长度正确
					for (vtLpIndex = 0; vtLpIndex < vtLength; vtLpIndex++) {
						vtChksum ^= UART_RX_BUF[vtLpIndex];
					}
					if (!vtChksum) {	//校验位正确,有效数据
						DDL_ZERO_STRUCT(uartCMDStruct);
						if (fIsMasterWritCmd) {									//来自主控的写入命令
							uartCMDStruct.fIsMasterWrite=TRUE;
							vtParseIndex = 1;
							vtFlag = UART_RX_BUF[vtParseIndex++];
							vtFlag <<= 8;
							vtFlag |= UART_RX_BUF[vtParseIndex++];
							uartCMDStruct.flag = vtFlag;
							for (vtLpIndex = 0; vtLpIndex < 16; vtLpIndex++) {
								if ((vtFlag >> vtLpIndex) & 0x01) {
									switch (vtLpIndex) {
									case BIT_CMD:
										uartCMDStruct.cmd = UART_RX_BUF[vtParseIndex++];
										break;
									case BIT_MODE:
										uartCMDStruct.preinstallEffectNo = UART_RX_BUF[vtParseIndex++];
										break;
									case BIT_BRIGHTNESS:
										uartCMDStruct.brightness = UART_RX_BUF[vtParseIndex++];
										break;
									case BIT_COLOR_TEMPERTURE:
										uartCMDStruct.colorTemperature = UART_RX_BUF[vtParseIndex++];
										break;
									case BIT_HUES:
										uartCMDStruct.hues = UART_RX_BUF[vtParseIndex++];
										uartCMDStruct.hues <<= 8;
										uartCMDStruct.hues |= UART_RX_BUF[vtParseIndex++];
										break;
									case BIT_SATURATION:
										uartCMDStruct.saturation = UART_RX_BUF[vtParseIndex++];
										break;
									case BIT_CUSTOMIZE_EFFECT_MODE:
										uartCMDStruct.customizeEffectMode = UART_RX_BUF[vtParseIndex++];
										break;
									case BIT_CUSTOMIZE_EFFECT_TIMES:
										uartCMDStruct.customizeEffectTimes = UART_RX_BUF[vtParseIndex++];
										break;
									case BIT_CUSTOMIZE_EFFECT_FREQ:
										uartCMDStruct.customizeEffectFreq = UART_RX_BUF[vtParseIndex++];
										break;
									}
								}
							}
						}else{												//来自主控的读取命令
								uartCMDStruct.fIsMasterWrite=FALSE;
								uartCMDStruct.cmd = UART_RX_BUF[01];
						}
						fIsNewCMDGod = 1;
					}
				}
			}
		}
	}
}

void uartSendDataProcess(void) {
	if (fIsUartSending) {
		if (!SendState) {				//TX通道空闲状态,则继续发送
			if (uartCMDStruct.fIsMasterWrite) {	//转发来自主控的控制命令
				if (!fIsHeaderSent) {
					Uart_SendByte( UART0, UART_ACK_BYTE);
					fIsHeaderSent = TRUE;
				} else {
					if (!fIsUartReceiving) {
						if (vUartSentLength >= vUartReceivedLength) {
							fIsUartSending = FALSE;
							vUartSentLength = 0;//转发结束
							fIsHeaderSent = FALSE;
						} else {
							Uart_SendByte( UART0, UART_RX_BUF[vUartSentLength++]);
						}
					} else {		//UART 接收未完成
						if (vUartSentLength < vUartReceivedLength) {
							Uart_SendByte( UART0, UART_RX_BUF[vUartSentLength++]);
						}
					}
				}
			} else {				//回复来自主控的读取命令
				if (!fIsHeaderSent) {
					Uart_SendByte( UART0, UART_READ_START_BYTE);
					fIsHeaderSent = TRUE;
				} else {

					if (vUartSentLength < UART_ACK_BUF[0]) {
						Uart_SendByte( UART0, UART_ACK_BUF[vUartSentLength++]);
					} else {
						fIsUartSending = FALSE;
						vUartSentLength = 0;	//转发结束
						fIsHeaderSent = FALSE;
						//uartCMDStruct.fIsMasterWrite=FALSE;
					}
				}
			}
		}
	}
}

//串口中断子程序1
void UART_IRQHandler(void)
 {
	u8	vtRecByte=0;
	if ((UART0->ISR & UART_ISR_TI) == UART_ISR_TI) {
		UART0->ICR |= UART_ICR_TI;
		SendState = 0x00;
	} else if ((UART0->ISR & UART_ISR_RI) == UART_ISR_RI) {
		UART0->ICR |= UART_ICR_RI;
		if(!fIsUartReceiving){
			fIsUartReceiving=TRUE;
			vUartReceivedLength=0;
		}
		vtRecByte=UART_ReceiveData( UART0);
		if(!fIsUartStartRecevingValidData){
				vUartReceivedLength=0;						//0xAA 为有效数据帧的起始Byte
			if(UART_START_BYTE==vtRecByte){
				fIsUartStartRecevingValidData=TRUE;
				fIsMasterWritCmd=TRUE;						//主控写入
				fIsUartSending=TRUE;							//有效数据,UART开始转发
				uartCMDStruct.fIsMasterWrite=TRUE;
			}else if(UART_READ_START_BYTE==vtRecByte){
				fIsUartStartRecevingValidData=TRUE;
				fIsMasterWritCmd=FALSE;						//主控读取命令
			}
		}else{
				UART_RX_BUF[vUartReceivedLength++]=vtRecByte;
		}
		if(vUartReceivedLength>=UART_BUFFER_SIZE){
			vUartReceivedLength=0;							//error data
		}
		resetUartRecTimer();
		FlagState = 0x01;
	} else {
		;
	}
}





