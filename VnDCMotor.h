/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class VnDCMotor
 * \brief   Driver for Me DC motor device.
 * @file    VnDCMotor.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Header for VnDCMotor.cpp module
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
 * This file is a drive for Me DC motor device.
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
 *
 */
#ifndef VnDCMotor_H
#define VnDCMotor_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "VnConfig.h"

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif


#define MOTOR1	1
#define MOTOR2 	2
#define MOTOR3	3
/**
 * Class: VnDCMotor
 * @Brief :
 * Declaration of Class VnDCMotor
 */
#ifndef VN_PORT_DEFINED
class VnDCMotor
#else // !VN_PORT_DEFINED
class VnDCMotor : public VnPort
#endif // !VN_PORT_DEFINED
{
public:
#ifdef VN_PORT_DEFINED
	VnDCMotor(void);
	VnDCMotor(uint8_t port);	
#else // VN_PORT_DEFINED
	#ifdef MOTOR_TYPE_3
		VnDCMotor(uint8_t cw_pin, uint8_t ccw_pin,uint8_t pwm_pin, int channel);
	#else
		VnDCMotor(uint8_t dir_pin, uint8_t pwm_pin, int channel);
	#endif	
#endif // VN_PORT_DEFINED

  void setpin(uint8_t cw_pin, uint8_t ccw_pin,uint8_t pwm_pin);
  void reset(uint8_t port);
  void reset(uint8_t port, uint8_t slot);
  void run(int16_t speed, uint8_t motor);
  void stop(uint8_t motor);
private:
#ifdef MOTOR_TYPE_3
  volatile uint8_t dc_cw_pin;
  volatile uint8_t dc_ccw_pin;
  volatile uint8_t dc_pwm_pin;
#else  
  volatile uint8_t dc_dir_pin;
  volatile uint8_t dc_pwm_pin;
#endif
  int16_t  last_speed;
};
#endif

