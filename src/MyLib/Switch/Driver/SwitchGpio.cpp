/*
 * SwitchGpio.cpp
 *
 *  Created on: 2015/11/06
 *      Author: sa
 */
#include "stm32f0xx.h"
#include "SwitchGpio.h"


SwitchGpio::SwitchGpio(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef pa15def;
	GPIO_StructInit(&pa15def);
	pa15def.GPIO_Mode = GPIO_Mode_IN;
	pa15def.GPIO_Pin = GPIO_Pin_15;
	pa15def.GPIO_PuPd = GPIO_PuPd_UP;
	pa15def.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA,&pa15def);
}

int SwitchGpio::getPinStatus(){
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
}
