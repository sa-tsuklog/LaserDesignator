/*
 * Stdout.cpp
 *
 *  Created on: 2014/06/08
 *      Author: sa
 */

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f0xx.h"

#include "Stdout.h"
//#include "SerialCommand.h"
#include "Driver/USART2.h"

Stdout::Stdout(){
	
}

void Stdout::initStdout(){
	//task create.
	xTaskCreate(&USART2Class::prvTxTask,"u2tx",512,NULL,2,&(Stdout::GetInstance()->u3txHandle));
	//xTaskCreate(&USART3Class::prvRxTask,"u3rx",1024,USART3,1,NULL);
	//xTaskCreate(&SerialCommand::prvSerialCommandTaskEntry,"u2rx",256,NULL,3,&(Stdout::GetInstance()->u2rxHandle));
}


