/*
 * user_SysClock.c
 *
 *  Created on: 2019年8月12日
 *      Author: Bough_004
 */
#include "user_SysClock.h"
#include "user_clktrim.h"
#include "user_internalFlash.h"
#include "main.h"
void setSystemHIRC(SystemHIRCType type){
	u32 vtRcc_HIRccr_data=0x5A690000;
	u16 vTemp16=0;
	RCC_SysclkCmd(RCC,RCC_SYSCLKSource_HIRC_EN,ENABLE);			//启用HIRC
	//读取出厂时flash中校准过的HIRC值
	switch (type){
	case HIRC_24M:
		vTemp16=readInternalFlashWrod(HIRC_24M_ADDR);
		break;
	case HIRC_22M:
		vTemp16=readInternalFlashWrod(HIRC_22M_ADDR);
		break;
	case HIRC_16M:
		vTemp16=readInternalFlashWrod(HIRC_16M_ADDR);
		break;
	case HIRC_8M:
		vTemp16=readInternalFlashWrod(HIRC_8M_ADDR);
		break;
	case HIRC_4M:
		vTemp16=readInternalFlashWrod(HIRC_4M_ADDR);
		break;
	}
	vTemp16&=0x0FFF;
	vtRcc_HIRccr_data|=vTemp16;
	RCC->REGLOCK =  RCC_REGLOCKKEY;
	RCC->HIRCCR = 	vtRcc_HIRccr_data;							//使用出厂校准过的HIRC值.
	RCC->REGLOCK =  RCC_RESGLOCKKEY;
}
void setSystemLIRC(SystemLIRCType type){
	u32 vtRcc_LIRccr_data=0x5A690000;
	u16 vTemp16=0;
	//读取出厂时flash中校准过的HIRC值
	if(type==LIRC_32K768)
		vTemp16=readInternalFlashWrod(LIRC_32K768_ADDR);
	else
		vTemp16=readInternalFlashWrod(LIRC_38K4_ADDR);
	vTemp16&=0x01FF;
	vtRcc_LIRccr_data|=vTemp16;
	RCC->REGLOCK =  RCC_REGLOCKKEY;
	RCC->LIRCCR = 	vtRcc_LIRccr_data;							//使用出厂校准过的LIRC值.
	RCC->REGLOCK =  RCC_RESGLOCKKEY;
	while(RCC->LIRCCR&0x00001000);							//等待LIRC稳定
}
/*
 * 选择时钟
 */
void systemClkSelect(SystemClkSelectType vtData){
	u32	vTemp32=0x5A690000;
	vTemp32|=vtData;
	RCC->REGLOCK =  RCC_REGLOCKKEY;
	RCC->CLKSEL=vTemp32;
	RCC->REGLOCK =  RCC_RESGLOCKKEY;
}

void systemClkSet(void){
	setSystemHIRC(HIRC_24M);									//设定高速时钟
	setSystemLIRC(LIRC_38K4);									//设定低速时钟
	RCC->REGLOCK =  RCC_REGLOCKKEY;
	RCC->CLKCON  |= 0x5a690085;								//(RCC_SYSCLKCR   启用HIRC和LIRC,并且设定从deep sleep醒来后自动启用并切换HIRC
	RCC->REGLOCK =  RCC_RESGLOCKKEY;

	systemClkSelect(HIRC_SEL);									//选择HIRC
}

