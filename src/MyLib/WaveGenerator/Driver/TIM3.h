/*
 * TIM3Class.h
 *
 *  Created on: 2015/03/25
 *      Author: sa
 */

#ifndef TIM3CLASS_H_
#define TIM3CLASS_H_

class TIM3Class {
	// Singleton pattern definition
private:
	TIM3Class();
	TIM3Class(const TIM3Class& rhs);
	TIM3Class& operator=(const TIM3Class& rhs);
	virtual ~TIM3Class() {}
public:
	static TIM3Class* GetInstance() {
		static TIM3Class instance;
		return &instance;
	}

	// Class definition
private:
	
public:
	
	
};

#endif /* TIM3CLASS_H_ */
