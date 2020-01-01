/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \brief   Driver for Vbot DC Motor.
 * \file    VbotDCMotor.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VbotDCMotor.cpp module
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

#ifndef MeMbotDCMotor_H
#define MeMbotDCMotor_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "VnConfig.h"


#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#include "VnDCMotor.h"
#endif




/**
 * Class: VBotDCMotor
 * @Brief :
 * Declaration of Class VBotDCMotor.
 */
#ifdef VN_PORT_DEFINED
class VBotDCMotor : public VnDCMotor
{
public:
  VBotDCMotor(void);
  VBotDCMotor(uint8_t port);
  void move(int direction, int speed);
};
#endif
#endif //VN_PORT_DEFINED
