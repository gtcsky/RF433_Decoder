/*
 * user_internalFlash.h
 *
 *  Created on: 2019-08-12
 *      Author: Bough_004
 */

#ifndef USER_INC_USER_INTERNALFLASH_H_
#define USER_INC_USER_INTERNALFLASH_H_
#include "const.h"
#include "misc.h"
#include "cx32l003_flash.h"

u32 readInternalFlashData(u32 Address);
u16 readInternalFlashWrod(u32 Address);
u8 readInternalFlashByte(u32 Address);

#define	MAX_SECURITY_CODE_INDEX	3
#define	NEW_FLASH_CODE	0x5A

typedef struct{
	UINT8	security_code[MAX_SECURITY_CODE_INDEX];
	UINT8	flashNewFlag;
}StorageParamsStruct;


extern	StorageParamsStruct storageParamsStruct;
extern	StorageParamsStruct *pStorageParamsStruct;
//extern	u16	TemperatureRecordArray[];

//#define WRITE_START_ADDR  ((uint32_t)0x00002000)
//#define WRITE_END_ADDR    ((uint32_t)0x00010000)
#define WRITE_START_ADDR  ((uint32_t)0x00007E00)
#define WRITE_END_ADDR    ((uint32_t)0x00008000)
#define FLASH_PAGE_SIZE    512

FLASH_Status LoadAllDataFromFlash(void);
FLASH_Status StoreData2Flash(void);
FLASH_Status TemperatureRecordInit(void);

extern	int FlashInit(void);





#endif /* USER_INC_USER_INTERNALFLASH_H_ */
