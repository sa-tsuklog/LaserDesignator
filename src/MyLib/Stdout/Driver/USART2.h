/*
 * USART2.hpp
 *
 *  Created on: 2014/04/27
 *      Author: sa
 */

#ifndef USART2_HPP_
#define USART2_HPP_

#include "stm32f0xx.h"
#include "FreeRTOS.h"
#include "queue.h"

class USART2Class {
	// Singleton pattern definition
private:
	USART2Class();
	USART2Class(const USART2Class& rhs);
	USART2Class& operator=(const USART2Class& rhs);
	virtual ~USART2Class() {}
public:
	static USART2Class* GetInstance() {
    	static USART2Class instance;
    	return &instance;
	}

	// Class definition
private:
	static const int TX_BUFFERSIZE = 128;
	static const int RX_BUFFERSIZE = 48;
	static const int LINE_BUF_SIZE = 48;
	xQueueHandle m_queue3;
	char m_txBuf[TX_BUFFERSIZE];
	char m_rxBuf[RX_BUFFERSIZE];
	char m_lineBuf[LINE_BUF_SIZE];
	int rxBufIndex;
	
	int echo;
public:
	virtual void Tx();
	//virtual void Rx();
	virtual char* readLine();
	virtual char getChar();
	virtual void setEcho(int newValue){echo = newValue;};
	xQueueHandle GetQueue(){ return m_queue3; }
	// Task definition
public:
	static void prvTxTask(void *pvParameters);
	static void prvRxTask(void *pvParameters);
};


#endif /* USART2_HPP_ */
