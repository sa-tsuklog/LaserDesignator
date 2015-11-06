/*
 * LedGpio.cpp
 *
 *  Created on: 2015/03/25
 *      Author: sa
 */

#include "LedGpio.h"
#include "stm32f0xx.h"

LedGpioClass::LedGpioClass(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
		
	GPIO_InitTypeDef pa12def;
	GPIO_StructInit(&pa12def);
	
	pa12def.GPIO_Mode = GPIO_Mode_OUT;
	pa12def.GPIO_OType = GPIO_OType_PP;
	pa12def.GPIO_Pin = GPIO_Pin_12;
	pa12def.GPIO_PuPd = GPIO_PuPd_NOPULL;
	pa12def.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&pa12def);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
}

void LedGpioClass::on(){
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
}
void LedGpioClass::off(){
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
}


