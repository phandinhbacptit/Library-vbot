/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class VnDCMotor
 * \brief   Driver for Me DC motor device.
 * @file    VnDCMotor.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Driver for Me DC motor device.
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
 * This file is a drive for Vn DC motor device.
 *
 * @ Method List:
 *
 *    1. void VnDCMotor::setpin(uint8_t dir_pin,uint8_t pwm_pin)
 *    2. void VnDCMotor::run(int16_t speed)
 *    3. void VnDCMotor::stop(void)
 *    4. void VnDCMotor::reset(uint8_t port)
 *    5. void VnDCMotor::reset(uint8_t port, uint8_t slot)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#include "VnDCMotor.h"

//#define __AVR_ATmega328__

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port,
 * no pins are used or initialized here.
 * @Param :  None
 */
VnDCMotor::VnDCMotor(void) : VnPort(0)
{
}

/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnDCMotor::VnDCMotor(uint8_t port) : VnPort(port)
{
// #ifdef MOTOR_TYPE_3	
	// dc_cw_pin = cw;
	// dc_ccw_pin = ccw;
	// dc_pwm_pin = pwm;
	
	// pinMode(dc_cw_pin, OUTPUT);
	// pinMode(dc_ccw_pin, OUTPUT);
	
	// ledcSetup(dc_pwm_pin, 2000, 8);
	// ledcAttachPin(pwm_pin, dc_pwm_pin);
// #else
	// Serial.println(" s1");
	// Serial.print(s1);
	// Serial.println(" s2");
	// Serial.print(s2);
// #endif	
}
#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port,
 * it will assigned the output pin.
 * @Param :  dir_pin - arduino port for direction pin(should analog pin)
 *           pwm_pin - arduino port for pwm input(should analog pin)
 */
	#ifdef MOTOR_TYPE_3
		VnDCMotor::VnDCMotor(uint8_t cw_pin, uint8_t ccw_pin,uint8_t pwm_pin, int channel)
		{
			dc_cw_pin = cw_pin;
			dc_ccw_pin = ccw_pin;
			dc_pwm_pin = pwm_pin;
			
			pinMode(dc_cw_pin, OUTPUT);
			pinMode(dc_ccw_pin, OUTPUT);
			
			ledcSetup(channel, 2000, 8);
			ledcAttachPin(dc_pwm_pin, channel);
		}
	#else
		VnDCMotor::VnDCMotor(uint8_t dir_pin, uint8_t pwm_pin, int channel)
		{
			dc_dir_pin = dir_pin;
			dc_pwm_pin = pwm_pin;
			
			pinMode(dc_dir_pin, OUTPUT);
			ledcSetup(channel, 2000, 8);
			ledcAttachPin(dc_pwm_pin, channel);
		}
	#endif
       		
#endif /* VN_PORT_DEFINED */

/**
 * @Brief :  Reset the DC motor available PIN by its arduino port.
 * @Param :  dir_pin - arduino port for direction pin(should analog pin)
 *           pwm_pin - arduino port for pwm input(should analog pin)
 * @Retval : None
 * @Others : None
 */
void VnDCMotor::setpin(uint8_t cw_pin, uint8_t ccw_pin,uint8_t pwm_pin)
{
#ifdef VN_PORT_DEFINED

	#ifdef MOTOR_TYPE_3
	  cw  = cw_pin;
	  ccw = ccw_pin;
	  pwm = pwm_pin;
	#endif
	
#else
	
	#ifdef MOTOR_TYPE_3	 
	  dc_cw_pin = cw_pin;
	  dc_ccw_pin = ccw_pin;
	  pinMode(dc_cw_pin, OUTPUT);
	  pinMode(dc_ccw_pin, OUTPUT);
	#endif
#endif // VN_PORT_DEFINED
}

/**
 * @Brief :  Reset the DC motor available PIN by its RJ25 port.
 * @Param :  port - RJ25 port from PORT_1 to M2
 * @Retval : None
 * @Others : None
 */
 #ifdef VN_PORT_DEFINED
