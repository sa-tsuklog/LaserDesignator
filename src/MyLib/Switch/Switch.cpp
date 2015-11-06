/*
 * Switch.cpp
 *
 *  Created on: 2015/11/06
 *      Author: sa
 */

#include "Switch.h"
#include "Driver/SwitchGpio.h"

Switch::Switch() {
	SwitchGpio::GetInstance();
}

int Switch::isPushed(){
	if(SwitchGpio::GetInstance()->getPinStatus()){
		return 0;
	}else{
		return 1;
	}
}
