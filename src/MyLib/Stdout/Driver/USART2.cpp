/*
 * USART2.cpp
 *
 *  Created on: 2014/04/27
 *      Author: sa
 */



#include "USART2.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "stdlib.h"

USART2Class::USART2Class(){
	m_queue3 = xQueueCreate(TX_BUFFERSIZE,sizeof(char));
	if(m_queue3 == NULL){
		while(1){}
	}
	vQueueAddToRegistry(m_queue3,"u2tx");
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

	GPIO_InitTypeDef pa2def;

	GPIO_StructInit(&pa2def);
	pa2def.GPIO_Pin = GPIO_Pin_2;
	pa2def.GPIO_Mode = GPIO_Mode_AF;
	pa2def.GPIO_OType = GPIO_OType_PP;
	pa2def.GPIO_PuPd = GPIO_PuPd_NOPULL;
	pa2def.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&pa2def);

	GPIO_InitTypeDef pa3def;
	GPIO_StructInit(&pa3def);
	pa3def.GPIO_Pin = GPIO_Pin_3;
	pa3def.GPIO_Mode = GPIO_Mode_AF;
	pa3def.GPIO_PuPd = GPIO_PuPd_NOPULL;
	pa3def.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&pa3def);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);


	USART_InitTypeDef usart2;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	USART_StructInit(&usart2);
	usart2.USART_BaudRate = 115200;
	usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart2.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart2.USART_Parity = USART_Parity_No;
	usart2.USART_StopBits = USART_StopBits_1;
	usart2.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2,&usart2);

	USART_DMACmd(USART2,USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);

	USART_Cmd(USART2, ENABLE);


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);


	DMA_InitTypeDef dma4;
	DMA_StructInit(&dma4);
	dma4.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->TDR);
	dma4.DMA_MemoryBaseAddr = (uint32_t)m_txBuf;
	dma4.DMA_DIR = DMA_DIR_PeripheralDST;
	dma4.DMA_BufferSize = 1;
	dma4.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma4.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma4.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma4.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma4.DMA_Mode = DMA_Mode_Normal;
	dma4.DMA_Priority = DMA_Priority_High;
	
	DMA_Init(DMA1_Channel4,&dma4);
	
	DMA_InitTypeDef dma5;
	DMA_StructInit(&dma5);
	dma5.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->RDR);
	dma5.DMA_MemoryBaseAddr = (uint32_t)m_rxBuf;
	dma5.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma5.DMA_BufferSize = RX_BUFFERSIZE;
	dma5.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma5.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma5.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma5.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma5.DMA_Mode = DMA_Mode_Circular;
	dma5.DMA_Priority = DMA_Priority_Low;

	DMA_Init(DMA1_Channel5,&dma5);
	
	DMA_Cmd(DMA1_Channel5,ENABLE);


	for(int i=0;i<RX_BUFFERSIZE;i++){
		m_rxBuf[i] = 0;
	}
	
	echo = 0;
	rxBufIndex=0;
}

void USART2Class::Tx()
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	while(1){
		int numTx=0;
		
		if(DMA_GetFlagStatus(DMA1_FLAG_TC4)){
			DMA1_Channel4->CCR &= (~DMA_CCR_EN);
		}
		
		if((!(DMA1_Channel4->CCR&DMA_CCR_EN)) && (numTx = uxQueueMessagesWaiting(m_queue3)) != 0){
		//if(DMA_GetCmdStatus(DMA1_Channel4)==DISABLE && (numTx = uxQueueMessagesWaiting(m_queue3)) != 0){
			for(int i=0;i<numTx;i++){
				char c;
				xQueueReceive(m_queue3,&c,0);
				m_txBuf[i] = c;
			}
			
			DMA_SetCurrDataCounter(DMA1_Channel4,numTx);
			USART_ClearFlag(USART2,USART_FLAG_TC);
			DMA_ClearFlag(DMA1_FLAG_TC4);
			DMA_Cmd(DMA1_Channel4,ENABLE);
		}
		
		vTaskDelayUntil(&xLastWakeTime,1);
	}
}

char* USART2Class::readLine()
{
	int lineBufIndex = 0;

	char c;
	
	while(1){
		while( (c = m_rxBuf[rxBufIndex]) != 0 ){
			m_rxBuf[rxBufIndex]=0;
			rxBufIndex=(rxBufIndex+1)%RX_BUFFERSIZE;
			
			if(echo){
				if(c=='\r'){
					//do nothing
				}else if(c=='\n'){
					
				}else if(c=='\b'){
					putchar('\b');
					putchar(' ');
					putchar('\b');
					fflush(stdout);
				}else{
					putchar(c);
					fflush(stdout);
				}
			}
			
			
			if(c=='\r'){
			}else if(c=='\n'){
				if(lineBufIndex==0 || echo){
					putchar('\r');
					putchar('\n');
					fflush(stdout);
				}
				
				m_lineBuf[lineBufIndex]=0;
	
				//SerialCommand::GetInstance()->handleSerialCommand(m_lineBuf);
				lineBufIndex=0;
				return m_lineBuf;
			}else if(c=='\b'){
				if(lineBufIndex > 0){
					lineBufIndex--;
				}
			}else{
				
				m_lineBuf[lineBufIndex]=c;
				if(lineBufIndex<LINE_BUF_SIZE-1){
					lineBufIndex++;
				}
			}
		}
		
		vTaskDelay(10);
	}
}

char USART2Class::getChar(){
	char c;
	while(1){
		if((c = m_rxBuf[rxBufIndex]) != 0){
			m_rxBuf[rxBufIndex]=0;
			rxBufIndex=(rxBufIndex+1)%RX_BUFFERSIZE;
			return c;
		}
		vTaskDelay(25);
	}
	return 0;
}

void USART2Class::prvTxTask(void *pvParameters)
{
	USART2Class::GetInstance()->Tx();
}

