/*
 * VoltageMonitor.cpp
 *
 *  Created on: 2015/03/25
 *      Author: sa
 */

#include "FreeRTOS.h"
#include "task.h"

#include "stdio.h"

#include "VoltageMonitor.h"
#include "MyLib/Adc/Driver/Adc.h"
#include "MyLib/Led/Driver/LedGpio.h"

#include "stm32f0xx.h"

VoltageMonitor::VoltageMonitor(){
	
}

uint32_t VoltageMonitor::getMvVoltage(){
	uint32_t adcValue;
	
	AdcClass::GetInstance()->startAdc();
	vTaskDelay(1);
	adcValue = AdcClass::GetInstance()->getLastAdData();
	
	return adcValue*11*3333/4096-mvOffset;
}

void VoltageMonitor::voltageMonitorTask(){
	while(1){
		if(getMvVoltage()<MV_ALART_VOLTAGE){
			LedGpioClass::GetInstance()->on();
			vTaskDelay(250);
			LedGpioClass::GetInstance()->off();
			vTaskDelay(250);
		}else{
			for(int i=0;i<50;i++){
				LedGpioClass::GetInstance()->on();
				vTaskDelay(1);
				LedGpioClass::GetInstance()->off();
				vTaskDelay(9);
			}
		}
	}
}

static void VoltageMonitor::voltageMonitorTaskEntry(void* pvParameters){
	VoltageMonitor::GetInstance()->voltageMonitorTask();
}
static void VoltageMonitor::initVoltageMonitor(){
	AdcClass::GetInstance();
	LedGpioClass::GetInstance();
	
	xTaskCreate(voltageMonitorTaskEntry,"vMon",256,NULL,1,NULL);
}


