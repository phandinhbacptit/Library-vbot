/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnBuzzer
 * \brief   Driver for Vn Buzzer module.
 * @file    VnBuzzer.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VnBuzzer.cpp module
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
 *    1. void VnBuzzer::setpin(int pin);
 *	  2. void VnBuzzer::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void VnBuzzer::tone(uint16_t frequency, uint32_t duration)
 *	  4. void VnBuzzer::noTone(int pin);
 *	  5. void VnBuzzer::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#ifndef VnBuzzer_H
#define VnBuzzer_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED

/**
 * Class: VnBuzzer
 * @Brief : Declaration of Class VnBuzzer.
 */
#ifdef VN_PORT_DEFINED
class VnBuzzer : public VnPort
#else
class VnBuzzer
#endif
{
public:
#ifdef VN_PORT_DEFINED

  VnBuzzer(void);
  VnBuzzer(uint8_t port);
  VnBuzzer(uint8_t port, uint8_t slot);
#else // VN_PORT_DEFINED

  VnBuzzer(int pin);
#endif // VN_PORT_DEFINED

  void setpin(int pin);
  void tone(int pin, uint16_t frequency, uint32_t duration);
  void tone(uint16_t frequency, uint32_t duration = 0);
  void noTone(int pin);
  void noTone();
  void test();
};
#endif
