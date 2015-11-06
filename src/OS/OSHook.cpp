/*
 * OSHook.c
 *
 *  Created on: 2014/03/14
 *      Author: Lark_mp
 */

unsigned int idle_count = 0;

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stdint.h"

void vApplicationIdleHook(void){
	idle_count++;
}

void vApplicationMallocFailedHook(void){
	while(1);
}

void vApplicationStackOverflowHook(void* ptr, char* taskname){
	while(1);
}

void vApplicationTickHook(){
	
}

void vConfigureTimerForRumTimeStats(){
	
}

uint32_t vGetRunTimeCounterValue(){
	return 0;
}

#ifdef __cplusplus
 }
#endif 
