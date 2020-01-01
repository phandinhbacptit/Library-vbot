/**
 * \par Copyright (C), 2018-2020, VrobotX
 * \class VnPort
 * \brief   Port Mapping for RJ25
 * @file    VnPort.cpp
 * @author  VrobotX
 * @version V1.0.0
 * @date    2018/7/19
 * @brief   Port Mapping for RJ25
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
 * \par Description
 * This file is a drive for VrobotX rj25 port.
 *
 * \par Method List:
 *
 *    1. uint8_t VnPort::getSlot()
 *    2. uint8_t VnPort::getSlot()
 *    3. bool VnPort::dRead1(uint8_t mode)
 *    4. bool VnPort::dRead2(uint8_t mode)
 *    5. bool VnPort::dpRead1(void)
 *    6. bool VnPort::dpRead1(void)
 *    7. void VnPort::dWrite1(bool value)
 *    8. void VnPort::dWrite2(bool value)
 *    9. int16_t VnPort::aRead1()
 *    10. int16_t VnPort::aRead2()
 *    11. void VnPort::aWrite1(int16_t value)
 *    12. void VnPort::aWrite2(int16_t value)
 *    13. void VnPort::reset(uint8_t port)
 *    14. void VnPort::reset(uint8_t port, uint8_t slot)
 *    15. uint8_t VnPort::pin1()
 *    16. uint8_t VnPort::pin2()
 *    17. uint8_t VnPort::pin()
 *    18. uint8_t VnPort::pin(uint8_t port, uint8_t slot)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`         `<Descr>`
 * Phan Dinh Bac    2018/07/19          1.0.0            The first build
 * </pre>
 */
#include "VnPort.h"

/***********************Port*********************/
/**
 * Alternate Constructor which can call your own function to map the VnPort to arduino port,
 * no pins are used or initialized here
 */
VnPort::VnPort(void)
{
	s1 = vnPort[0].s1;
	s2 = vnPort[0].s2;
	_port = 0;

#ifdef MOTOR_TYPE_3
	cw = vnMotor[0].cw_pin;
	ccw = vnMotor[0].ccw_pin;
	pwm = vnMotor[0].pwm_pin;
#endif
  // Serial.print(s1);
  // Serial.println(s2);
  // Serial.println("Come void");
}

/**
  * @Brief :    Alternate Constructor which can call your own function to map the VnPort to arduino port,
  * 		    no pins are used or initialized here, but PWM frequency set to 976 Hz
  * @Param :	port - RJ25 port from PORT_1 to M2
  * @Retval:	None
  */
VnPort::VnPort(uint8_t port)
{
    s1 = vnPort[port].s1;
    s2 = vnPort[port].s2;
    _port = port;

#ifdef MOTOR_TYPE_3
	cw = vnMotor[port].cw_pin;
	ccw = vnMotor[port].ccw_pin;
	pwm = vnMotor[port].pwm_pin;
#endif
}

/**
  * @Brief :    Alternate Constructor which can call your own function to map the VnPort to arduino port,
  * 		    no pins are used or initialized here, but PWM frequency set to 976 Hz
  * @Param :	port - RJ25 port from PORT_1 to M2
  *				slot - SLOT1 or SLOT2
  * @Retval:	None
  */
VnPort::VnPort(uint8_t port, uint8_t slot)
{
  s1 = vnPort[port].s1;
  s2 = vnPort[port].s2;
  _port = port;
  _slot = slot;
}

/**
  * @Brief :    Get current valid port of current RJ25 objec
  * @Param :	None
  * @Retval:	Port number from PORT_1 to M2
  */
uint8_t VnPort::getPort()
{
  return(_port);
}

/**
  * @Brief :    Get current valid slot of current RJ25 object's port
  * @Param :	None
  * @Retval:	Slot bumber SLOT1 or SLOT2
  */
uint8_t VnPort::getSlot(void)
{
  return(_slot);
}

/**
  * @Brief :    Read the digital input value on slot1 of current RJ25 object's port
  * @Param :	mode - digital input mode INPUT or INPUT_PULLUP
  * @Retval:	Digital input value
  */
bool VnPort::dRead1(uint8_t mode)
{
  bool val;
  pinMode(s1, mode);
  val = digitalRead(s1);
  return(val);
}

/**
  * @Brief :    Read the digital input value on slot2 of current RJ25 object's port
  * @Param :	mode - digital input mode INPUT or INPUT_PULLUP
  * @Retval:	Digital input value
  */
bool VnPort::dRead2(uint8_t mode)
{
  bool val;
  pinMode(s2, mode);
  val = digitalRead(s2);
  return(val);
}

/**
  * @Brief :    Read the digital input value on slot1 of current RJ25 object's port, the input 
  *             mode set as INPUT_PULLUP.
  * @Param :	None
  * @Retval:	Digital input value
  */
bool VnPort::dpRead1(void)
{
  bool val;
  pinMode(s1, INPUT_PULLUP);
  val = digitalRead(s1);
  return(val);
}

/**
  * @Brief :    Read the digital input value on slot2 of current RJ25 object's port, the input 
  *             mode set as INPUT_PULLUP.
  * @Param :	None
  * @Retval:	Digital input value
  */
