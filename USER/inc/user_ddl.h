/*
 * user_ddl.h
 *
 *  Created on: 2019-11-20
 *      Author: Bough_004
 */
#ifndef USER_INC_USER_DDL_H_
#define USER_INC_USER_DDL_H_
#include "const.h"

extern	void	delay100us(UINT16 cnt);
void ddl_memclr(void *pu8Address, u32 u32Count);
#define DDL_ZERO_STRUCT(x)          ddl_memclr((uint8_t*)&(x), (u32)(sizeof(x)))
#endif /* USER_INC_USER_DDL_H_ */
