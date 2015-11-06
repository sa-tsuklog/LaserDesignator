/*
 * myFileHandle.c
 *
 *  Created on: 2014/05/28
 *      Author: sa
 */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "MyFileHandle.h"
#include "stm32f0xx.h"
#include "MyLib/Stdout/Driver/USART2.h"

#ifdef __cplusplus
 extern "C" {
#endif

//file handle
//1-2 :stdin,stdout,stderr
//3-9 :mapped to usart.

/***************************************************************************/

int myRead (struct _reent *r, int file, char * ptr, int len)
{
	return -1;
}

/***************************************************************************/

int myLseek (struct _reent *r, int file, int ptr, int dir)
{
//	r = r;
//	file = file;
//	ptr = ptr;
//	dir = dir;

	return 0;
}

/***************************************************************************/

int myWrite (struct _reent *r, int file, char * ptr, int len)
{
	unsigned int ret=0;
	if(file == 1){//stdout
		ret = len;
		if(USART2Class::GetInstance()->GetQueue() != NULL){
			for(int i=0;i<len;i++){
				if(xQueueSendToBackFromISR(USART2Class::GetInstance()->GetQueue(),&ptr[i],(BaseType_t *)pdFALSE)!=pdPASS){
					ret--;
				}else{
					
				}
			}
		}
	}else if(file == 2){//stderr
	}
	
	return ret;
}

int mySync(struct _reent *r,int file){
	return 0;
}

int myOpen(struct _reent *r,const char *path,int mode){
	return -1;
}

/***************************************************************************/

int myClose (struct _reent *r, int file)
{
	return -1;
}

int myFsync(FILE* fp){
	return mySync(NULL,fp->_file);
}

#ifdef __cplusplus
}
#endif
