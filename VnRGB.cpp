/**
 * \par Copyright (C), 2018-2020, VrobotX
 * \class VnRGB
 * \brief   Port Mapping for RJ25
 * @file    VnRGB.cpp
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
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`         `<Descr>`
 * Phan Dinh Bac    2018/07/19          1.0.0            The first build
 * </pre>
 */
 
#include "VnRGB.h"
 
VnRgbPixelType type = NEO_GRB + NEO_KHZ800;
 
#ifdef VN_PORT_DEFINED
	
VnRGB::VnRGB(uint8_t port) : VnPort(port) 
{
    updateType(type);
    updateLength(2); // we use 2 led in board
    setPin(s2);      //
    begun = false;
    brightness = 0;
    *pixels = NULL;
    endTime = 0;
}

VnRGB::VnRGB() : begun(false), numLEDs(0), numBytes(0), pin(-1), brightness(0), pixels(NULL),
				 rOffset(1), gOffset(0), bOffset(2), wOffset(1), endTime(0)
{
	
}

#else
VnRGB::VnRGB (int pin)
{
	updateType(type);
    updateLength(2); // we use 2 led in board
    setPin(pin);      //
    begun = false;
    brightness = 0;
    *pixels = NULL;
    endTime = 0;		
}
#endif

VnRGB::~VnRGB()
{
	free(pixels);
	if (pin >= 0)
		pinMode(pin, INPUT);
}

/*!
  @brief   Configure pinled for output.
*/
void VnRGB::begin(void)
{
	Serial.println(pin);
	if (pin >= 0) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}
	begun = true;
}

/*!
  @brief   Set/change the output pin number. Previous pin,
           if any, is set to INPUT and the new pin is set to OUTPUT.
  @param   p  Arduino pin number (-1 = no pin).
*/
void VnRGB::setPin(uint16_t p) 
{
	if (begun && (pin >= 0)) 
		pinMode(pin, INPUT);
	pin = p;
	if(begun) {
		pinMode(p, OUTPUT);
		digitalWrite(p, LOW);
	}
}

/*!
  @brief   Change the length of a previously-declared 
           strip object. Old data is deallocated and new data is cleared.
           Pin number and pixel format are unchanged.
  @param   n  New length of strip, in pixels.
  @note    
*/
void VnRGB::updateLength(uint16_t n)
{
	free(pixels);  // Free existing data before updateLength
	numBytes = n * ((wOffset == rOffset) ? 3 : 4);
	
	if ((pixels = (uint8_t *)malloc(numBytes))) {
		memset(pixels, 0, numBytes);
		numLEDs = n;
	}
	else {
		numLEDs = 0;
		numBytes = 0;
	}
	
}

void VnRGB::updateType(VnRgbPixelType t)
{
	boolean oldThreeBytesPerPixel = (wOffset == rOffset);
	
	wOffset = (t >> 6) & 0b11; // See notes in header file
	rOffset = (t >> 4) & 0b11; // regarding R/G/B/W offsets
	gOffset = (t >> 2) & 0b11;
	bOffset =  t       & 0b11;
	
	if (pixels) {
		boolean newThreeBytesPerPixel = (wOffset == rOffset);
		if (newThreeBytesPerPixel != oldThreeBytesPerPixel)
			updateLength(numLEDs);
		
	}
}

void VnRGB::clear(void)
{
	memset(pixels, 0, numBytes);
}
/*!
  @brief   Adjust output brightness. The next call to show() will
           refresh the LEDs at this level.
  @param   brn  Brightness setting, 0 = minimum (off), 255 = brightest.
  @note    
*/
void VnRGB::setBrightness(uint8_t brn)
{
	uint8_t newBrightness = brn + 1;
	uint8_t c = 0, *ptr = pixels, oldBrightness = brightness - 1;
	uint16_t scale = 0, i = 0;
		
	if (newBrightness != brightness) {
	   if (oldBrightness == 0)
		   scale = 0;
	   else if (brn == 255) 
		   scale = 65535 / oldBrightness;
	   else 
		   scale = (((uint16_t)  newBrightness << 8) - 1) / oldBrightness;
	   
	   for ( i = 0; i < numBytes; i++) {
		   c = *ptr;
		   *ptr++ = (c * scale) >> 8;
	   }
	   brightness = newBrightness;
	}
}
/*!
  @brief   Retrieve the last-set brightness value for the strip.
  @return  Brightness value: 0 = minimum (off), 255 = maximum.
*/
uint8_t VnRGB::getBrightness(void)
{
	return (brightness - 1);
}

uint8_t VnRGB::gamma8(uint8_t x) 
{
	return pgm_read_byte(&_vnPixelGammaTable[x]);
}

