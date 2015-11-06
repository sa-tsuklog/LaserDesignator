#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_conf.h"

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"

#include "FreeRTOS.h"
#include "task.h"

#include "MyLib/Stdout/Stdout.h"
#include "MyLib/Stdout/Driver/USART2.h"

#include "App/VoltageMonitor.h"
#include "App/Ignitor.h"
#include "MyLib/WaveGenerator/Driver/TIM3.h"

void prvTaskA(void* pvParameters){
	char* string;
	int i=0;
	uint16_t temp;
	while(1){
		vTaskDelay(100);
		i++;
	}
}

int main(void) {
	SystemInit();
	
	
	
	//xTaskCreate(prvTaskA,"test",1024,NULL,1,NULL);
	Stdout::initStdout();
	VoltageMonitor::initVoltageMonitor();
	Ignitor::initIgnitor();
	TIM3Class::GetInstance();
	
	vTaskStartScheduler();
	
	while (1){}
}
