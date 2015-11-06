/*
 * SPI1.cpp
 *
 *  Created on: 2015/03/26
 *      Author: sa
 */

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "stm32f0xx.h"

#include "SPI1.h"



SPI1Class::SPI1Class(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef pa15;
	GPIO_StructInit(&pa15);
	pa15.GPIO_Pin = GPIO_Pin_15;
	pa15.GPIO_Mode = GPIO_Mode_OUT;
	pa15.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&pa15);
	
	GPIO_InitTypeDef pb3;
	GPIO_StructInit(&pb3);
	pb3.GPIO_Pin = GPIO_Pin_3;
	pb3.GPIO_Mode = GPIO_Mode_AF;
	pb3.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&pb3);
	
	GPIO_InitTypeDef pb4;
	GPIO_StructInit(&pb4);
	pb4.GPIO_Pin = GPIO_Pin_4;
	pb4.GPIO_Mode = GPIO_Mode_AF;
	pb4.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&pb4);
	
	GPIO_InitTypeDef pb5;
	GPIO_StructInit(&pb5);
	pb5.GPIO_Pin = GPIO_Pin_5;
	pb5.GPIO_Mode = GPIO_Mode_AF;
	pb5.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&pb5);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_0);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	SPI_InitTypeDef spi;
	SPI_StructInit(&spi);
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	spi.SPI_CPHA = SPI_CPHA_2Edge;
	spi.SPI_CPOL = SPI_CPOL_High;
	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_DataSize = SPI_DataSize_16b;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(SPI1,&spi);
	SPI_NSSInternalSoftwareConfig(SPI1,ENABLE);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
	
	SPI_Cmd(SPI1,ENABLE);
}

uint16_t SPI1Class::txrx16(uint16_t txData){
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	SPI_I2S_SendData16(SPI1,txData);
	vTaskDelay(1);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
	return SPI_I2S_ReceiveData16(SPI1);
}

