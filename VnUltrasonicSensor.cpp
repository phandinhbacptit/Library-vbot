/**
 * @Copyright (C), 2018-2020, VrobotX
 * \class VnUltrasonicSensor
 * \brief   Driver for Vn ultrasonic sensor device.
 * @file    VnUltrasonicSensor.cpp
 * @author  VrobotX
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Driver for Vn ultrasonic sensor device.
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
 * @brief :
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
 *
 * @example UltrasonicSensorTest.ino
 */
#include "VnUltrasonicSensor.h"

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic sensor to arduino port,
 * no pins are used or initialized here.
 * @param :  None
 */
VnUltrasonicSensor::VnUltrasonicSensor(void) : VnPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port
 * @param :  port - RJ25 port from PORT_1 to M2
 */
VnUltrasonicSensor::VnUltrasonicSensor(uint8_t port) : VnPort(port)
{

}
#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port,
 * it will assigned the signal pin.
 * @param :  port - arduino port(should analog pin)
 */
VnUltrasonicSensor::VnUltrasonicSensor(uint8_t trigerPin, uint8_t echoPin)
{
  _SignalPin = trigerPin;
  _EchoPin = echoPin;
  pinMode(_SignalPin, OUTPUT);
  pinMode(_EchoPin, INPUT);
  _lastEnterTime = millis();
  _measureFlag = true;
  _measureValue = 0;
}
#endif // VN_PORT_DEFINED

/**
 * @brief :  Reset the ultrasonic Sensor available PIN by its arduino port.
 * @param :  SignalPin - arduino port for sensor read(should analog pin)
 * @retval : None
 * @Others : None
 */
void VnUltrasonicSensor::setpin(uint8_t SignalPin)
{
  _SignalPin = SignalPin;
  _lastEnterTime = millis();
  _measureFlag = true;
  _measureValue = 0;
#ifdef VN_PORT_DEFINED
  s2 = _SignalPin;
#endif // VN_PORT_DEFINED
}

/**
 * @brief :  Centimeters return the distance
 * @param :  MAXcm - The Max centimeters can be measured, the default value is 400.
 * @retval : The distance measurement in centimeters
 * @Others : None
 */
double VnUltrasonicSensor::distanceCm(uint16_t MAXcm)
{
  long distance = measure(MAXcm * 55 + 200);
  if(distance == 0)
  {
    distance = MAXcm * 58;
  }
    return( (double)((distance /36.9 /2 - 5.5) / 0.7 + 2.5) );
}


/**
 * @brief :  To get the duration of the ultrasonic sensor
 * @param :  timeout - This value is used to define the measurement range, The
 *           default value is 30000.
 * @retval : The duration value associated with distance
 * @Others : None
 */
long VnUltrasonicSensor::measure(unsigned long timeout)
{
  long duration;
  if(millis() - _lastEnterTime > 23)
  {
    _measureFlag = true; 
  }

  if(_measureFlag == true)
  {
    _lastEnterTime = millis();
    _measureFlag = false;
#ifdef VN_PORT_DEFINED
    // VnPort::dWrite2(HIGH);
    // delayMicroseconds(2);
    VnPort::dWrite2(HIGH);
    delayMicroseconds(2);
    VnPort::dWrite2(LOW);
    pinMode(s1, INPUT);
    duration = pulseIn(s1, LOW, timeout);
#else
	// digitalWrite(_SignalPin, LOW);
    // delayMicroseconds(2);
    digitalWrite(_SignalPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(_SignalPin, LOW);
    duration = pulseIn(_EchoPin, LOW, timeout);
#endif
    _measureValue = duration;
  }
  else
  {
    duration = _measureValue;
  }
  return(duration);
}

