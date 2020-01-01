/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnRGB
 * \brief   Driver for Vn Buzzer module.
 * @file    VnRGB.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VnRGB.cpp module
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
 * This file is a drive for Vn Buzzer device, The Vn Buzzer inherited the 
 * VnSerial class from SoftwareSerial.
 *
 * @ List function:
 *

 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#ifndef _VnRGB_H_
#define _VnRGB_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
 #include "VnPort.h"
#endif /* VN_PORT_DEFINED */

// RGB NeoPixel permutations; white and red offsets are always same
// Offset:         W        R        G        B
#define NEO_RGB  ((0<<6) | (0<<4) | (1<<2) | (2)) ///< Transmit as R,G,B
#define NEO_RBG  ((0<<6) | (0<<4) | (2<<2) | (1)) ///< Transmit as R,B,G
#define NEO_GRB  ((1<<6) | (1<<4) | (0<<2) | (2)) ///< Transmit as G,R,B
#define NEO_GBR  ((2<<6) | (2<<4) | (0<<2) | (1)) ///< Transmit as G,B,R
#define NEO_BRG  ((1<<6) | (1<<4) | (2<<2) | (0)) ///< Transmit as B,R,G
#define NEO_BGR  ((2<<6) | (2<<4) | (1<<2) | (0)) ///< Transmit as B,G,R

typedef enum color {
	GREEN = 1,
	RED,
	BLUE, 
	YELLOW, 
	PINK,
	WHITE
};

#define NEO_KHZ800 0x0000 ///< 800 KHz data transmission
#ifndef __AVR_ATtiny85__
#define NEO_KHZ400 0x0100 ///< 400 KHz data transmission
#endif

static const uint8_t PROGMEM _vnPixelGammaTable[256] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,
    3,  3,  4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  7,
    7,  7,  8,  8,  8,  9,  9,  9, 10, 10, 10, 11, 11, 11, 12, 12,
   13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20,
   20, 21, 21, 22, 22, 23, 24, 24, 25, 25, 26, 27, 27, 28, 29, 29,
   30, 31, 31, 32, 33, 34, 34, 35, 36, 37, 38, 38, 39, 40, 41, 42,
   42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
   58, 59, 60, 61, 62, 63, 64, 65, 66, 68, 69, 70, 71, 72, 73, 75,
   76, 77, 78, 80, 81, 82, 84, 85, 86, 88, 89, 90, 92, 93, 94, 96,
   97, 99,100,102,103,105,106,108,109,111,112,114,115,117,119,120,
  122,124,125,127,129,130,132,134,136,137,139,141,143,145,146,148,
  150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,
  182,184,186,188,191,193,195,197,199,202,204,206,209,211,213,215,
  218,220,223,225,227,230,232,235,237,240,242,245,247,250,252,255};


#ifdef NEO_KHZ400
typedef uint16_t VnRgbPixelType; ///< 3rd arg to Adafruit_NeoPixel constructor
#else
typedef uint8_t  VnRgbPixelType; ///< 3rd arg to Adafruit_NeoPixel constructor
#endif


#ifdef VN_PORT_DEFINED
  class VnRGB : public VnPort
#else
 class VnRGB
#endif
{
public:

#ifdef VN_PORT_DEFINED
	VnRGB(void);
	VnRGB(uint8_t port);
#else /* VN_PORT_DEFINED */
    VnRGB (int pin);
#endif /* VN_PORT_DEFINED */

  ~VnRGB();
  
  void begin(void);
  void clear(void);
  void setBrightness(uint8_t brn);
  uint8_t getBrightness(void);
  uint32_t gamma32(uint32_t x);
  uint8_t gamma8(uint8_t x); 
  void setPin(uint16_t p);
  void updateLength(uint16_t n);
  void updateType(VnRgbPixelType t);
  
  void setPixelColor( uint16_t n, uint8_t r, uint8_t g, uint8_t b) ;
  void setPixelColor(uint16_t n, uint32_t c); 
  uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
  uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w); 
  boolean canShow(void);
  void show(void); 
  protected:
  
#ifdef NEO_KHZ400  // If 400 KHz NeoPixel support enabled...
  boolean           is800KHz;   ///< true if 800 KHz pixels
#endif
  boolean           begun;      ///< true if begin() previously called
  uint16_t          numLEDs;    ///< Number of RGB LEDs in strip
  uint16_t          numBytes;   ///< Size of 'pixels' buffer below
  int16_t           pin;        ///< Output pin number (-1 if not yet set)
  uint8_t           brightness; ///< Strip brightness 0-255 (stored as +1)
  uint8_t          *pixels;     ///< Holds LED color values (3 or 4 bytes each)
  uint8_t           rOffset;    ///< Red index within each 3- or 4-byte pixel
  uint8_t           gOffset;    ///< Index of green byte
  uint8_t           bOffset;    ///< Index of blue byte
  uint8_t           wOffset;    ///< Index of white (==rOffset if no white)
  uint32_t          endTime;    ///< Latch timing reference
#ifdef __AVR__
  volatile uint8_t *port;       ///< Output PORT register
  uint8_t           pinMask;    ///< Output PORT bitmask
#endif
#ifdef ARDUINO_ARCH_STM32
  GPIO_TypeDef *gpioPort;       ///< Output GPIO PORT
  uint32_t gpioPin;             ///< Output GPIO PIN
#endif

  private:

};


#endif /* _VnRGB_H_ */