/*
 * TIM1.cpp
 *
 *  Created on: 2014/04/21
 *      Author: sa
 */
#include "stm32f0xx.h"
#include "ServoTim1.h"

ServoTim1::ServoTim1(){
	/////////////////////////////////////
	//GPIO
	/////////////////////////////////////
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpioa8;
	GPIO_StructInit(&gpioa8);
	gpioa8.GPIO_Pin = GPIO_Pin_8;
	gpioa8.GPIO_Mode = GPIO_Mode_AF;
	gpioa8.GPIO_OType = GPIO_OType_PP;
	gpioa8.GPIO_Speed = GPIO_Speed_50MHz;
	gpioa8.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpioa8);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_2);
	
	GPIO_InitTypeDef gpioa9;
	GPIO_StructInit(&gpioa9);
	gpioa9.GPIO_Pin = GPIO_Pin_9;
	gpioa9.GPIO_Mode = GPIO_Mode_AF;
	gpioa9.GPIO_OType = GPIO_OType_PP;
	gpioa9.GPIO_Speed = GPIO_Speed_50MHz;
	gpioa9.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpioa9);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_2);
	
	
	/////////////////////////////////////
	//TIM
	/////////////////////////////////////
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TIM_TimeBaseInitTypeDef timebase;
	TIM_TimeBaseStructInit(&timebase);
	timebase.TIM_ClockDivision = TIM_CKD_DIV1;
	timebase.TIM_Prescaler = 48-1;
	timebase.TIM_Period = 15000-1;
	timebase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1,&timebase);
	
	TIM_OCInitTypeDef oc1def;
	TIM_OCStructInit(&oc1def);
	oc1def.TIM_OCMode = TIM_OCMode_PWM1;
	oc1def.TIM_OutputState = TIM_OutputState_Enable;
	oc1def.TIM_OCPolarity = TIM_OCPolarity_High;
	oc1def.TIM_Pulse = 1500-1;
	TIM_OC1Init(TIM1,&oc1def);
	
	TIM_OCInitTypeDef oc2def;
	TIM_OCStructInit(&oc2def);
	oc2def.TIM_OCMode = TIM_OCMode_PWM1;
	oc2def.TIM_OutputState = TIM_OutputState_Enable;
	oc2def.TIM_OCPolarity = TIM_OCPolarity_High;
	oc2def.TIM_Pulse = 1500-1;
	TIM_OC2Init(TIM1,&oc2def);
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

void ServoTim1::timerStart(){
	TIM_Cmd(TIM1,ENABLE);
}
void ServoTim1::setDuty(int ch,uint32_t duty){
	switch(ch){
	case 0:TIM_SetCompare1(TIM1,duty);break;
	case 1:TIM_SetCompare2(TIM1,duty);break;
	}
}


