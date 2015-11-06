/*
 * Ignitor.h
 *
 *  Created on: 2015/03/26
 *      Author: sa
 */

#ifndef IGNITOR_H_
#define IGNITOR_H_

class Ignitor {
	// Singleton pattern definition
private:
	Ignitor();
	Ignitor(const Ignitor& rhs);
	Ignitor& operator=(const Ignitor& rhs);
	virtual ~Ignitor() {}
public:
	static Ignitor* GetInstance() {
		static Ignitor instance;
		return &instance;
	}

	// Class definition
private:
	static const float SERVO0_LOCK_POS = -0.5;
	static const float SERVO0_UNLOCK_POS = 0.3;
	static const float SERVO1_LOCK_POS = -0.5;
	static const float SERVO1_UNLOCK_POS = 0.3;
	
	static const int MS_CYCLE = 100;
	static const int MS_SWICH_DELAY = 2000;
	static const int MS_UNLOCK_HOLD_TIME = 2000;
	
	void IgnitorTask();
public:
	static void IgnitorTaskEntry(void* pvParameter);
	static void initIgnitor();
};

#endif /* Ignitor_H_ */
