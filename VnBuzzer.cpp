/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnBuzzer
 * \brief   Driver for Vn Buzzer module.
 * @file    VnBuzzer.cpp
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
 *    1. void VnBuzzer::setpin(int pin);
 *	  2. void VnBuzzer::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void VnBuzzer::tone(uint16_t frequency, uint32_t duration)
 *	  4. void VnBuzzer::noTone(int pin);
 *	  5. void VnBuzzer::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#include "VnBuzzer.h"
//#include <avr/wdt.h>

uint8_t buzzer_pin;

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * Buzzer pins are used and initialized here.
 * @Param : None
 */
VnBuzzer::VnBuzzer(void)
{
  buzzer_pin = 32;
  Serial.println(buzzer_pin);
 
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnBuzzer::VnBuzzer(uint8_t port):VnPort(port)
{
  buzzer_pin = s2;
  Serial.println(buzzer_pin);
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * you can set any slot for the buzzer device. 
 * @Param :  port - RJ25 port from PORT_1 to M2
 *           slot - SLOT1 or SLOT2
 */
VnBuzzer::VnBuzzer(uint8_t port, uint8_t slot):VnPort(port)
{
  buzzer_pin = s2;
  if(slot == SLOT2)
  {   
    buzzer_pin = s2;
  }
  else
  {
    buzzer_pin = s1;
  }
}
#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * @Param :  switchPin - arduino port for buzzer detect pin.
 */
VnBuzzer::VnBuzzer(int pin)
{
  buzzer_pin = pin;
}
#endif // VN_PORT_DEFINED

/**
 * @Brief :  Reset the buzzer available pin by its arduino port.
 * @Param :  pin - arduino port for buzzer detect pin.
 * @Retval : None
 * @Others : None
 */
void VnBuzzer::setpin(int pin)
{
  buzzer_pin = pin;
}

/**
 * @Brief :  Playing the tones.
 * @Param :  pin - Which pin on board that buzzer is connecting to.
 *           frequency - The speed of buzzer's tone play.
 *           duration - Time of a tone play.
 * @Retval : None.
 * @Others : Frequency (in hertz) and duration (in milliseconds).
 */
void VnBuzzer::tone(int pin, uint16_t frequency, uint32_t duration)
{
  buzzer_pin = pin;
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (long i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
    //wdt_reset();
  }
}

/**
 * @Brief :  Playing the tones.
 * @Param :  frequency - The speed of buzzer's tone play.
 *           duration - Time of a tone play.
 * @Retval : None.
 * @Others : Frequency (in hertz) and duration (in milliseconds).
 */
void VnBuzzer::tone(uint16_t frequency, uint32_t duration)
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (long i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
    //wdt_reset();
  }
}

void VnBuzzer::test()
{
	ledcSetup(1, 4000, 8);
	ledcAttachPin(32, 1);
	ledcWrite(1, 100);
}

/**
 * @Brief :  Do not playing the tones.
 * @Param :  pin - Which pin on board that buzzer is connecting to.
 * @Retval : None.
 * @Others : None
 */
void VnBuzzer::noTone(int pin)
{
  buzzer_pin = pin;
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}

/**
 * @Brief :  Do not playing the tones.
 * @Param :  None
 * @Retval : None.
 * @Others : None
 */
void VnBuzzer::noTone()
{
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}