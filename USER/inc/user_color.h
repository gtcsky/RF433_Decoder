/*
 * user_color.h
 *
 *  Created on: 2019-11-20
 *      Author: Bough_004
 */

#ifndef USER_INC_USER_COLOR_H_
#define USER_INC_USER_COLOR_H_
#include "const.h"

extern	void	 setCoolDuty(float duty);
extern	void	 PwmCh3Default(void);
extern	void	 setCoolData(u16 pwmData);
extern	void	 setWarmDuty(float duty);
extern	void	 setWarmData(u16 pwmData);
extern	void	 setBlueData(u16 pwmData);
extern	void	 setGreenData(u16 pwmData);
extern	void	 setRedData(u16 pwmData);
#endif /* USER_INC_USER_COLOR_H_ */
