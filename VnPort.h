/**
 * @ Param : Copyright (C), 2018-2020, VrobotX
 * \class VnPort
 * \brief   Port Mapping for RJ25
 * @file    VnPort.h
 * @author  VrobotX
 * @version V1.0.0
 * @date    2018/7/19
 * @brief   Header for VnPort.cpp module
 *
 * @ Param : Copyright
 * This software is Copyright (C), 2018-2020, VrobotX. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * @ Param : Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * @ Brief : 
 * This file is a drive for VrobotX rj25 port.
 *
 * @ Param : Method List:
 *
 *    1.  uint8_t VnPort::getSlot()
 *    2.  uint8_t VnPort::getSlot()
 *    3.  bool VnPort::dRead1(uint8_t mode)
 *    4.  bool VnPort::dRead2(uint8_t mode)
 *    5.  bool VnPort::dpRead1(void)
 *    6.  bool VnPort::dpRead1(void)
 *    7.  void VnPort::dWrite1(bool value)
 *    8.  void VnPort::dWrite2(bool value)
 *    9.  int16_t VnPort::aRead1()
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
 * @ Param : History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`         `<Descr>`
 * Phan Dinh Bac    2018/07/19          1.0.0            The first build
 * </pre>
 */
#ifndef VNPORT_H_
#define VNPORT_H_

#include "Arduino.h"
//#include <avr/interrupt.h>
//#include <avr/io.h>
//#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <VnConfig.h>

#define MOTOR_TYPE_3
/**
 * A structure to represent VnPort Signal.
 */
typedef struct {
  uint8_t s1;
  uint8_t s2;
} VnPort_Sig;

typedef struct {
    uint8_t cw_pin;
    uint8_t ccw_pin;
    uint8_t pwm_pin;
} VnMotor;

extern VnPort_Sig           vnPort[17];  // vnPort[0] is nonsense
extern VnMotor				vnMotor[4];
#define NC                  (0)  //use UART RX for NULL port

#define ULTRA               (0x01)
#define M1                  (0x01)
#define M2                  (0x02)
#define M3                  (0x03)
#define FLOWLINE            (0x04)
#define LIGHT_SENSOR        (0x05)
#define SERVO               (0x06)
#define RGB_LED             (0x07)
#define BUZZER              (0x08)
#define IR_REMOTE           (0x09)
#define BUTTON              (0x0a)
#define MAXTRIX             (0x0b) // s1: SER - s2: CLK 
#define MPU6050             (0x0c)
#define PORT_13             (0x0d)
#define PORT_14             (0x0e)
#define PORT_15             (0x0f)
#define PORT_16             (0x10)

////#ifdef Vbot_H
////#define PORT_RGB            (0x03)
#define PORT_LightSensor    (0x06)
//#endif

#define SLOT1               (1)
#define SLOT2               (2)
#define SLOT3               (3)
#define SLOT4               (4)
#define SLOT_1              SLOT1
#define SLOT_2              SLOT2
#define SLOT_3              SLOT3
#define SLOT_4              SLOT4
            
#ifndef FALSE           
#define FALSE              (0)
#endif          
            
#ifndef TRUE            
#define TRUE               (1)
#endif

// /**
 // @ Class        : VnPort
 // @ Description  : Declaration of Class VnPort
 // */
 class VnPort
 {
 public:
// /**
 // * Alternate Constructor which can call your own function to map the VnPort to arduino port,
 // * no pins are used or initialized here
 // */
   VnPort(void);

  VnPort(uint8_t port);

  VnPort(uint8_t port, uint8_t slot);

  uint8_t getPort(void);

  uint8_t getSlot(void);

  bool dRead1(uint8_t mode = INPUT);

  bool dRead2(uint8_t mode = INPUT);

  bool dpRead1(void);

  bool dpRead2(void);

  void dWrite1(bool value);

  void dWrite2(bool value);

  int16_t aRead1(void);

  int16_t aRead2(void);

  void aWrite1(int16_t value);

  void aWrite2(int16_t value);
  
  void aWrite3(int16_t value);

  void reset(uint8_t port);

  void reset(uint8_t port, uint8_t slot);

  uint8_t pin1(void);

  uint8_t pin2(void);

  uint8_t pin(void);

  uint8_t pin(uint8_t port, uint8_t slot);

 protected:
/**
 *  @ Brief : 
 *  Variables used to store the slot1 gpio number
 */
  uint8_t s1;
/**
 *  @ Brief : 
 *  Variables used to store the slot2 gpio number
 */
  uint8_t s2;
/**
 *  @ Brief : 
 *  Variables used to store the port
 */
  uint8_t _port;
/**
 *  @ Brief : 
 *  Variables used to store the slot
 */
  uint8_t _slot;
  
 /**
 *  @ Brief : 
 *  Variables used to store the slot
 */
  uint8_t cw;
 /**
 *  @ Brief : 
 *  Variables used to store the slot
 */
 uint8_t ccw;
 /**
 *  @ Brief : 
 *  Variables used to store the slot
 */
 uint8_t pwm;
 };
#endif // VNPORT_H_
