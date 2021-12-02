/*
 * communication.h
 *
 *  Created on: 2020年03月09日
 *      Author:  Sky@Bough.com
 */

#ifndef USER_INC_COMMUNICATION_H_
#define USER_INC_COMMUNICATION_H_
#include "const.h"
extern	u8 fIsReceiveStart;


//SYNC 10.6MS
//HI Bit   : 1.080ms HI+376 us Low
//Low Bit:  340 us HI+1.080ms Low


#define	MAX_RECEIVE_INDEX	19
#define	COMMUN_TIME_OUT_CONST	120000	//120000/24M=5ms

#define	SYNC_LOW_9MS				6818	//step 1.33us

#define	NEG_LPT_CNT					0x3F	//(u8)_LPTIMER_IT_LOADVALUE
#define	CHARGE_SYNC_BIT_HIGH			123	//100CLK=3.2ms      3200/26.05=123	(Lptimer step=26.05us)
#define	CHARGE_LOW_BIT_HIGH			10	//10CLK=256us      256/26.05=10	(Lptimer step=26.05us)
#define	CHARGE_HIGH_BIT_HIGH			1	//2CLK=64us      64/26.05=2	(Lptimer step=26.05us)

#define	CHARGE_LOW_BIT_LOW			1	//2CLK=64us      64/26.05=2	(Lptimer step=26.05us)
#define	CHARGE_HIGH_BIT_LOW			10	//10CLK=256us      256/26.05=10	(Lptimer step=26.05us)

#define	MAX_BIT_TIMER			49		//1.3ms   (Lptimer step=26.05us)
#define	MIN_BIT_TIMER			11		//286us   (Lptimer step=26.05us)
#define	VALID_BIT_TIMER		30		//780us
#define	MASK_BYTE				0x55

#define	CHARGE_TIME_OUT				100	//5ms*100=500ms
#define	CODE_FULLY_BIT			0X20
#define	CODE_CHARGING_BIT		0X40
#define	CODE_SYNC_BIT			0X80


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


#define	SERIES_TIME_CONST		30//15		//5*10ms

#define	SECURITY_KEY_1			0
#define	SECURITY_KEY_2			1
#define	SECURITY_KEY_3			2

extern	u8	vSkipCommKeyTimer;

typedef enum{
	invalidResult=0,
	validResultBuff=1
}ChgRecResult;

typedef struct{
	UINT8  	fReceivedResult;
	UINT8  	vReceivedData[5];
	UINT8	fIsNotFirstReceived;
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
	UINT8	vHiStartTimer;
	UINT8	vLowStartTimer;
	UINT8	vHiLastTimer;
	UINT8	vLowLastTimer;
	UINT8	vCommBitCnt;
	UINT8	vReceiveTemp;
	UINT8	fIsFirstHiGot;
	UINT8	vRecByteCnt;
}ChgRecevingParams;

extern	void	 deinitComm(void);
extern	void  dataReceiveFunc(void);
extern	void	 dataReceivedProcess(void);
#endif /* USER_INC_COMMUNICATION_H_ */
