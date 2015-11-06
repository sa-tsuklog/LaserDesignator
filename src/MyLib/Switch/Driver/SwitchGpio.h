/*
 * SwitchGpio.h
 *
 *  Created on: 2015/11/06
 *      Author: sa
 */

#ifndef SWITCHGPIO_H_
#define SWITCHGPIO_H_

class SwitchGpio {
	// Singleton pattern definition
private:
	SwitchGpio();
	SwitchGpio(const SwitchGpio& rhs);
	SwitchGpio& operator=(const SwitchGpio& rhs);
	virtual ~SwitchGpio() {}
public:
	static SwitchGpio* GetInstance() {
		static SwitchGpio instance;
		return &instance;
	}

	// Class definition
private:
	
public:
	int getPinStatus();
	
};

#endif /* SWITCHGPIO_H_ */