void VnDCMotor::reset(uint8_t port)
{
  VnPort::reset(port);
  last_speed = 500;
}

/**
 * @Brief :  Reset the DC motor available PIN by its RJ25 port and slot.
 * @Param :  port - RJ25 port from PORT_1 to M2
 *           slot - SLOT1 or SLOT2
 * @Retval : None
 * @Others : None
 */
void VnDCMotor::reset(uint8_t port, uint8_t slot)
{
  VnPort::reset(port, slot);
  last_speed = 500;
}
#endif
/**
 * @Brief :  Control the motor forward or reverse
 * @Param :  speed - Speed value from -255 to 255
 * @Retval : None
 * @Others : None
 */
void VnDCMotor::run(int16_t speed, uint8_t motor)
{
  speed	= speed > 255 ? 255 : speed;	
  speed	= speed < -255 ? -255 : speed;

  if(last_speed != speed)
  {
    last_speed = speed;
  }
  else
  {
    return;
  }

  if(speed >= 0)
  {
	  
Serial.println(" speed > 0");
#ifdef VN_PORT_DEFINED
	#ifdef MOTOR_TYPE_3
		VnPort::dWrite1(HIGH);
		VnPort::dWrite2(LOW);
		delayMicroseconds(5);
		switch(motor) {
			case MOTOR1:
				VnPort::aWrite1(speed);
				break;
			case MOTOR2:
				VnPort::aWrite2(speed);
				break;
				
			case MOTOR3:
				VnPort::aWrite3(speed);
				break;
		    default:
				break;
		}
	#else
		VnPort::dWrite1(HIGH);
		delayMicroseconds(5);
		VnPort::aWrite2(speed);
	#endif
#else /* VN_PORT_DEFINED */;
	#ifdef MOTOR_TYPE_3
		digitalWrite(dc_cw_pin, HIGH);
		digitalWrite(dc_ccw_pin, LOW);
		delayMicroseconds(5);
		ledcWrite(dc_pwm_pin, speed);
	#else
		digitalWrite(dc_dir_pin, HIGH);
	    delayMicroseconds(5);
		ledcWrite(dc_pwm_pin, speed);
	#endif
#endif/* VN_PORT_DEFINED */
  }
  else
  {
#ifdef VN_PORT_DEFINED
	#ifdef MOTOR_TYPE_3
		Serial.println(" Speed < 0");
		VnPort::dWrite1(LOW);
		VnPort::dWrite2(HIGH);
		delayMicroseconds(5);
		switch(motor) {
			case MOTOR1:
				VnPort::aWrite1(-speed);
				break;
			case MOTOR2:
				VnPort::aWrite2(-speed);
				break;
				
			case MOTOR3:
				VnPort::aWrite3(-speed);
				break;
		    default:
				break;
		}
	#else
		VnPort::dWrite1(LOW);
		delayMicroseconds(5);
		VnPort::aWrite2(-speed);
	#endif
#else /* VN_PORT_DEFINED */
	#ifdef MOTOR_TYPE_3
		digitalWrite(dc_cw_pin, LOW);
		digitalWrite(dc_ccw_pin, HIGH);
		delayMicroseconds(5);
		ledcWrite(dc_pwm_pin,-speed);
	#else
		digitalWrite(dc_dir_pin, LOW);
	    delayMicroseconds(5);
		ledcWrite(dc_pwm_pin, speed);
	#endif
#endif/* VN_PORT_DEFINED */
  }
}

/**
 * @Brief :  Stop the rotation of the motor
 * @Retval : None
 * @Others : None
 */
void VnDCMotor::stop(uint8_t motor)
{
  switch(motor){
	case MOTOR1:
		VnDCMotor::run(0, MOTOR1);
		break;
	case MOTOR2: 
	  VnDCMotor::run(0, MOTOR2);
	  break;
	case MOTOR3:
	  VnDCMotor::run(0, MOTOR3);
	  break;
	default:
	  break;
  }
}

