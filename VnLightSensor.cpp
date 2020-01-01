/**
 * \par Copyright (C), 2018-2020, VrobotX
 * \class   VnLightSensor
 * \brief   Driver for Vn-Light Sensor module.
 * @file    VnLightSensor.cpp
 * @author  VrobotX
 * @version V1.0.2
 * @date    2018/7/27
 * @brief   Driver for Vn-Light Sensor module.
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

/* Private define ------------------------------------------------------------*/
#include "VnLightSensor.h"

/* Private functions ---------------------------------------------------------*/
#ifdef VN_PORT_DEFINED

/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port,
 * no pins are used or initialized here.
 * @param :  None
 */
VnLightSensor::VnLightSensor(void) : VnPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port
 * @param :  port - RJ25 port from PORT_1 to M2
 */
VnLightSensor::VnLightSensor(uint8_t port) : VnPort(port)
{

}
#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port
 * @param :  ledPin - arduino port for led input
 * @param :  sensorPin - arduino port for sensor data read
 */
VnLightSensor::VnLightSensor(uint8_t ledPin, uint8_t sensorPin)
{
  _ledPin = ledPin;
  _sensorPin = sensorPin;

  pinMode(_ledPin, OUTPUT);
  pinMode(_sensorPin, INPUT);

  digitalWrite(_ledPin, LOW);
}
#endif //VN_PORT_DEFINED

/**
 * @brief :  Set pin mode connect with light sensor
 * @param :  ledPin - Which pin on board that LEDpin is connecting to.
 *           sensorPin - Which pin on board that sensorPin is connecting to.
 * @reval :  None
 * @others : Set global variable _KeyPin and s2
 */
void VnLightSensor::setpin(uint8_t ledPin, uint8_t sensorPin)
{
  _ledPin = ledPin;
  _sensorPin = sensorPin;

  pinMode(_ledPin, OUTPUT);
  pinMode(_sensorPin, INPUT);

#ifdef VN_PORT_DEFINED
  s1 = _ledPin;
  s2 = _sensorPin;
#endif 
}

/**
 * @brief :  Read analog value of light sensor.
 * @param :  None
 * @reval :  VnPort::aRead2() - DAC value of current light sensor's output.
 * @others :
 */
int16_t VnLightSensor::read(void)
{
#ifdef VN_PORT_DEFINED
  return(VnPort::aRead2());
#else 
  return(analogRead(_sensorPin));
#endif 

}

/**
 * @brief :  Turn on the LED on the light sensor.
 * @param :  None
 * @reval :  None
 * @others :
 */
void VnLightSensor::lightOn(void)
{
#ifdef VN_PORT_DEFINED
  VnPort::dWrite1(HIGH);
#else 
  digitalWrite(_ledPin,HIGH);
#endif 
}

/**
 * @brief :  Turn off the LED on the light sensor.
 * @param :  None
 * @reval :  None
 * @others :
 */
void VnLightSensor::lightOff(void)
{
#ifdef VN_PORT_DEFINED
  VnPort::dWrite1(LOW);
#else 
  digitalWrite(_ledPin,LOW);
#endif 
}
