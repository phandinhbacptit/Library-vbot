/**
 * @Copyright (C), 2018-2020, VrobotX
 * \class VnUltrasonicSensor
 * \brief   Driver for Vn ultrasonic sensor device.
 * @file    VnUltrasonicSensor.h
 * @author  VrobotX
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Header for for VnUltrasonicSensor.cpp module
 *
 * @Copyright
 * This software is Copyright (C), 2018-2020, VrobotX. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * @Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * @Copyright
 * This software is Copyright (C), 2012-2015, VrobotX. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * @Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * @Description
 * This file is a drive for Vn ultrasonic sensor device, It supports ultrasonic sensor
 * V3.0 provided by the VrobotX.
 *
 * @Vnthod List:
 *
 *    1. void VnUltrasonicSensor::setpin(uint8_t SignalPin)
 *    2. double VnUltrasonicSensor::distanceCm(uint16_t MAXcm)
 *    3. double VnUltrasonicSensor::distanceInch(uint16_t MAXinch)
 *    4. long VnUltrasonicSensor::measure(unsigned long timeout)
 *
 * @History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#ifndef VnUltrasonicSensor_H
#define VnUltrasonicSensor_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "VnConfig.h"

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED

/**
 * Class: VnUltrasonicSensor
 * @Description
 * Declaration of Class VnUltrasonicSensor.
 */
#ifndef VN_PORT_DEFINED
class VnUltrasonicSensor
#else // !VN_PORT_DEFINED
class VnUltrasonicSensor : public VnPort
#endif // !VN_PORT_DEFINED
{
public:
#ifdef VN_PORT_DEFINED

  VnUltrasonicSensor(void);
  VnUltrasonicSensor(uint8_t port);
#else // VN_PORT_DEFINED

  VnUltrasonicSensor(uint8_t trigerPin, uint8_t echoPin);
#endif // VN_PORT_DEFINED

  void setpin(uint8_t SignalPin);
  double distanceCm(uint16_t = 400);
  long measure(unsigned long = 30000);
private:
  volatile uint8_t  _SignalPin;
  volatile uint8_t  _EchoPin;
  volatile bool _measureFlag;
  volatile long _lastEnterTime;
  volatile float _measureValue;
};

#endif 

