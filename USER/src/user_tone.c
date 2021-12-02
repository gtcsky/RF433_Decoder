/*
 * tone.c
 *
 *  Created on: 2020年3月7日
 *      Author: Bough_004
 */
#include "user_tone.h"
#include "misc.h"

#include "user_adc.h"
#include "io_define.h"
#include "user_lptimer.h"
#include "user_advtime.h"

#define	MAX_EDNTONE_INDEX		10
#define	MAX_KEYTONE_INDEX		2
#define	MAX_CONFIRM_INDEX		2
#define	MAX_ERRORTONE_INDEX		6

voiceParamStruct	 voiceParams;

const u8 keyToneTimeArray[MAX_KEYTONE_INDEX]={1,10};
const u8 keyToneSttsArray[MAX_KEYTONE_INDEX]={0,1};

//const u8 endToneTimeArray[MAX_EDNTONE_INDEX]={1,10,20,10,20,10,20,10,20,10};
//const u8 endToneSttsArray[MAX_EDNTONE_INDEX]=  {0,1,0,1,0,1,0,1,0,1};
const u8 endToneTimeArray[MAX_EDNTONE_INDEX]={1,10,100,10,100,10,100,10,100,100};
const u8 endToneSttsArray[MAX_EDNTONE_INDEX]=  {0,1,0,1,0,1,0,1,0,1};

const u8 confirmToneTimeArray[MAX_CONFIRM_INDEX]={1,100};
const u8 confirmToneSttsArray[MAX_CONFIRM_INDEX]={0,1};

const u8 systemVoltErrorTimeArray[MAX_ERRORTONE_INDEX]={10,10,10,10,10,10};
const u8 systemVoltErrorSttsArray[MAX_ERRORTONE_INDEX]=   {0,1,0	,1,0,1};

void genTonePub(voiceParamStruct * vtVoicePara){
	vSystem5ms = 0;
	vtVoicePara->tongStts = ON;
	vtVoicePara->tongProcessCnt = voiceParams.timeArray[0];	//100ms
	vtVoicePara->toneProcessIndex = 0;
	vtVoicePara->pfnToneFuncCallBack = NULL;
}

void	 genErrorTone(void){
//		voiceParams.toneID = ErrorTone;
		voiceParams.toneMaxIndex = MAX_ERRORTONE_INDEX;
		voiceParams.timeArray = systemVoltErrorTimeArray;
		voiceParams.sttsArray = systemVoltErrorSttsArray;
		genTonePub(&voiceParams);
//		vSystem5ms = 0;
//		voiceParams.tongStts = ON;
//		voiceParams.tongProcessCnt = voiceParams.timeArray[0];	//100ms
//		voiceParams.toneProcessIndex = 0;
//		voiceParams.pfnToneFuncCallBack = NULL;
}


void genConfrimTone(void) {
//		voiceParams.toneID = ConfirmTone;
		voiceParams.toneMaxIndex = MAX_CONFIRM_INDEX;
		voiceParams.timeArray = confirmToneTimeArray;
		voiceParams.sttsArray = confirmToneSttsArray;
		genTonePub(&voiceParams);
//		vSystem5ms = 0;
//		voiceParams.tongStts = ON;
//		voiceParams.tongProcessCnt = voiceParams.timeArray[0];	//100ms
//		voiceParams.toneProcessIndex = 0;
//		voiceParams.pfnToneFuncCallBack = NULL;
}

void genKeyTone(void) {
//		voiceParams.toneID = KeyTone;
		voiceParams.toneMaxIndex = MAX_KEYTONE_INDEX;
		voiceParams.timeArray = keyToneTimeArray;
		voiceParams.sttsArray = keyToneSttsArray;
		genTonePub(&voiceParams);
//		vSystem5ms = 0;
//		voiceParams.tongStts = ON;
//		voiceParams.tongProcessCnt = voiceParams.timeArray[0];	//100ms
//		voiceParams.toneProcessIndex = 0;
//		voiceParams.pfnToneFuncCallBack = NULL;
}
void genEndTone(void) {
//		voiceParams.toneID = EndTone;
		voiceParams.toneMaxIndex = MAX_EDNTONE_INDEX;
		voiceParams.timeArray = endToneTimeArray;
		voiceParams.sttsArray = endToneSttsArray;
		genTonePub(&voiceParams);
//		vSystem5ms = 0;
//		voiceParams.tongStts = ON;
//		voiceParams.toneProcessIndex = 0;
//		voiceParams.pfnToneFuncCallBack = NULL;
//		voiceParams.tongProcessCnt = voiceParams.timeArray[0];
}

void turnOffTone(void) {
	voiceParams.tongStts = OFF;
	updatePWMChlDuty(BUZZER_CHANNEL, OFF, ADVTIM1);		//
}

void voiceFunc(void){
	if(ON==voiceParams.tongStts){
		if(voiceParams.tongProcessCnt&&(--voiceParams.tongProcessCnt==0)){
			if(++voiceParams.toneProcessIndex>=voiceParams.toneMaxIndex){
				voiceParams.tongStts=OFF;								//end of tone
				updatePWMChlDuty(BUZZER_CHANNEL,OFF,ADVTIM1);		//
			}else{
				voiceParams.tongProcessCnt=voiceParams.timeArray[voiceParams.toneProcessIndex];
				if(1==voiceParams.sttsArray[voiceParams.toneProcessIndex]){
					updatePWMChlDuty(BUZZER_CHANNEL,TONE_DUTY,ADVTIM1);		//duty=0.3
				}else{
					updatePWMChlDuty(BUZZER_CHANNEL,OFF,ADVTIM1);		//duty=0.3
				}
			}
		}
	}
}
