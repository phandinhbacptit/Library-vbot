/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \brief   Driver for Vbot Servo motor.
 * \file    VnServo.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/10/29
 * @brief   Header for VnServo.cpp module
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
 * This file is Hardware adaptation layer between Vbot board and all
 * Vrobotx drives
 * 
 * @ Method List:
 *
 *    1. void VnServo::move(int direction, int speed);
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/10/29      1.0.0            Build the first library.
 * </pre>
 */

#ifndef VnServo_H
#define VnServo_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "VnConfig.h"

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif




/**
 * Class: VnServo
 * @Brief :
 * Declaration of Class VnServo.
 */
#ifdef VN_PORT_DEFINED
class VnServo : public VnPort
#else
class VnServo
#endif
{
public:
#ifdef VN_PORT_DEFINED
  VnServo(void) ;
  VnServo(uint8_t port);
  void attach(uint8_t channel);
  void detach(void);
  void write(int value);
#else
	VnServo(uint8_t pin, uint8_t channel);
	void attach(void);
	void detach(void);
	void write(int value);
#endif

private:
  volatile uint8_t _channel;
  volatile uint8_t _pin;
};
#endif //VN_PORT_DEFINED
