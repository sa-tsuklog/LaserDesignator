/*
 * Ignitor.cpp
 *
 *  Created on: 2015/03/26
 *      Author: sa
 */

#include "FreeRTOS.h"
#include "task.h"

#include "stdio.h"

#include "MyLib/ThermoCouple/Driver/SPI1.h"
#include "MyLib/Switch/Switch.h"
#include "Ignitor.h"

#include "MyLib/Servo/Servo.h"

Ignitor::Ignitor(){
	Switch::GetInstance();
	Servo::GetInstance();
}


void Ignitor::IgnitorTask(){
	portTickType lastWakeTime;
	lastWakeTime = xTaskGetTickCount();
	
	Servo::GetInstance()->start();
	
	int pushedCount=0;
	while(1){
		Servo::GetInstance()->setPos(0,SERVO0_LOCK_POS);
		Servo::GetInstance()->setPos(1,SERVO1_LOCK_POS);
		
		if(Switch::GetInstance()->isPushed()){
			pushedCount++;
		}else{
			pushedCount=0;
		}

		if(pushedCount == MS_SWICH_DELAY/MS_CYCLE){
			Servo::GetInstance()->setPos(0,SERVO0_UNLOCK_POS);
			Servo::GetInstance()->setPos(1,SERVO1_UNLOCK_POS);
			vTaskDelay(MS_UNLOCK_HOLD_TIME);
		}
		vTaskDelayUntil(&lastWakeTime,MS_CYCLE);
	}
}
static void Ignitor::IgnitorTaskEntry(void* pvParameter){
	Ignitor::GetInstance()->IgnitorTask();
}
static void Ignitor::initIgnitor(){
	SPI1Class::GetInstance();
	
	xTaskCreate(&Ignitor::IgnitorTaskEntry,"temp",1024,NULL,2,NULL);
}
