/*
 * SPI1.h
 *
 *  Created on: 2015/03/26
 *      Author: sa
 */

#ifndef SPI1_H_
#define SPI1_H_

class SPI1Class {
	// Singleton pattern definition
private:
	SPI1Class();
	SPI1Class(const SPI1Class& rhs);
	SPI1Class& operator=(const SPI1Class& rhs);
	virtual ~SPI1Class() {}
public:
	static SPI1Class* GetInstance() {
		static SPI1Class instance;
		return &instance;
	}

	// Class definition
private:
	
public:
	uint16_t txrx16(uint16_t txData);
	
};

#endif /* SPI1_H_ */
