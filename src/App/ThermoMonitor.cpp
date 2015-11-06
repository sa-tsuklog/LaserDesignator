/*
 * ThermoMonitor.cpp
 *
 *  Created on: 2015/03/26
 *      Author: sa
 */

#include "FreeRTOS.h"
#include "task.h"

#include "stdio.h"

#include "MyLib/ThermoCouple/Driver/SPI1.h"
#include "ThermoMonitor.h"

#include "MyLib/Servo/Servo.h"

ThermoMonitor::ThermoMonitor(){
	Servo::GetInstance();
}

int ThermoMonitor::getMkTemp(){
	uint32_t buf = SPI1Class::GetInstance()->txrx16(0);
	
	return (int)(buf>>2)/4;
}

void ThermoMonitor::thermoMonitorTask(){
	portTickType lastWakeTime;
	lastWakeTime = xTaskGetTickCount();
	
	Servo::GetInstance()->start();
	
	int i=0;
	while(1){
		i++;
		//int temp = getMkTemp();
		//printf("%d,%d\r\n",i,temp);
		vTaskDelayUntil(&lastWakeTime,1000);
		
		if(i%10 == 0){
			Servo::GetInstance()->setPos(0,0.3);
			Servo::GetInstance()->setPos(1,0.3);
		}else{
			Servo::GetInstance()->setPos(0,-0.5);
			Servo::GetInstance()->setPos(1,-0.5);
		}
	}
}
static void ThermoMonitor::thermoMonitorTaskEntry(void* pvParameter){
	ThermoMonitor::GetInstance()->thermoMonitorTask();
}
static void ThermoMonitor::initThermoMonitor(){
	SPI1Class::GetInstance();
	
	xTaskCreate(&ThermoMonitor::thermoMonitorTaskEntry,"temp",1024,NULL,2,NULL);
}