uint32_t VnRGB::gamma32(uint32_t x)
{
	uint8_t *y = (uint8_t *)&x;
	uint8_t i = 0;
	
	for (i = 0; i < 4; i++)
		y[i] = gamma8(y[i]);
	
	return x;	
}
/*!
  @brief   Set a pixel's color using separate red, green and blue
           components. If using RGBW pixels, white will be set to 0.
  @param   n  Pixel index, starting from 0.
  @param   r  Red brightness, 0 = minimum (off), 255 = maximum.
  @param   g  Green brightness, 0 = minimum (off), 255 = maximum.
  @param   b  Blue brightness, 0 = minimum (off), 255 = maximum.
*/
void VnRGB::setPixelColor( uint16_t n, uint8_t r, uint8_t g, uint8_t b) 
{
    uint8_t *p;
	if  ( n < numLEDs) {
		if(brightness) { // See notes in setBrightness()
			r = (r * brightness) >> 8;
			g = (g * brightness) >> 8;
			b = (b * brightness) >> 8;
		}

    if (wOffset == rOffset) { // Is an RGB-type strip
		p = &pixels[n * 3];    // 3 bytes per pixel
    }
	else {                 // Is a WRGB-type strip
		p = &pixels[n * 4];    // 4 bytes per pixel
		p[wOffset] = 0;        // But only R,G,B passed -- set W to 0
    }
    p[rOffset] = r;          // R,G,B always stored
    p[gOffset] = g;
    p[bOffset] = b;
  }
}
/*!
  @brief   Set a pixel's color using a 32-bit 'packed' RGB or RGBW value.
           Can select direct color: GREEN, RED, BLUE, PINK, YELLOW, WHITE
  @param   n  Pixel index, starting from 0.
  @param   c  32-bit color value. Most significant byte is white (for RGBW
              pixels) or ignored (for RGB pixels), next is red, then green,
              and least significant byte is blue.
*/
void VnRGB::setPixelColor(uint16_t n, uint32_t c) 
{
	uint8_t *p, r = 0, g = 0, b = 0;
    uint8_t w = 0; 
	       
		    switch (c) {
				case GREEN:
				    c = 0x00ff00;
					break;				
				case RED:
				    c = 0xff0000;
					break;
				case BLUE:
				    c = 0x0000ff;
					break;
				case PINK:
				    c = 0xff80c0;
					break;
				case YELLOW:
				    c = 0xffff00;
					break;
				case WHITE:
				    c = 0xffffff;
					break;	
			    default:
					break;
			}
		   
			r = (uint8_t)(c >> 16),
			g = (uint8_t)(c >>  8),
			b = (uint8_t)c;
			w = (uint8_t)(c >> 24); 
	
	if (n < numLEDs) {
		if(brightness) { // See notes in setBrightness()
			r = (r * brightness) >> 8;
			g = (g * brightness) >> 8;
			b = (b * brightness) >> 8;
		}
		if(wOffset == rOffset) {
			p = &pixels[n * 3];
		} 
		else {
			p = &pixels[n * 4];
			p[wOffset] = brightness ? ((w * brightness) >> 8) : w;
		}
		p[rOffset] = r;
		p[gOffset] = g;
		p[bOffset] = b;
   }
}

  /*!
    @brief   Convert separate red, green and blue values into a single
             "packed" 32-bit RGB color.
    @param   r  Red brightness, 0 to 255.
    @param   g  Green brightness, 0 to 255.
    @param   b  Blue brightness, 0 to 255.
    @return  32-bit packed RGB value, which can then be assigned to a
             variable for later use or passed to the setPixelColor()
             function. Packed RGB format is predictable, regardless of
             LED strand color order.
  */
uint32_t VnRGB::Color(uint8_t r, uint8_t g, uint8_t b) 
{
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
  
  /*!
    @brief   Convert separate red, green, blue and white values into a
             single "packed" 32-bit WRGB color.
    @param   r  Red brightness, 0 to 255.
    @param   g  Green brightness, 0 to 255.
    @param   b  Blue brightness, 0 to 255.
    @param   w  White brightness, 0 to 255.
    @return  32-bit packed WRGB value, which can then be assigned to a
             variable for later use or passed to the setPixelColor()
             function. Packed WRGB format is predictable, regardless of
             LED strand color order.
  */
uint32_t VnRGB::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) 
{
    return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

/*!
    @brief   Check whether a call to show() will start sending data
             immediately or will 'block' for a required interval. NeoPixels
             require a short quiet time (about 300 microseconds) after the
             last bit is received before the data 'latches' and new data can
             start being received. Usually one's sketch is implicitly using
             this time to generate a new frame of animation...but if it
             finishes very quickly, this function could be used to see if
             there's some idle time available for some low-priority
             concurrent task.
    @return  1 or true if show() will start sending immediately, 0 or false
             if show() would block (meaning some idle time is available).
 */
boolean VnRGB::canShow(void) 
{ 
	return ((micros() - endTime) >= 300L); 
}

extern "C" void espShow(uint16_t pin, uint8_t *pixels, uint32_t numBytes, uint8_t type);

void VnRGB::show(void) 
{
	if(!pixels) return;
	while(!canShow());

	espShow(pin, pixels, numBytes, is800KHz);
	endTime = micros(); // Save EOD time for latch on next call
}

















