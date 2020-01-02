/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   Vn74hc595
 * \brief   Driver for Vn Buzzer module.
 * @file    Vn74hc595.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2019/12/30
 * @brief   Driver for Vn Buzzer module.
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
 * MeSerial class from SoftwareSerial.
 *
 * @ Method List:
 *
 *    1. Vn74hc595::Vn74hc595(void);
 *	  2. Vn74hc595::Vn74hc595(uint8_t port):VnPort(port);
 *	  3. Vn74hc595::Vn74hc595(uint8_t ser_pin, uint8_t clk_pin, uint8_t latch_pin);
 *	  4. void Vn74hc595::screenClear(void);
 *	  5. void Vn74hc595::displayImage(unsigned int image[], int duration);
 *	  6. void Vn74hc595:: scrollImage(unsigned int image[], uint8_t duration, uint8_t dir_shift);
 *
 * @ History:
 * <pre>
 * <Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac     2019/12/30         1.0.0             Build the first library.
 * </pre>
 */
#include "Vn74hc595.h"


#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * Buzzer pins are used and initialized here.
 * @Param : None
 */
Vn74hc595::Vn74hc595(void)
{
	_serPin		=	12;
	_clkPin 	=	2;
	_latchPin	=	13;
   
   	pinMode(_clkPin, OUTPUT);
	pinMode(_serPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	
	// Serial.print("ser: ");
	// Serial.print(_serPin);
	// Serial.print("clk: ");
	// Serial.print(_clkPin);
	// Serial.print("latch: ");
	// Serial.print(_latchPin);
}

/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to MATRIX
 */
Vn74hc595::Vn74hc595(uint8_t port):VnPort(port)
{
	_serPin		=	s1;
	_clkPin 	=	s2;
	_latchPin	=	13;
   
    pinMode(_clkPin, OUTPUT);
	pinMode(_serPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	
	// Serial.print("ser: ");
	// Serial.print(_serPin);
	// Serial.print("clk: ");
	// Serial.print(_clkPin);
	// Serial.print("latch: ");
	// Serial.print(_latchPin);
}

#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * @Param :  ser_pin 	- Pin correspond to the serial input data
 *			 clk_pin 	- Shift register clock
 *			 latch_pin 	- Pin emit signal load data from the shift to the storage register
 */
Vn74hc595::Vn74hc595(uint8_t ser_pin, uint8_t clk_pin, uint8_t latch_pin)
{
  	_serPin		=	ser_pin;
	_clkPin 	=	clk_pin;
	_latchPin	=	latch_pin;
   
    pinMode(_clkPin, OUTPUT);
	pinMode(_serPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	
	// Serial.print("ser: ");
	// Serial.print(_serPin);
	// Serial.print("clk: ");
	// Serial.print(_clkPin);
	// Serial.print("latch: ");
	// Serial.print(_latchPin);
}
#endif // VN_PORT_DEFINED

/**
 * @Brief :  Clear display image in the screen
 * @Param :  None
 * @Retval : None.
 */
void Vn74hc595::screenClear(void)
{  
	digitalWrite(_latchPin, LOW);
	shiftOut(_serPin, _clkPin, LSBFIRST, 0x00);	//column
	shiftOut(_serPin, _clkPin, LSBFIRST, 0x00);		//row
	digitalWrite(_latchPin, HIGH);
	delay(1);
}
/**
 * @Brief :  Display image in the screen
 * @Param :  image[] - data image display
 *			 duration - duration show effect
 * @Retval : None.
 */
void Vn74hc595::displayImage(unsigned int image[], int duration)
{
	for (int hold = 0; hold < duration; hold++) {
		for (int a = 0; a < 8; a++) {
			digitalWrite(_latchPin, LOW);
			shiftOut(_serPin, _clkPin, LSBFIRST, image[a]);	//column
			shiftOut(_serPin, _clkPin, LSBFIRST, row[a]);//row[a]);		//row
			digitalWrite(_latchPin, HIGH);
			delay(1);
		}
	}
	// screenClear();
}
/**
 * @Brief :  Scroll image
 * @Param :  image[]   - data image want to scroll
 *			 hold 	   - duration show effect
 *			 dir_shift - direction shift image	
 * @Retval : None.
 */
 void Vn74hc595:: scrollImage(unsigned int image[], uint8_t duration, uint8_t dir_shift)
{
	int shift, hold, a;//biến shift dùng để lưu số bit cần shiftOut
					//biến hold dùng để điều chỉnh độ dài của hiệu ứng
					//biến a dùng để lưu column và row hiện tại
	for(shift = 0; shift < 9; shift++)
	{
	for(hold = 0; hold < duration; hold++)
	{
		for(a = 0; a < 8; a++) {
			digitalWrite(_latchPin, 0);   /* shift data from right to left */
			
			if (dir_shift == RIGHT_SIDE) {
				shiftOut(_serPin,_clkPin, LSBFIRST,(image[a]>>shift));//column
			}
			else {
				shiftOut(_serPin,_clkPin, LSBFIRST,(image[a]<<shift));//column
			}
			
			shiftOut(_serPin,_clkPin, LSBFIRST, row[a]);//row
			digitalWrite(_latchPin, 1);
			delay(1);
		}
	}
  }
}