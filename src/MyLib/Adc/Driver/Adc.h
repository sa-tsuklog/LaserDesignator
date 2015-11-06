/*
 * Adc.h
 *
 *  Created on: 2015/03/25
 *      Author: sa
 */

#ifndef ADC_H_
#define ADC_H_

#include "stdint.h"

class AdcClass {
	// Singleton pattern definition
private:
	AdcClass();
	AdcClass(const AdcClass& rhs);
	AdcClass& operator=(const AdcClass& rhs);
	virtual ~AdcClass() {}
public:
	static AdcClass* GetInstance() {
		static AdcClass instance;
		return &instance;
	}

	// Class definition
private:
	
public:
	uint32_t calibrationFactor;
	void startAdc();
	uint32_t getLastAdData();
};


#endif /* ADC_H_ */
