/*
 * TIM3Class.cpp
 *
 *  Created on: 2015/03/25
 *      Author: sa
 */

#include "stm32f0xx.h"

#include "TIM3.h"


TIM3Class::TIM3Class(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef gpioa6;
	GPIO_StructInit(&gpioa6);
	gpioa6.GPIO_Pin = GPIO_Pin_6;
	gpioa6.GPIO_Mode = GPIO_Mode_AF;
	gpioa6.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioa6.GPIO_OType = GPIO_OType_PP;
	gpioa6.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpioa6);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_1);
	
	
	GPIO_InitTypeDef gpioa7;
	GPIO_StructInit(&gpioa7);
	gpioa7.GPIO_Pin = GPIO_Pin_7;
	gpioa7.GPIO_Mode = GPIO_Mode_OUT;
	gpioa7.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioa7.GPIO_OType = GPIO_OType_PP;
	gpioa7.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpioa7);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseInitTypeDef timebase;
	TIM_TimeBaseStructInit(&timebase);
	timebase.TIM_ClockDivision = TIM_CKD_DIV1;
	timebase.TIM_Prescaler = 48-1;
	timebase.TIM_Period = 1000-1;
	timebase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&timebase);
	
	TIM_OCInitTypeDef oc1def;
	TIM_OCStructInit(&oc1def);
	oc1def.TIM_OCMode = TIM_OCMode_PWM1;
	oc1def.TIM_OutputState = TIM_OutputState_Enable;
	oc1def.TIM_OCPolarity = TIM_OCPolarity_High;
	oc1def.TIM_Pulse = 500-1;
	TIM_OC1Init(TIM3,&oc1def);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}


