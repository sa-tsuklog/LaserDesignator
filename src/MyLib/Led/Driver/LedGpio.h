/*
 * LedGpio.h
 *
 *  Created on: 2015/03/25
 *      Author: sa
 */

#ifndef LEDGPIO_H_
#define LEDGPIO_H_

class LedGpioClass {
	// Singleton pattern definition
private:
	LedGpioClass();
	LedGpioClass(const LedGpioClass& rhs);
	LedGpioClass& operator=(const LedGpioClass& rhs);
	virtual ~LedGpioClass() {}
public:
	static LedGpioClass* GetInstance() {
		static LedGpioClass instance;
		return &instance;
	}

	// Class definition
private:
	
public:
	void on();
	void off();
};

#endif /* LEDGPIO_H_ */
