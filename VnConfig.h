/*
 * @ Param : Copyright (C), 2018-2020, VrobotX
 * \class VnConfig
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
 * @ Param : Vnthod List:
 * @ Param : History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`         `<Descr>`
 * Phan Dinh Bac    2018/07/19          1.0.0            The first build
 * </pre>
 */

#ifndef VnConfig_H
#define VnConfig_H

//#include <utility/Servo.h>
//#include <utility/Wire.h>
//#include <utility/EEPROM.h>
//#include <utility/SoftwareSerial.h>
//#include <utility/SPI.h>

#define VN_PORT_DEFINED

#if defined(__AVR__)
#define VnPIN_TO_BASEREG(pin)               ( portInputRegister (digitalPinToPort (pin) ) )
#define VnPIN_TO_BITMASK(pin)               ( digitalPinToBitMask (pin) )
#define VnIO_REG_TYPE                       uint8_t
#define VnIO_REG_ASM                        asm ("r30")
#define VnDIRECT_READ(base, mask)           ( ( (*(base) ) & (mask) ) ? 1 : 0)
#define VnDIRECT_MODE_INPUT(base, mask)     ( (*( (base) + 1) ) &= ~(mask) ), ( (*( (base) + 2) ) |= (mask) ) // INPUT_PULLUP
#define VnDIRECT_MODE_OUTPUT(base, mask)    ( (*( (base) + 1) ) |= (mask) )
#define VnDIRECT_WRITE_LOW(base, mask)      ( (*( (base) + 2) ) &= ~(mask) )
#define VnDIRECT_WRITE_HIGH(base, mask)     ( (*( (base) + 2) ) |= (mask) )
#endif // __AVR__

#endif // VnConfig_H

