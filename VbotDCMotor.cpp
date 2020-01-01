/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \brief   Driver for Vbot DC Motor.
 * \file    VbotDCMotor.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Driver for Vbot DC Motor.
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
 * This file is Hardware adaptation layer between Vbot board and all
 * Vrobotx drives
 * 
 * @ Method List:
 *
 *    1. void VBotDCMotor::move(int direction, int speed);
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */

#include "VbotDCMotor.h"

/**
 * Alternate Constructor which can call your own function to map the MBot DCMotor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * @Param : port - RJ25 port from PORT_1 to M2
 */
#ifdef VN_PORT_DEFINED
VBotDCMotor::VBotDCMotor(void) 
{

}

VBotDCMotor::VBotDCMotor(uint8_t port) : VnDCMotor(port)
{

}

/**
 * @Brief :  MBot DCMotor moves with the speed and direction.
 * @Param :  direction - The direction of the MBot DCMotor's movement
 *           speed - The speed of MBot DCMotor's movement.
 * @Retval : None
 * @Others : None
 */
void VBotDCMotor::move(int direction, int speed)
{
  int leftSpeed = 0;
  int rightSpeed = 0;
  if(direction==1)
  {
    leftSpeed = -speed;
    rightSpeed = speed;
  }
  else if(direction==2)
  {
    leftSpeed = speed;
    rightSpeed = -speed;
  }
  else if(direction==3)
  {
    leftSpeed = speed;
    rightSpeed = speed;
  }
  else if(direction==4)
  {
    leftSpeed = -speed;
    rightSpeed = -speed;
  }
  VnDCMotor::reset(M1);
  VnDCMotor::run(leftSpeed, MOTOR1);
  VnDCMotor::reset(M2);
  VnDCMotor::run(rightSpeed, MOTOR2);
}
#endif //VN_PORT_DEFINED

