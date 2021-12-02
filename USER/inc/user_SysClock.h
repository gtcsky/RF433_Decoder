/*
 * user_SysClock.h
 *
 *  Created on: 2019-08-12
 *      Author: Bough_004
 */

#ifndef USER_INC_USER_SYSCLOCK_H_
#define USER_INC_USER_SYSCLOCK_H_
#include "const.h"

void setSystemHIRC(SystemHIRCType type);
void systemClkSet(void);
void systemClkSelect(SystemClkSelectType vtData);
#endif /* USER_INC_USER_SYSCLOCK_H_ */
