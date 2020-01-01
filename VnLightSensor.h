/**
 * \par Copyright (C), 2018-2020, VrobotX
 * \class   VnLightSensor
 * \brief   Driver for Vn-Light Sensor module.
 * @file    VnLightSensor.h
 * @author  VrobotX
 * @version V1.0.2
 * @date    2018/7/27
 * @brief   Header file for Vn-Light Sensor.cpp
 *
 * \par Copyright
 * This software is Copyright (C), 2018-2020, VrobotX. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * @brief :
 *
 * \par Vnthod List:
 *
 *    1. void    VnLightSensor::setpin(uint8_t ledPin, uint8_t sensorPin)
 *    2. int16_t VnLightSensor::read()
 *    3. void    VnLightSensor::lightOn()
 *    4. void    VnLightSensor::lightOff()
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac      2018/07/27     1.0.0            Build the first library
 * </pre>
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VnLightSensor_H
#define VnLightSensor_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "VnConfig.h"

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED

/**
 * Class: VnLightSensor
 * @brief :
 * Declaration of Class VnLightSensor.
 */
#ifndef VN_PORT_DEFINED
class VnLightSensor
#else // !VN_PORT_DEFINED
class VnLightSensor : public VnPort
#endif // !VN_PORT_DEFINED
{
public:
#ifdef VN_PORT_DEFINED

  VnLightSensor(void);
  VnLightSensor(uint8_t port);
  
#else // VN_PORT_DEFINED

  VnLightSensor(uint8_t ledPin, uint8_t sensorPin);
  
#endif  // VN_PORT_DEFINED

  void setpin(uint8_t ledPin, uint8_t sensorPin);
  int16_t read(void);
  void lightOn(void);
  void lightOff(void);
  
private:

  uint8_t _ledPin;
  uint8_t _sensorPin;
};

#endif // VnLightSensor_H
