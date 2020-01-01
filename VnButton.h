/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnButton
 * \brief   Driver for Vn Buzzer module.
 * @file    VnButton.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VnButton.cpp module
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
 *    1. void VnButton::setpin(int pin);
 *	  2. void VnButton::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void VnButton::tone(uint16_t frequency, uint32_t duration)
 *	  4. void VnButton::noTone(int pin);
 *	  5. void VnButton::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#ifndef VnButton_H
#define VnButton_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED


#define MODE1	1
#define MODE2	2
#define MODE3	3
#define MODE4	4

/**
 * Class: VnButton
 * @Brief : Declaration of Class VnButton.
 */
#ifdef VN_PORT_DEFINED
class VnButton : public VnPort
#else
class VnButton
#endif
{
public:
#ifdef VN_PORT_DEFINED

  VnButton(void);
  VnButton(uint8_t port);
#else // VN_PORT_DEFINED
  VnButton(int pin);
#endif // VN_PORT_DEFINED
	void setpin(int pin);
	void read_mode(void);
	
	volatile uint8_t mode_pin;
	volatile uint8_t mode_state;
};
#endif
