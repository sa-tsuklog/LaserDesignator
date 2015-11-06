/*
 * Adc.cpp
 *
 *  Created on: 2015/03/25
 *      Author: sa
 */

#include "Adc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_adc.h"

AdcClass::AdcClass(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef gpioa4;
	GPIO_StructInit(&gpioa4);
	gpioa4.GPIO_Pin = GPIO_Pin_4;
	gpioa4.GPIO_Mode = GPIO_Mode_AN;
	gpioa4.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&gpioa4);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitTypeDef adc;
	ADC_StructInit(&adc);
	adc.ADC_ContinuousConvMode = DISABLE;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_Resolution = ADC_Resolution_12b; 
	adc.ADC_ScanDirection = ADC_ScanDirection_Upward;
	
	ADC_Init(ADC1,&adc);
	
	
	
	calibrationFactor = ADC_GetCalibrationFactor(ADC1);
	
	ADC_Cmd(ADC1,ENABLE);
	ADC_ChannelConfig(ADC1,ADC_Channel_4,ADC_SampleTime_7_5Cycles);
}

void AdcClass::startAdc(){
	ADC_StartOfConversion(ADC1);
}
uint32_t AdcClass::getLastAdData(){
	return ADC_GetConversionValue(ADC1) + calibrationFactor;
}
