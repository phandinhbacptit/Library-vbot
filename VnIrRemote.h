/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnIrRemote
 * \brief   Driver for Vn Buzzer module.
 * @file    VnIrRemote.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VnIrRemote.cpp module
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
#ifndef _VNIRREMOTE_H_
#define _VNIRREMOTE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
 #include "VnPort.h"
#endif /* VN_PORT_DEFINED */

#define TIMER_RESET

/******** Define  const parameter */
#define RAWBUF  		101 
#define MARK_EXCESS     100
#define REPEAT 0xFFFFFFFF

#define USECPERTICK    50

#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261

#define MARK   0
#define SPACE  1

// Upper and Lower percentage tolerances in measurements
#define TOLERANCE       25
#define LTOL            (1.0 - (TOLERANCE/100.))
#define UTOL            (1.0 + (TOLERANCE/100.))

// Minimum gap between IR transmissions
#define _GAP            5000
#define GAP_TICKS       (_GAP/USECPERTICK)

#define TICKS_LOW(us)   ((int)(((us)*LTOL/USECPERTICK)))
#define TICKS_HIGH(us)  ((int)(((us)*UTOL/USECPERTICK + 1)))

/*State-Machine : Receiver States*/
#define STATE_IDLE      2
#define STATE_MARK      3
#define STATE_SPACE     4
#define STATE_STOP      5
#define STATE_OVERFLOW  6

#define NEC_BITS          32
#define NEC_HDR_MARK    9000
#define NEC_HDR_SPACE   4500
#define NEC_BIT_MARK     560
#define NEC_ONE_SPACE   1690
#define NEC_ZERO_SPACE   560
#define NEC_RPT_SPACE   2250


typedef struct {
	uint8_t rcvstate; 				// Contain state of state machine
	uint8_t recvpin;				// Pin connect to output of IR remote sensor
	uint8_t blinkflag;				// true -> enable blinking of pin on IR processing
	uint8_t rawlen;					// Counter of entries in rawbuf
	unsigned int timer;				// State timer, counts 50us per ticks.
	unsigned int rawbuf[RAWBUF]; 	// Buffer contain data
	uint8_t overflow;				// Raw buffer overflow occurred
	
} irparams_t;


  
class decode_results
{
	public:
		unsigned int           address;      // Used by Panasonic & Sharp [16-bits]
		unsigned long          value;        // Decoded value [max 32-bits]
		int                    bits;         // Number of bits in decoded value
		volatile unsigned int  *rawbuf;      // Raw intervals in 50uS ticks
		int                    rawlen;       // Number of records in rawbuf
		int                    overflow;     // true iff IR raw code too long
};

#ifdef VN_PORT_DEFINED
 class VnIrRemote : public VnPort
#else
 class VnIrRemote
#endif
{
public:

#ifdef VN_PORT_DEFINED
	VnIrRemote(void);
	VnIrRemote(uint8_t port);
	VnIrRemote(uint8_t port, uint8_t slot);
#else /* VN_PORT_DEFINED */
  VnIrRemote(int pin);
#endif /* VN_PORT_DEFINED */
	void enableIr(void);
	void resume(void);
	int decode(decode_results *results);
  // void setpin(int pin);
  // void tone(int pin, uint16_t frequency, uint32_t duration);
  // void tone(uint16_t frequency, uint32_t duration = 0);
  // void noTone(int pin);
  // void noTone();
  // void test();
   
  private:

  long decodeHash (decode_results *results);
  int MATCH(int measured, int desired);
  int MATCH_MARK (int measured_ticks,  int desired_us);
  int MATCH_SPACE (int measured_ticks,  int desired_us);
  bool decodeNEC (decode_results *results);
  int compare (unsigned int oldval,  unsigned int newval);
};

#endif /* _VNIRREMOTE_H_ */