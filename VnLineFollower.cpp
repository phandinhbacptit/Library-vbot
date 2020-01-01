/**
 * @ Copyright (C), 2012-2016, Vrobotx
 * \class VnLineFollower
 * \brief   Driver for Me line follwer device.
 * @file    VnLineFollower.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Driver for Me line follwer device.
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
 * @example LineFollowerTest.ino
 */

#include "VnLineFollower.h"                                    

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * no pins are used or initialized here.
 * @Param :  None
 */
VnLineFollower::VnLineFollower(void) : VnPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnLineFollower::VnLineFollower(uint8_t port) : VnPort(port)
{

}
#else // VN_PORT_DEFINED 
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * it will assigned the input pin.
 * @Param :  Sensor1 - arduino port(should digital pin)
 *           Sensor2 - arduino port(should digital pin)
 */
VnLineFollower::VnLineFollower(uint8_t Sensor1,uint8_t Sensor2)
{
  _Sensor1 = Sensor1;
  _Sensor2 = Sensor2;
  pinMode(_Sensor1,INPUT);
  pinMode(_Sensor2,INPUT);
}
#endif // VN_PORT_DEFINED

/** 
 * @Brief :  Reset the line follwer device available PIN by its arduino port.
 * @Param :  Sensor1 - arduino port(should digital pin)
 *           Sensor2 - arduino port(should digital pin)
 * @Retval : None
 */
void VnLineFollower::setpin(uint8_t Sensor1,uint8_t Sensor2)
{
  _Sensor1 = Sensor1;
  _Sensor2 = Sensor2;
  pinMode(_Sensor1,INPUT);
  pinMode(_Sensor2,INPUT);
#ifdef VN_PORT_DEFINED
  s1 = _Sensor1;
  s2 = _Sensor2;
#endif // VN_PORT_DEFINED
}

/**
 * @Brief :  Get the sensors state.
 * @Retval :
 *   (0x00)-S1_IN_S2_IN:   sensor1 and sensor2 are both inside of black line \n
 *   (0x01)-S1_IN_S2_OUT:  sensor1 is inside of black line and sensor2 is outside of black line \n
 *   (0x02)-S1_OUT_S2_IN:  sensor1 is outside of black line and sensor2 is inside of black line \n
 *   (0x03)-S1_OUT_S2_OUT: sensor1 and sensor2 are both outside of black line
 */
uint8_t VnLineFollower::readSensors(void)
{
  uint8_t state	= S1_IN_S2_IN;
#ifdef VN_PORT_DEFINED
  bool s1State = VnPort::dRead1();
  bool s2State = VnPort::dRead2();
#else // VN_PORT_DEFINED
  bool s1State = digitalRead(_Sensor1);
  bool s2State = digitalRead(_Sensor2);
#endif // VN_PORT_DEFINED
  state = ( (1 & s1State) << 1) | s2State;
  return(state);
}

/**
 * @Brief :  Get the sensors1(left sensors) state.
 * @Retval :
 *   0: sensor1 is inside of black line \n
 *   1: sensor1 is outside of black line
 */
bool VnLineFollower::readSensor1(void)
{
#ifdef VN_PORT_DEFINED
  return(VnPort::dRead1(INPUT) );
#else // VN_PORT_DEFINED
  return digitalRead(_Sensor1);
#endif // VN_PORT_DEFINED
}

/**
 * @Brief :  Get the sensors2(right sensors) state.
 * @Retval :
 *   0: sensor1 is inside of black line \n
 *   1: sensor1 is outside of black line
 */
bool VnLineFollower::readSensor2(void)
{
#ifdef VN_PORT_DEFINED
	return(VnPort::dRead2(INPUT) );
#else // VN_PORT_DEFINED
  return digitalRead(_Sensor2);
#endif // VN_PORT_DEFINED
}

