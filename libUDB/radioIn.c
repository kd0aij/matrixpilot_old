// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


#include "libUDB_internal.h"
#include "oscillator.h"
#include "interrupt.h"

#if (FLY_BY_DATALINK_ENABLED == 1)
#include "fly_by_datalink.h"
#include "mode_switch.h"
#endif

// with T2 prescaler set to 8 and FCY=16MHz, maximum interval is 65535 / 2e6 = 32.767 msec
// which gives a PWM range of 2000 to 4000 counts for just under 11 bits of resolution
// with T2 prescaler set to 8 and FCY=40MHz, maximum interval is 65535 / 5e6 = 13.107 msec
// which gives a PWM range of 5000 to 10000 counts for over 12 bits of resolution
// increasing FCY to 70MHz decreases the max interval to 7.49 msec, which might be too short
// for a PPM sync pulse. So use prescaling of 64 above 40MHz
// At 64MHz this gives a resolution of 1usec, and a PWM range of 1000 to 2000 counts
// which is just under 10 bits of resolution

// make pwIn values independent of clock and timer rates
// this scaling is relative to the legacy FCY of 16e6 (minimum)
// Resolution of udb_pwIn is always 0.5 usec/count with this scaling.

// This declaration puts PWINSCALE in program memory, and this causes no problem
// here, but causes resets if done in servoOut.c
//const uint16_t PWINSCALE = (uint16_t)(65535 * (16.0E6 / FCY));

// valid range of FCY is [70e6, 16e6]
// therefore range of PWINSCALE is [14,979, 65,535] => [.229, 1)
// If FCY >= 64e6, PWINSCALE is multiplied by 8 via LEFTSHIFT = 3
#define PWINSCALE (uint16_t)(65535 * (16.0E6 / FCY))

#if (MIPS >= 64)
// prescaler 64
#define TCKPS_VAL 2
// scale factor > 1
#define LEFTSHIFT 3
// With T2 prescaler set to 64, the timer resolution is 64/FCY sec/count
// so 1 msec = (FCY/64) * 1e-3
#define MIN_SYNC_PULSE_WIDTH (3.5e-3 * FCY / 64.0) // 3.5ms
#else
// prescaler 8
#define TCKPS_VAL 1
// scale factor < 1
#define LEFTSHIFT 0
// With T2 prescaler set to 8, the timer resolution is 8/FCY sec/count
// so 1 msec = (FCY/8) * 1e-3
#define MIN_SYNC_PULSE_WIDTH (3.5e-3 * FCY / 8.0) // 3.5ms
#endif

//#define DEBUG_FAILSAFE_MIN_MAX


//	Measure the pulse widths of the servo channel inputs from the radio.
//	The dsPIC makes this rather easy to do using its capture feature.

//	One of the channels is also used to validate pulse widths to detect loss of radio.

//	The pulse width inputs can be directly converted to units of pulse width outputs to control
//	the servos by simply dividing by 2. (need to check validity of this statement - RobD)

int16_t udb_pwIn[NUM_INPUTS+1];     // pulse widths of radio inputs
int16_t udb_pwTrim[NUM_INPUTS+1];   // initial pulse widths for trimming

int16_t failSafePulses = 0;
int16_t noisePulses = 0;

void udb_init_capture(void)
{
	int16_t i;

#if (USE_NV_MEMORY == 1)
	if (udb_skip_flags.skip_radio_trim == 0)
#endif
	{	
		for (i = 0; i <= NUM_INPUTS; i++)
	#if (FIXED_TRIMPOINT == 1)
			if(i == THROTTLE_OUTPUT_CHANNEL)
				udb_pwTrim[i] = udb_pwIn[i] = THROTTLE_TRIMPOINT;
			else
				udb_pwTrim[i] = udb_pwIn[i] = CHANNEL_TRIMPOINT;
	#else
			udb_pwTrim[i] = udb_pwIn[i] = 0;
	#endif
	}
	
	TMR2 = 0;               // initialize timer
	T2CONbits.TCKPS = TCKPS_VAL;    // prescaler (8 or 64)
	T2CONbits.TCS = 0;      // use the internal clock
	T2CONbits.TON = 1;      // turn on timer 2

#if (NORADIO != 1)

#if (BOARD_TYPE == AUAV3_BOARD)
#define REGTOK1 N1
#define REGTOK2 N2
#define IC1VAL 0x0401
#else
#define REGTOK1 N
#define REGTOK2 N
#define IC1VAL 0x0081
#endif
#define IC2VAL 0 // SYNCSEL = 0x00: no sync, no trigger, rollover at 0xFFFF

#define _IC_INIT(x, y, z) \
{ \
	IC##x##CO##z = IC2VAL; \
	IC##x##CO##y = IC1VAL; \
	_IC##x##IP = INT_PRI_IC; \
	_IC##x##IF = 0; \
	_IC##x##IE = 1; \
}
#define IC_INIT(x, y, z) _IC_INIT(x, y, z)

	if (NUM_INPUTS > 0) IC_INIT(1, REGTOK1, REGTOK2);
#if (USE_PPM_INPUT == 0)
	if (NUM_INPUTS > 1) IC_INIT(2, REGTOK1, REGTOK2);
	if (NUM_INPUTS > 2) IC_INIT(3, REGTOK1, REGTOK2);
	if (NUM_INPUTS > 3) IC_INIT(4, REGTOK1, REGTOK2);
	if (NUM_INPUTS > 4) IC_INIT(5, REGTOK1, REGTOK2);
	if (NUM_INPUTS > 5) IC_INIT(6, REGTOK1, REGTOK2);
	if (NUM_INPUTS > 6) IC_INIT(7, REGTOK1, REGTOK2);
	if (NUM_INPUTS > 7) IC_INIT(8, REGTOK1, REGTOK2);
#endif // USE_PPM_INPUT
#endif // NORADIO
}

