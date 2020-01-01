#include "VnIrRemote.h"

hw_timer_t *timer;
void IRTimer(); // defined in IRremote.cpp
volatile irparams_t  irparam;

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * Buzzer pins are used and initialized here.
 * @Param : None
 */
VnIrRemote::VnIrRemote(void)
{
  irparam.recvpin = 25;
  Serial.println(irparam.recvpin);
 
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnIrRemote::VnIrRemote(uint8_t port):VnPort(port)
{
  irparam.recvpin = s2;
  Serial.println(irparam.recvpin);
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * you can set any slot for the buzzer device. 
 * @Param :  port - RJ25 port from PORT_1 to M2
 *           slot - SLOT1 or SLOT2
 */
VnIrRemote::VnIrRemote(uint8_t port, uint8_t slot):VnPort(port)
{
  irparam.recvpin = s2;
  if(slot == SLOT2)
  {   
    irparam.recvpin = s2;
  }
  else
  {
    irparam.recvpin = s1;
  }
}
#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * @Param :  switchPin - arduino port for buzzer detect pin.
 */
VnIrRemote::VnIrRemote(int pin)
{
  irparam.recvpin = pin;
}
#endif // VN_PORT_DEFINED

void VnIrRemote::enableIr(void)
{
	timer = timerBegin(1, 80, 1);
	timerAttachInterrupt(timer, &IRTimer, 1);
	// every 50ns, autoreload = true
	timerAlarmWrite(timer, 50, true);
	timerAlarmEnable(timer);
	
	// Initialize state machine variables
	irparam.rcvstate = STATE_IDLE;
	irparam.rawlen = 0;

	// Set pin modes
	pinMode(irparam.recvpin, INPUT);
}

void VnIrRemote::resume(void)
{	
	irparam.rcvstate = STATE_IDLE;
	irparam.rawlen = 0;
}

int VnIrRemote::compare (unsigned int oldval,  unsigned int newval)
{
	if      (newval < oldval * .8)  return 0 ;
	else if (oldval < newval * .8)  return 2 ;
	else                            return 1 ;
}

long VnIrRemote::decodeHash (decode_results *results)
{
	long  hash = FNV_BASIS_32;

	// Require at least 6 samples to prevent triggering on noise
	if (results->rawlen < 6)  return false ;

	for (int i = 1;  (i + 2) < results->rawlen;  i++) {
		int value =  compare(results->rawbuf[i], results->rawbuf[i+2]);
		// Add value into the hash
		hash = (hash * FNV_PRIME_32) ^ value;
	}

	results->value       = hash;
	results->bits        = 32;
	// results->decode_type = UNKNOWN;

	return true;
}

int VnIrRemote::MATCH(int measured, int desired)
{
#ifdef DEBUG
	Serial.print("Testing: ");
 	Serial.print(TICKS_LOW(desired), DEC);
 	Serial.print(" <= ");
 	Serial.print(measured, DEC);
 	Serial.print(" <= ");
 	Serial.print(TICKS_HIGH(desired), DEC);
#endif

	bool passed = ((measured >= TICKS_LOW(desired)) && (measured <= TICKS_HIGH(desired)));
	if (passed) {
	#ifdef DEBUG
			Serial.println("?; passed");
	#endif
	}
	else {
	#ifdef DEBUG
			Serial.println("?; FAILED"); 
	#endif
	}
 	return passed;
}

//+========================================================
// Due to sensor lag, when received, Marks tend to be 100us too long
//
int VnIrRemote::MATCH_MARK (int measured_ticks,  int desired_us)
{
#ifdef DEBUG
	Serial.println("Testing mark (actual vs desired): ");
	Serial.println(measured_ticks * USECPERTICK, DEC);
	Serial.println("us vs ");
	Serial.println(desired_us, DEC);
	Serial.println("us"); 
	Serial.println(": ");
	Serial.println(TICKS_LOW(desired_us + MARK_EXCESS) * USECPERTICK, DEC);
	Serial.println(" <= ");
	Serial.println(measured_ticks * USECPERTICK, DEC);
	Serial.println(" <= ");
	Serial.println(TICKS_HIGH(desired_us + MARK_EXCESS) * USECPERTICK, DEC);
#endif

bool passed = ((measured_ticks >= TICKS_LOW (desired_us + MARK_EXCESS))
                && (measured_ticks <= TICKS_HIGH(desired_us + MARK_EXCESS)));
	if (passed) {
	#ifdef DEBUG
		Serial.println("?; passed");
	#endif
	}
	else {
	#ifdef DEBUG
		Serial.println("?; FAILED"); 
	#endif
  }
 	return passed;
}

//+========================================================
// Due to sensor lag, when received, Spaces tend to be 100us too short
//
int VnIrRemote::MATCH_SPACE (int measured_ticks,  int desired_us)
{
#ifdef DEBUG
	Serial.println("Testing space (actual vs desired): ");
	Serial.println(measured_ticks * USECPERTICK, DEC);
	Serial.println("us vs ");
	Serial.println(desired_us, DEC);
	Serial.println("us"); 
	Serial.println(": ");
	Serial.println(TICKS_LOW(desired_us - MARK_EXCESS) * USECPERTICK, DEC);
	Serial.println(" <= ");
	Serial.println(measured_ticks * USECPERTICK, DEC);
	Serial.println(" <= ");
	Serial.println(TICKS_HIGH(desired_us - MARK_EXCESS) * USECPERTICK, DEC);
#endif

  bool passed = ((measured_ticks >= TICKS_LOW (desired_us - MARK_EXCESS))
                && (measured_ticks <= TICKS_HIGH(desired_us - MARK_EXCESS)));
  if (passed) {
	#ifdef DEBUG
		Serial.println("?; passed");
	#endif
  }
  else {
	#ifdef DEBUG
		Serial.println("?; FAILED"); 
	#endif
  }
 	return passed;
}

bool VnIrRemote::decodeNEC (decode_results *results)
{
	long  data   = 0;  // We decode in to here; Start with nothing
	int   offset = 1;  // Index in to results; Skip first entry!?

	// Check header "mark"
	if (!MATCH_MARK(results->rawbuf[offset], NEC_HDR_MARK))  return false ;
	offset++;

	// Check for repeat
	if ( (irparam.rawlen == 4)
	    && MATCH_SPACE(results->rawbuf[offset  ], NEC_RPT_SPACE)
	    && MATCH_MARK (results->rawbuf[offset+1], NEC_BIT_MARK )
	   ) {
		results->bits        = 0;
		results->value       = REPEAT;
		// results->decode_type = NEC;
		return true;
	}

	// Check we have enough data
	if (irparam.rawlen < (2 * NEC_BITS) + 4)  return false ;

	// Check header "space"
	if (!MATCH_SPACE(results->rawbuf[offset], NEC_HDR_SPACE))  return false ;
	offset++;

	// Build the data
	for (int i = 0;  i < NEC_BITS;  i++) {
		// Check data "mark"
		if (!MATCH_MARK(results->rawbuf[offset], NEC_BIT_MARK))  return false ;
		offset++;
        // Suppend this bit
		if      (MATCH_SPACE(results->rawbuf[offset], NEC_ONE_SPACE ))  data = (data << 1) | 1 ;
		else if (MATCH_SPACE(results->rawbuf[offset], NEC_ZERO_SPACE))  data = (data << 1) | 0 ;
		else                                                            return false ;
		offset++;
	}

	// Success
	results->bits        = NEC_BITS;
	results->value       = data;

	return true;
}
int VnIrRemote::decode(decode_results *results)
{	
	results->rawbuf   = irparam.rawbuf;
	results->rawlen   = irparam.rawlen;

	results->overflow = irparam.overflow;

	if (irparam.rcvstate != STATE_STOP)  return false ;

#ifdef DEBUG
	Serial.println("Attempting NEC decode");
#endif
	if (decodeNEC(results))  return true ;
	
	if (decodeHash(results))  return true ;

	// Throw away and start over
	resume();
	return false;
}
void IRTimer()
{
	TIMER_RESET;

	// Read if IR Receiver -> SPACE [xmt LED off] or a MARK [xmt LED on]
	// digitalRead() is very slow. Optimisation is possible, but makes the code unportable
	uint8_t  irdata ;
	
	irdata = (uint8_t)digitalRead(irparam.recvpin);

	irparam.timer++;  // One more 50uS tick
	if (irparam.rawlen >= RAWBUF)  irparam.rcvstate = STATE_OVERFLOW ;  // Buffer overflow

	switch(irparam.rcvstate) {
		//......................................................................
		case STATE_IDLE: // In the middle of a gap
			if (irdata == MARK) {
				if (irparam.timer < GAP_TICKS)  {  // Not big enough to be a gap.
					irparam.timer = 0;

				} else {
					// Gap just ended; Record duration; Start recording transmission
					irparam.overflow                  = false;
					irparam.rawlen                    = 0;
					irparam.rawbuf[irparam.rawlen++] = irparam.timer;
					irparam.timer                     = 0;
					irparam.rcvstate                  = STATE_MARK;
				}
			}
			break;
		//......................................................................
		case STATE_MARK:  // Timing Mark
			if (irdata == SPACE) {   // Mark ended; Record time
				irparam.rawbuf[irparam.rawlen++] = irparam.timer;
				irparam.timer                     = 0;
				irparam.rcvstate                  = STATE_SPACE;
			}
			break;
		//......................................................................
		case STATE_SPACE:  // Timing Space
			if (irdata == MARK) {  // Space just ended; Record time
				irparam.rawbuf[irparam.rawlen++] = irparam.timer;
				irparam.timer                     = 0;
				irparam.rcvstate                  = STATE_MARK;

			} else if (irparam.timer > GAP_TICKS) {  // Space
					// A long Space, indicates gap between codes
					// Flag the current code as ready for processing
					// Switch to STOP
					// Don't reset timer; keep counting Space width
					irparam.rcvstate = STATE_STOP;
			}
			break;
		//......................................................................
		case STATE_STOP:  // Waiting; Measuring Gap
		 	if (irdata == MARK)  irparam.timer = 0 ;  // Reset gap timer
		 	break;
		//......................................................................
		case STATE_OVERFLOW:  // Flag up a read overflow; Stop the State Machine
			irparam.overflow = true;
			irparam.rcvstate = STATE_STOP;
		 	break;
	}

	// // If requested, flash LED while receiving IR data
	// if (irparam.blinkflag) {
		// if (irdata == MARK)
			// if (irparam.blinkpin) digitalWrite(irparam.blinkpin, HIGH); // Turn user defined pin LED on
				// else BLINKLED_ON() ;   // if no user defined LED pin, turn default LED pin for the hardware on
		// else if (irparam.blinkpin) digitalWrite(irparam.blinkpin, LOW); // Turn user defined pin LED on
				// else BLINKLED_OFF() ;   // if no user defined LED pin, turn default LED pin for the hardware on
	// }
}
