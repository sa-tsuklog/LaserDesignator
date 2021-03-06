/*
 * Servo.h
 *
 *  Created on: 2014/06/08
 *      Author: sa
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

/**
 * @class Servo
 * @brief サーボ制御用クラス
 */


class Servo {
	// Singleton pattern definition
private:
	Servo();
	Servo(const Servo& rhs);
	Servo& operator=(const Servo& rhs);
	virtual ~Servo() {}
public:
	/**
	 * @brief このクラスのインスタンスを返す
	 */
	static Servo* GetInstance() {
		static Servo instance;
		return &instance;
	}

	// Class definition
private:
	static const int USE_CH0_1 = 1;/**<@brief 1:ch0～1を使用する 0:ch0～1を使用しない*/
	
	static const uint32_t US_DUTY_CENTER = 1500;/**<@brief 中立位置(pos = 0)でのパルス幅*/
	static const uint32_t US_DUTY_GAIN = 350;/**<@brief パルス幅の変化量*/
	
public:
	static const int CH_NUM = 2; /**<@brief 最大チャンネル数*/
	
	void start();
	void setPos(int ch,float pos);
};

#endif /* SERVO_H_ */
