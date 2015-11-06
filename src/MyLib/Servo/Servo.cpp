/*
 * Servo.cpp
 *
 *  Created on: 2014/06/08
 *      Author: sa
 */
#include "Servo.h"
#include "Driver/ServoTim1.h"

Servo::Servo(){
	if(USE_CH0_1){
		ServoTim1::GetInstance();
	}
}
/**
 * @brief パルスの出力を開始する
 */
void Servo::start(){
	if(USE_CH0_1){
		ServoTim1::GetInstance()->timerStart();
	}
}

/**
 * @brief パルス幅を設定する
 * 
 * @param[in] ch パルス幅を設定するチャンネル
 * @param[in] pos パルス幅。-1.0～1.0。範囲外の値が入力された場合、それぞれ-1.0、1.0として扱われる。
 * 
 */
void Servo::setPos(int ch,float pos){
	//int* trim = Util::GetInstance()->flashData.servoTrim;
	int trim[2];
	trim[0] = 0;
	trim[1] = 0;
	
	if(pos < -1.0){
		pos = -1.0;
	}else if(pos > 1.0){
		pos = 1.0;
	}
	
	switch(ch){
	case 0:if(USE_CH0_1){ServoTim1::GetInstance()->setDuty(0,US_DUTY_CENTER+pos*US_DUTY_GAIN-1 + trim[0]);}break;
	case 1:if(USE_CH0_1){ServoTim1::GetInstance()->setDuty(1,US_DUTY_CENTER+pos*US_DUTY_GAIN-1 + trim[1]);}break;
	}
}
