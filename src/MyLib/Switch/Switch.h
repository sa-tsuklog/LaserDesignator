/*
 * Switch.h
 *
 *  Created on: 2015/11/06
 *      Author: sa
 */

#ifndef SWITCH_H_
#define SWITCH_H_

class Switch {
	// Singleton pattern definition
private:
	Switch();
	Switch(const Switch& rhs);
	Switch& operator=(const Switch& rhs);
	virtual ~Switch() {}
public:
	static Switch* GetInstance() {
		static Switch instance;
		return &instance;
	}

	// Class definition
private:
	
public:
	int isPushed();
	
};

#endif /* SWITCH_H_ */
