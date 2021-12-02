/*
 * user_internalFlash.c
 *
 *  Created on: 2019-08-12
 *      Author: Bough_004
 */

#include "user_internalFlash.h"
#include "user_menu.h"
#include "user_ddl.h"

StorageParamsStruct storageParamsStruct;
StorageParamsStruct *pStorageParamsStruct=&storageParamsStruct;
u32 readInternalFlashData(u32 Address){
	return	*(__IO u32*)Address;
}
u16 readInternalFlashWrod(u32 Address){
	return	*(__IO u16*)Address;
}
u8 readInternalFlashByte(u32 Address){
	return	*(__IO u8*)Address;
}

FLASH_Status EraseFlash(void){
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	/*清除所有的标志位*/
	FLASH_ClearFlag(FLASH_FLAG_ALL);

	FLASHStatus = FLASH_EraseSector(WRITE_START_ADDR);
	return	FLASHStatus;
}

FLASH_Status StoreData2Flash(void){
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	uint32_t Address = 0x00;
	uint8_t i=0;
	UINT8 * p=(UINT8 *)&storageParamsStruct;
	EraseFlash();
	/*PROGRAM*/
	Address = WRITE_START_ADDR;
	for(i=0;i<MAX_SECURITY_CODE_INDEX+1;i++) {
//		FLASHStatus =FLASH_ProgramHalfWord(Address,TemperatureRecordArray[i]);
		FLASHStatus =FLASH_ProgramByte(Address,*(p+i));
		Address ++;
	}
	return	FLASHStatus;
}

FLASH_Status LoadAllDataFromFlash(void){
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	uint32_t Address = 0x00;
	uint8_t i=0,len=0;
	UINT8 * p=(UINT8 *)&storageParamsStruct;
	Address = WRITE_START_ADDR;
	i=0;
	len=sizeof(storageParamsStruct);
//	while (i < MAX_TEMPERATURE_INDEX+10) {
	while (i < len) {
		*(p+(i++))=*(__IO UINT8*) Address;
//		TemperatureRecordArray[i++]=*(__IO UINT8*) Address;
		Address += 1;
	}
	return	FLASHStatus;
}
/******************************************************
 *
 * 初始化所有数据
 *
 *******************************************************/
FLASH_Status StoreDataInit(void){
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	FLASHStatus=EraseFlash();
	if(FLASHStatus!=FLASH_COMPLETE)
		return	FLASHStatus;
	FLASHStatus=LoadAllDataFromFlash();
	if(FLASHStatus!=FLASH_COMPLETE)
		return	FLASHStatus;
	DDL_ZERO_STRUCT(storageParamsStruct);
	pStorageParamsStruct->flashNewFlag=NEW_FLASH_CODE;
	FLASHStatus=StoreData2Flash();
	return	FLASHStatus;
}

int FlashInit(void){
	LoadAllDataFromFlash();
	if(NEW_FLASH_CODE!=pStorageParamsStruct->flashNewFlag){		//新Flash或者 Flash数据丢失
		StoreDataInit();											//重新初始化Flash
		LoadAllDataFromFlash();
	}
	return	 PASSED;
}
/**
* @brief  InternalFlash_Test
* @param  None
* @retval None
*/
//int Test_Flash(void)
//{
//	uint32_t EraseAddr = (uint32_t) 0x00;
//	uint32_t Address = 0x00;
//	UINT8 Data = 0xAA33;
//	UINT8 readTemp = 0;
//	uint8_t	i=0;
//
//	FLASH_Status FLASHStatus = FLASH_COMPLETE;
//	TestStatus MemoryProgramStatus = PASSED;
//
////	/*清除所有的标志位*/
////	FLASH_ClearFlag(FLASH_FLAG_ALL);
////	/*ERASE*/
////	for (EraseAddr = WRITE_START_ADDR; EraseAddr <= WRITE_END_ADDR;
////			EraseAddr = EraseAddr + 512) {
////		FLASHStatus = FLASH_EraseSector(EraseAddr);
////	}
//	EraseFlash();
//
//	/*PROGRAM*/
//	Address = WRITE_START_ADDR;
//	while (Address < WRITE_END_ADDR) {
//		if(Address==WRITE_START_ADDR+8)
//			FLASH_ProgramHalfWord(WRITE_START_ADDR+8,0x1234);
//		else
//			FLASHStatus = FLASH_ProgramHalfWord(Address, Data);
//		Address = Address + 2;
//	}
//	while(FLASH_COMPLETE!=FLASHStatus);
//	/*READ&&CHECK*/
//	Address = WRITE_START_ADDR;
//	i=0;
//	while (Address < WRITE_END_ADDR) {
//		readTemp=*(__IO UINT8*) Address;
//		TemperatureRecordArray[i++]=readTemp;
//		if (readTemp != Data) {
//			MemoryProgramStatus = FAILED;
//		}
//		Address += 2;
//	}
//	return MemoryProgramStatus;
//}
