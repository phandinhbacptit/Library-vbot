/**
 * @ Copyright (C), 2012-2016, Vrobotx
 * \class VnLineFollower
 * \brief   Driver for Me line follwer device.
 * @file    VnLineFollower.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Header for for VnLineFollower.cpp module
 *
 * @ Copyright
 * This software is Copyright (C), 2012-2016, Vrobotx. Use is subject to license \n
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
 * This file is a drive for Me line follwer device, It supports line follwer device
 * V2.2 provided by the Vrobotx. The line follwer used Infrared Tube to Use infrared
 * receiver and transmitter to detect the black line.
 *
 * @ Method List:
 *
 *    1. void VnLineFollower::setpin(uint8_t Sensor1,uint8_t Sensor2)
 *    2. uint8_t VnLineFollower::readSensors(void)
 *    3. bool VnLineFollower::readSensor1(void)
 *    4. bool VnLineFollower::readSensor1(void)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac         2018/07/20     1.0.0            Rebuild the old lib.
 * </pre>
 *
 */
#ifndef MeLineFollower_H
#define MeLineFollower_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "VnConfig.h"

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED

#define S1_IN_S2_IN   (0x00)    // sensor1 and sensor2 are both inside of black line
#define S1_IN_S2_OUT  (0x01)    // sensor1 is inside of black line and sensor2 is outside of black line
#define S1_OUT_S2_IN  (0x02)    // sensor1 is outside of black line and sensor2 is inside of black line
#define S1_OUT_S2_OUT (0x03)    // sensor1 and sensor2 are both outside of black line

/**
 * Class: VnLineFollower
 * @Brief :
 * Declaration of Class VnLineFollower.
 */
#ifndef VN_PORT_DEFINED
class VnLineFollower
#else // !VN_PORT_DEFINED
class VnLineFollower : public VnPort
#endif  // VN_PORT_DEFINED
{
public:
#ifdef VN_PORT_DEFINED

  VnLineFollower(void);
  VnLineFollower(uint8_t port);
  
#else // VN_PORT_DEFINED 

  VnLineFollower(uint8_t Sensor1,uint8_t Sensor2);
  
#endif  // VN_PORT_DEFINED

  void setpin(uint8_t Sensor1,uint8_t Sensor2);
  uint8_t readSensors(void);
  bool readSensor1(void);
  bool readSensor2(void);
private:
  volatile uint8_t  _Sensor1;
  volatile uint8_t  _Sensor2;
};
#endif