bool VnPort::dpRead2(void)
{
  bool val;
  pinMode(s2, INPUT_PULLUP);
  val = digitalRead(s2);
  return(val);
}

/**
  * @Brief :    Set the digital output value on slot1 of current RJ25 object's port 
  * @Param :	value - digital output value HIGH or LOW
  * @Retval:	None
  */
void VnPort::dWrite1(bool value)
{
	pinMode(s1, OUTPUT);
	digitalWrite(s1, value);
#ifdef MOTOR_TYPE_3
	pinMode(cw, OUTPUT);
	digitalWrite(cw, value);
#endif
}

/**
  * @Brief :    Set the digital output value on slot2 of current RJ25 object's port 
  * @Param :	value - digital output value HIGH or LOW
  * @Retval:	None
  */
void VnPort::dWrite2(bool value)
{
	pinMode(s2, OUTPUT);
	digitalWrite(s2, value);
#ifdef MOTOR_TYPE_3
	pinMode(ccw, OUTPUT);
	digitalWrite(ccw, value);
#endif
}
/**
  * @Brief :    Read the analog value on slot1 of current RJ25 object's port 
  * @Param :	None
  * @Retval:	Analog value from 0-1023
  */
int16_t VnPort::aRead1(void)
{
	int16_t val;
  
	pinMode(s1, INPUT);
	val = analogRead(s1);

	return(val);
}

/**
  * @Brief :   Read the analog value on slot2 of current RJ25 object's port 
  * @Param :	None
  * @Retval:	Analog value from 0-1023
  */
int16_t VnPort::aRead2(void)
{
	int16_t val;
	pinMode(s2, INPUT);
	val = analogRead(s2);
	return(val);
}

/**
  * @Brief :    Set the PWM output value on slot1 of current RJ25 object's port 
  * @Param :	None
  * @Retval:	None
  */
int channel1 = 1;
void VnPort::aWrite1(int16_t value)
{
	ledcSetup(channel1, 2000, 8);
	ledcAttachPin(s1, channel1);
	
#ifdef MOTOR_TYPE_3
	ledcAttachPin(pwm, channel1);
#endif

	ledcWrite(channel1, value);
}

/**
  * @Brief :    Set the PWM output value on slot2 of current RJ25 object's port 
  * @Param :	None
  * @Retval:	None
  */
  
int channel2 = 2;
void VnPort::aWrite2(int16_t value)
{
	ledcSetup(channel2, 2000, 8);
	ledcAttachPin(s2, channel2);
	
#ifdef MOTOR_TYPE_3
	ledcAttachPin(pwm, channel2);
#endif

	ledcWrite(channel2, value);
}

/**
  * @Brief :    Set the PWM output value on slot2 of current RJ25 object's port 
  * @Param :	None
  * @Retval:	None
  */
  
int channel3 = 3;
void VnPort::aWrite3(int16_t value)
{
	ledcSetup(channel3, 2000, 8);
	ledcAttachPin(pwm, channel3);
	ledcWrite(channel3, value);
}

/**
 * @Brief :     Reset the RJ25 available PIN by its port
 * @Param :		port - RJ25 port from PORT_1 to M2
 * @Retval:		None
 */
void VnPort::reset(uint8_t port)
{
	Serial.print(port);
	s1 = vnPort[port].s1;
	s2 = vnPort[port].s2;
	_port = port;
#ifdef MOTOR_TYPE_3
	cw = vnMotor[port].cw_pin;
	ccw = vnMotor[port].ccw_pin;
	pwm = vnMotor[port].pwm_pin;
#endif
}

/**  
 * @Brief :    Reset the RJ25 available PIN by its port and slot
 * @Param :    port - RJ25 port from PORT_1 to M2
 *   		   slot - SLOT1 or SLOT2
 * @Retval:    None
 */
void VnPort::reset(uint8_t port, uint8_t slot)
{
  s1 = vnPort[port].s1;
  s2 = vnPort[port].s2;
  _port = port;
  _slot = slot;
}

/**
 * @Brief :    Return the arduino pin number of current RJ25 object's slot1
 * @Param :    Output
 * @Retval:    The PIN number of arduino
 */
uint8_t VnPort::pin1(void)
{
  return(s1);
}

/**
 * @Brief :    Return the arduino pin number of current RJ25 object's slot2
 * @Param :    None
 * @Retval:    The PIN number of arduino
 */
uint8_t VnPort::pin2(void)
{
  return(s2);
}

/**
 * @Brief :    Return the arduino pin number of current RJ25 object's port, if the RJ25 module
 *             have one available PIN.
 * @Param :    None
 * @Retval:    The PIN number of arduino
 */
uint8_t VnPort::pin(void)
{
  return(_slot == SLOT_1 ? s1 : s2);
}

/**
 * @Brief :    Return the arduino pin number of current RJ25 object's port
 * @Param :    port - RJ25 port from PORT_1 to M2
 *             slot - SLOT1 or SLOT2
 * @Param :    None
 * @Retval:    The PIN number of arduino
 */
uint8_t VnPort::pin(uint8_t port, uint8_t slot)
{
  return(slot == SLOT_1 ? vnPort[port].s1 : vnPort[port].s2);
}

