/*
 * communication.h
 *
 *  Created on: 2020年03月09日
 *      Author:  Sky@Bough.com
 */

#ifndef USER_INC_COMMUNICATION_CUSTOMIZE_H_
#define USER_INC_COMMUNICATION_CUSTOMIZE_H_
#include "const.h"
extern	u8 fIsReceiveStart;



#define	MAX_RECEIVE_INDEX	19
#define	COMMUN_TIME_OUT_CONST		16000//11280//约15ms	1.33us/step

#define	ERROR_SYNC_HIGH				7895//10.5	 1.33us/step
#define	CHARGE_SYNC_BIT_HIGH			6917//9.2ms	 1.33us/step
#define	CHARGE_LOW_BIT_HIGH			677	//900us    1.33us/step
#define	CHARGE_HIGH_BIT_HIGH			226	//300us    1.33us/step

#define	CHARGE_LOW_BIT_LOW			226	//300us    1.33us/step
#define	CHARGE_HIGH_BIT_LOW			677	//900us    1.33us/step

#define	MAX_BIT_TIMER			49		//1.3ms
#define	MIN_BIT_TIMER			11		//286us
#define	VALID_BIT_TIMER			30		//780us
#define	MASK_BYTE				0x55

#define	CHARGE_TIME_OUT				5	//5ms*5=25ms
#define	CODE_FULLY_BIT			0X20
#define	CODE_CHARGING_BIT		0X40
#define	CODE_SYNC_BIT			0X80


//#define	COMM_CODE_ONOFF		0XC0
//#define	COMM_CODE_15MIN		0X30
//#define	COMM_CODE_30MIN		0X0C
//#define	COMM_CODE_60MIN		0X03
//#define	COMM_CODE_ONOFF			0X80
//#define	COMM_CODE_15MIN			0X20
//#define	COMM_CODE_30MIN			0X10
//#define	COMM_CODE_60MIN			0X40
#define	COMM_CODE_ONOFF			0X01
#define	COMM_CODE_15MIN			0X02
#define	COMM_CODE_30MIN			0X04
#define	COMM_CODE_60MIN			0X08
#define	COMM_PAIRING_CODE		0X0F
#define	COMM_PAIRED_CODE			0XF0
#define	COMM_PAIRED_FAIL_CODE		0XFF

#define	Pairing_code					0x30
#define	Paired_code					0x31
#define	Paired_fail					0x32

#define	SERIES_TIME_CONST		10		//5*10ms

extern	u8	vSkipCommKeyTimer;

typedef enum{
	invalidResult=0,
	validResultBuff=1
}ChgRecResult;

typedef struct{
	UINT8  	fReceivedResult;
	UINT8  	vReceivedData;
	UINT8	vFirstRecData;
}ChgReceiveStts;

typedef enum{
	NoSignal=0,
//	SyncLowStart=1,
	SyncLowGot=2,
	SyncHiGot=3,
	SyncCodeGot=4
}ChgSyscStts;

typedef struct{
	ChgSyscStts  vSyncCodeStts;
	UINT16	vHiStartTimer;
	UINT16	vLowStartTimer;
	UINT16	vHiLastTimer;
	UINT16	vLowLastTimer;
	UINT8	vCommBitCnt;
	UINT8	vReceiveTemp;
	UINT8	fIsFirstHiGot;
	UINT8	vRecByteCnt;
}ChgRecevingParams;

extern	void	 deinitComm(void);
extern	void  dataReceiveFunc(void);
extern	void	 dataReceivedProcess(void);
#endif /* USER_INC_COMMUNICATION_CUSTOMIZE_H_ */
