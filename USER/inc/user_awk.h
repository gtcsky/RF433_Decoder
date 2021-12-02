#ifndef __TEST_WWDG_H
#define	__TEST_WWDG_H


#include "cx32l003_awk.h"
#include "misc.h"

// AWK 参数设置
#define 	DEBUG_AWK                   				AWK
#define 	DEBUG_AWK_XTLPRSC           			0xBC
#define 	DEBUG_AWK_SELETECLKSOURCE   		0x01
#define 	AWK_COUNTERCLKDIV     				0x0F

#define   AWK_VALUE             					0X100-255		//255*1.706=435s
#define   DEBUG_AWK_CMD               			ENABLE

#define  DEBUG_AWK_IRQ                				AWK_IRQn
#define  DEBUG_AWK_IRQHandler         			AWK_IRQHandler


//define function
void AWK_Config(void);
void AWK_Feed(void);

#endif /* __BSP_WWDG_H */