void set_udb_pwIn(uint16_t pwm, int index)
{
#if (NORADIO != 1)
	union longww pww;
	pww.WW = __builtin_muluu(pwm, PWINSCALE);
#if (LEFTSHIFT > 0)
	pww.WW <<= LEFTSHIFT;
#endif
	pwm = pww._.W1;

	if (FAILSAFE_INPUT_CHANNEL == index)
	{
		if ((pwm > FAILSAFE_INPUT_MIN) && (pwm < FAILSAFE_INPUT_MAX))
		{
			failSafePulses++;
		}
		else
		{
			noisePulses++;
		}
	}

#if (FLY_BY_DATALINK_ENABLED == 1)
	// It's kind of a bad idea to override the radio mode input
	if (MODE_SWITCH_INPUT_CHANNEL == index)
	{
		udb_pwIn[index] = pwm;
	}
	else
	{
		if (udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] < MODE_SWITCH_THRESHOLD_LOW)
		{
			// if mode is in low mode, use pwm values that came in from external source
			udb_pwIn[index] = get_fbdl_pwm(index);
		}
		else
		{
			udb_pwIn[index] = pwm;
		}
	}
#else
	if (FAILSAFE_INPUT_CHANNEL == index)
	{
		//printf("FS: %u %u %u\r\n", pwm, failSafePulses, noisePulses);
		#ifdef DEBUG_FAILSAFE_MIN_MAX
		{
			static uint8_t foo = 0;
			if (!(++foo % 32)) 
			{
				printf("FS: %u\r\n", pwm);
			}
		}
		#endif // DEBUG_FAILSAFE_MIN_MAX
	}
	udb_pwIn[index] = pwm;
#endif // FLY_BY_DATALINK_ENABLED
#endif // NOARADIO !=1
}

#if (NORADIO != 1)
#if (USE_PPM_INPUT == 0)

#define _IC_HANDLER(x, y, z) \
void __attribute__((__interrupt__,__no_auto_psv__)) _IC##x##Interrupt(void) \
{ \
	indicate_loading_inter; \
	interrupt_save_set_corcon; \
	static uint16_t rise = 0; \
	uint16_t time = 0; \
	_IC##x##IF = 0; \
	while (IC##x##CO##y##bits.ICBNE) \
		time = IC##x##BUF; \
	if (z) \
		rise = time; \
	else \
		set_udb_pwIn(time - rise, x); \
	interrupt_restore_corcon; \
}
#define IC_HANDLER(x, y, z) _IC_HANDLER(x, y, z)

IC_HANDLER(1, REGTOK1, IC_PIN1);
IC_HANDLER(2, REGTOK1, IC_PIN2);
IC_HANDLER(3, REGTOK1, IC_PIN3);
IC_HANDLER(4, REGTOK1, IC_PIN4);
IC_HANDLER(5, REGTOK1, IC_PIN5);
IC_HANDLER(6, REGTOK1, IC_PIN6);
IC_HANDLER(7, REGTOK1, IC_PIN7);
IC_HANDLER(8, REGTOK1, IC_PIN8);

#else // (USE_PPM_INPUT != 0)

#if (PPM_SIGNAL_INVERTED == 1)
#define PPM_PULSE_VALUE 0
#else
#define PPM_PULSE_VALUE 1
#endif

// PPM Input on Channel 1

void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	indicate_loading_inter;
	interrupt_save_set_corcon;

	static uint16_t rise_ppm = 0;
	static uint8_t ppm_ch = 0;
	uint16_t time = 0;

	_IC1IF = 0;
#if (BOARD_TYPE == AUAV3_BOARD)
	while (IC1CON1bits.ICBNE)
#else
	while (IC1CONbits.ICBNE)
#endif
	{
		time = IC1BUF;
	}
#if (USE_PPM_INPUT == 1)
	if (IC_PIN1 == PPM_PULSE_VALUE)
	{
		uint16_t pulse = time - rise_ppm;
		rise_ppm = time;

		if (pulse > MIN_SYNC_PULSE_WIDTH)
		{
			ppm_ch = 1;
		}
		else
		{
			if (ppm_ch > 0 && ppm_ch <= PPM_NUMBER_OF_CHANNELS)
			{
				if (ppm_ch <= NUM_INPUTS)
				{
					set_udb_pwIn(pulse, ppm_ch);
				}
				ppm_ch++;
			}
		}
	}
#elif  (USE_PPM_INPUT == 2)
	uint16_t pulse = time - rise_ppm;
	rise_ppm = time;

	if (IC_PIN1 == PPM_PULSE_VALUE)
	{
		if (pulse > MIN_SYNC_PULSE_WIDTH)
		{
			ppm_ch = 1;
		}
	}
	else
	{
		if (ppm_ch > 0 && ppm_ch <= PPM_NUMBER_OF_CHANNELS)
		{
			if (ppm_ch <= NUM_INPUTS)
			{
				set_udb_pwIn(pulse, ppm_ch);
			}
			ppm_ch++;
		}
	}
#else  // USE_PPM_INPUT > 2
#error Invalid USE_PPM_INPUT setting
#endif // USE_PPM_INPUT
	interrupt_restore_corcon;
}

#endif // USE_PPM_INPUT
#endif // NOARADIO !=1
