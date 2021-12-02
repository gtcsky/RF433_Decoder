/*
 * user_ddl.c
 *
 *  Created on: 2019Äê11ÔÂ20ÈÕ
 *      Author: Bough_004
 */

#include "user_ddl.h"
#include  "stdio.h"

/*******************************************************************************
 ** \brief Memory clear function for DDL_ZERO_STRUCT()
 ******************************************************************************/
void ddl_memclr(void *pu8Address, u32 u32Count)
{
    u8 *pu8Addr = (u8 *)pu8Address;

    if(NULL == pu8Addr)
    {
        return;
    }

    while (u32Count--)
    {
        *pu8Addr++ = 0;
    }
}

void	delay100us(UINT16 cnt){
	u16	vtSimpleLoop=230;//240;
	u16 i=0,l=0;
	for(;i<cnt;i++){
		for(l=0;l<vtSimpleLoop;l++);
	}
}
