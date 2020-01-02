/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   Vn74hc595
 * \brief   Driver for Vn Buzzer module.
 * @file    Vn74hc595.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for Vn74hc595.cpp module
 *
 * @ Copyright
 * This software is Copyright (C), 2018-2020, Vrobotx. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * @ Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * @Brief :
 * This file is a drive for Vn Buzzer device, The Vn Buzzer inherited the 
 * VnSerial class from SoftwareSerial.
 *
 * @ Vnthod List:
 *
 *    1. void Vn74hc595::setpin(int pin);
 *	  2. void Vn74hc595::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void Vn74hc595::tone(uint16_t frequency, uint32_t duration)
 *	  4. void Vn74hc595::noTone(int pin);
 *	  5. void Vn74hc595::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2019/12/30      1.0.0            Build the first library.
 * </pre>
 */
#ifndef _VN74HC595_H_
#define _VN74HC595_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED
/**
 * Class: Vn74hc595
 * @Brief : Declaration of Class Vn74hc595.
 */
#define RIGHT_SIDE 		0
#define LEFT_SIDE 		1
 
#ifdef VN_PORT_DEFINED
class Vn74hc595 : public VnPort
#else
class Vn74hc595
#endif
{
public:
#ifdef VN_PORT_DEFINED

	Vn74hc595(void);
	Vn74hc595(uint8_t port);
	Vn74hc595(uint8_t port, uint8_t slot);
  
#else //VN_PORT_DEFINED

	Vn74hc595(uint8_t ser_pin, uint8_t clk_pin, uint8_t latch_pin);

#endif //VN_PORT_DEFINED
	void shiftOutData(uint8_t dataOut);
	void screenClear(void);
	void displayImage(unsigned int image[], int duration);
	void scrollImage(unsigned int image[], uint8_t duration, uint8_t dir_shift);
private:
	volatile uint8_t  _latchPin;
	volatile uint8_t  _clkPin;
	volatile uint8_t  _serPin;
	
	int row[8] = {1, 2, 4, 8, 16, 32, 64, 128};
	int column[8] = {128, 64, 32, 16, 8, 4, 2, 1};

};
#endif /* _VN74HC595_H_ */