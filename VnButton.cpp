/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnButton
 * \brief   Driver for Vn Buzzer module.
 * @file    VnButton.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
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
 *    1. void VnButton::setpin(int pin);
 *	  2. void VnButton::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void VnButton::tone(uint16_t frequency, uint32_t duration)
 *	  4. void VnButton::noTone(int pin);
 *	  5. void VnButton::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#include "VnButton.h"

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * Buzzer pins are used and initialized here.
 * @Param : None
 */
VnButton::VnButton(void) : VnPort()
{

}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnButton::VnButton(uint8_t port) : VnPort(port)
{
  mode_pin = s2;
  Serial.println(mode_pin);
}

#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * @Param :  switchPin - arduino port for buzzer detect pin.
 */
VnButton::VnButton(int pin)
{
  mode_pin = pin;
}
#endif // VN_PORT_DEFINED

/**
 * @Brief :  Reset the buzzer available pin by its arduino port.
 * @Param :  pin - arduino port for buzzer detect pin.
 * @Retval : None
 * @Others : None
 */
void VnButton::setpin(int pin)
{
	mode_pin = pin;
#ifdef VN_PORT_DEFINED
	s2 = pin;
#endif
}

/**
 * @Brief :  Playing the tones.
 * @Param :  pin - Which pin on board that buzzer is connecting to.
 *           frequency - The speed of buzzer's tone play.
 *           duration - Time of a tone play.
 * @Retval : None.
 * @Others : Frequency (in hertz) and duration (in milliseconds).
 */
void VnButton::read_mode(void)
{
	uint8_t val;
	
#ifdef 	VN_PORT_DEFINED
	val = VnPort::dRead2(INPUT_PULLUP);
#else
	pinMode(mode_pin, INPUT_PULLUP);
    val = digitalRead(mode_pin);
#endif

	delay(150);
	
	if (!val) 
		mode_state ++;
	
	if (mode_state > 4)
		mode_state = 0;
	
	switch (mode_state) {
		case MODE1:
			Serial.println("Mode1");
			break;
		case MODE2:
			Serial.println("Mode2");
			break;
		case MODE3:
			Serial.println("Mode3");
			break;
		case MODE4:
			Serial.println("Mode4");
			break;
		default:
			Serial.println("Ideal");
			break;	
	}
}
