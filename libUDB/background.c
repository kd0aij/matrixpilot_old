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
#include "heartbeat.h"

#if (USE_I2C1_DRIVER == 1)
#include "I2C.h"
#endif

// Include the NV memory services if required
#if (USE_NV_MEMORY == 1)
#include "NV_memory.h"
#include "data_storage.h"
#include "data_services.h"
#endif

#ifdef USE_MAVLINK_DBGIO
#include "mavlink_types.h"
int16_t mavlink_serial_send(mavlink_channel_t chan, uint8_t buf[], uint16_t len);
extern uint8_t dbg_buff[50];
#endif

#if (USE_MCU_IDLE == 0)
//      65536 to move result into upper 16 bits of 32 bit word
//      100 to make a percentage
//      FCY frequency of instruction clock
//      (16 * 256) Number of cycles for (see PR5 below) each timer interrupt
#define CPU_LOAD_PERCENT (6553600/((FCY)/4096))

uint16_t cpu_timer = 0;
uint16_t _cpu_timer = 0;
#else
uint32_t busy_timer = 0;
#endif

uint16_t udb_heartbeat_counter = 0;
#define HEARTBEAT_MAX 57600 // Evenly divisible by many common values: 2^8 * 3^2 * 5^2
#define MAX_NOISE_RATE 5    // up to 5 PWM "glitches" per second are allowed

void udb_run_init_step(void);


void udb_init_clock(void)   // initialize timers
{
#if (BOARD_TYPE == UDB4_BOARD)
	// Legacy code for analog IMU sensors

	// Initialize Timer1, used as the HEARTBEAT_HZ heartbeat of libUDB.
	// FCY is 70MHz max: prescaler = 64, timer clock max 70/64 MHz
	// For 40Hz heartbeat, PR1 max = 70e6/64/40 = 27,344 < 65,535
	// At lowest FCY of 16 MHz, PR1 = 6,250
	TMR1 = 0;
	T1CONbits.TCKPS = 2; // prescaler = 64
	PR1 = (FCY / 64) / HEARTBEAT_HZ; // period 1/HEARTBEAT_HZ
	T1CONbits.TCS = 0;      // use the crystal to drive the clock
	_T1IP = INT_PRI_T1;     // set interrupt priority
	_T1IF = 0;              // clear the interrupt
	_T1IE = 1;              // enable the interrupt
	T1CONbits.TON = 1;      // turn on timer 1
#else
	// MPU6000 interrupt is used as the HEARTBEAT_HZ heartbeat of libUDB.
	// Timer1 is not used for heartbeat, but its interrupt flag is set in the
	// MPU6000 ISR.

	T1CONbits.TON = 0;      // turn off timer 1
	TMR1 = 0;
	_T1IP = INT_PRI_T1;     // set interrupt priority
	_T1IF = 0;              // clear the interrupt
	_T1IE = 1;              // enable the interrupt
#endif


	// Two load measuring techniques are supported, depending on whether USE_MCU_IDLE is selected
#if (USE_MCU_IDLE == 0)
	// Timer 5 is used to measure CPU usage
	//   Timer 5 will be turned on in interrupt routines and turned off in main()
	TMR5 = 0;               // initialize timer
	PR5 = 16*256;           // measure instructions in groups of 16*256 
	_cpu_timer = 0;         // initialize the load counter
	T5CONbits.TCKPS = 0;    // no prescaler
	T5CONbits.TCS = 0;      // use the crystal to drive the clock
	_T5IP = INT_PRI_T5;     // set interrupt priority
	_T5IF = 0;              // clear the interrupt
	_T5IE = 1;              // enable the interrupt
	T5CONbits.TON = 0;      // turn off timer 5 until we enter an interrupt
#else
	// 32 bit Timer 8/9 free runs until stopped during CPU idle
	T9CONbits.TON = 0; // Disable Timer
	T8CONbits.TON = 0; // Disable Timer
	TMR9 = 0x00;       // Clear timer register
	TMR8 = 0x00;       // Clear timer register
	PR9 = 0xFFFF;      // period 2^32 cycles
	PR8 = 0xFFFF;

	T8CONbits.TCKPS = 0; // prescaler = 1
	T8CONbits.TGATE = 0; // not gated
	T8CONbits.TSIDL = 1; // stop the timer during CPU IDLE
	T8CONbits.TCS = 0;   // Select internal instruction cycle clock
	T8CONbits.T32 = 1;   // T8/T9 form a 32 bit timer
	_T8IP = 0;
	_T8IF = 0;
	_T8IE = 0;
	_T9IP = 0;
	_T9IF = 0;
	_T9IE = 0;
	T8CONbits.TON = 1;   // start the cpu timer
#endif

	// The Timer7 interrupt is used to trigger background tasks such as
	// navigation processing after binary data is received from the GPS.
	_T7IP = INT_PRI_T7;     // set interrupt priority
	_T7IF = 0;              // clear the interrupt
	_T7IE = 1;              // enable the interrupt

	// Enable the interrupt, but not the timer. This is used as a trigger from
	// the high priority heartbeat ISR to start all the HEARTBEAT_HZ processing
	// at a lower priority.
	_T6IP = INT_PRI_T6;     // set interrupt priority
	_T6IF = 0;              // clear the PWM interrupt
	_T6IE = 1;              // enable the PWM interrupt

}

// This interrupt is the Heartbeat of libUDB.
void __attribute__((__interrupt__,__no_auto_psv__)) _T1Interrupt(void)
{
	indicate_loading_inter;
	interrupt_save_set_corcon;

	_T1IF = 0;              // clear the interrupt

	// Start the sequential servo pulses at frequency SERVO_HZ
	if (udb_heartbeat_counter % (HEARTBEAT_HZ/SERVO_HZ) == 0)
	{
		start_pwm_outputs();
	}

	// Capture cpu_timer once per second.
	if (udb_heartbeat_counter % HEARTBEAT_HZ == 0)
	{
#if (USE_MCU_IDLE == 0)
		T5CONbits.TON = 0;      // turn off timer 5
		cpu_timer = _cpu_timer; // snapshot the load counter
		_cpu_timer = 0;         // reset the load counter
		T5CONbits.TON = 1;      // turn on timer 5
#else
		// 32 bit counter TMR8/9 is running whenever the cpu is not idle
		// but the following performs a coherent read of the 32 bit value
		busy_timer = TMR8; // snapshot the idle counter low word
		busy_timer += (((uint32_t) TMR9HLD) << 16);	// corresponding high word
		TMR9HLD = 0;
		TMR8 = 0;
#endif
	}

	// Call the periodic callback at HEARTBEAT_HZ
	udb_background_callback_periodic();

	// Trigger the HEARTBEAT_HZ calculations, but at a lower priority
	_T6IF = 1;

	udb_heartbeat_counter = (udb_heartbeat_counter+1) % HEARTBEAT_MAX;

	interrupt_restore_corcon;
}

// Trigger the low priority background processing interrupt.
void udb_background_trigger(void)
{
	_T7IF = 1;              // trigger the interrupt
}

// Process the TRIGGER interrupt.
// This is used by libDCM to kick off gps-based calculations at a lower
// priority after receiving each new set of GPS data.
void __attribute__((__interrupt__,__no_auto_psv__)) _T7Interrupt(void)
{
	indicate_loading_inter;
	interrupt_save_set_corcon;

	_T7IF = 0;              // clear the interrupt

	udb_background_callback_triggered();

	interrupt_restore_corcon;
}


#if (USE_MCU_IDLE == 0)
uint8_t udb_cpu_load(void)
{
	// scale cpu_timer to seconds*100 for percent loading
	return (uint8_t)(__builtin_muluu(cpu_timer, CPU_LOAD_PERCENT) >> 16);
}

void __attribute__((__interrupt__,__no_auto_psv__)) _T5Interrupt(void)
{
	interrupt_save_set_corcon;

	TMR5 = 0;               // reset the timer
	_cpu_timer ++;          // increment the load counter
	_T5IF = 0;              // clear the interrupt

	interrupt_restore_corcon;
}
#else
// return cpu load in percent * 100
uint16_t udb_cpu_ratio(void)
{
	// ratio ranges from 0 to 10,000 (100 * percent)
	float busyRatio = (10000.0  * busy_timer / FCY);
	return (busyRatio + 0.5);
}

// scale cpu_timer for percent loading
uint8_t udb_cpu_load(void)
{
	return (uint8_t)(udb_cpu_ratio() / 100);
}
#endif

//	Executes whatever lower priority calculation needs to be done every heartbeat (default: 25 milliseconds)
//	This is a good place to eventually compute pulse widths for servos.
void __attribute__((__interrupt__,__no_auto_psv__)) _T6Interrupt(void)
{
	indicate_loading_inter;
	interrupt_save_set_corcon;

	_T6IF = 0; // clear the interrupt

#if (NORADIO != 1)
	// 20Hz testing of radio link
	if ((udb_heartbeat_counter % (HEARTBEAT_HZ/20)) == 1)
	{
		// check to see if at least one valid pulse has been received,
		// and also that the noise rate has not been exceeded
		if ((failSafePulses == 0) || (noisePulses > MAX_NOISE_RATE))
		{
			if (udb_flags._.radio_on == 1) {
				udb_flags._.radio_on = 0;
				udb_callback_radio_did_turn_off();
			}
			LED_GREEN = LED_OFF;
			noisePulses = 0; // reset count of noise pulses
		}
		else
		{
			udb_flags._.radio_on = 1;
			LED_GREEN = LED_ON;
		}
		failSafePulses = 0;
	}
	// Computation of noise rate
	// Noise pulses are counted when they are detected, and reset once a second
	if ((udb_heartbeat_counter % HEARTBEAT_HZ) == 1)
	{
		noisePulses = 0;
	}
#endif // NORADIO

#ifdef VREF
	vref_adj = (udb_vref.offset>>1) - (udb_vref.value>>1);
#else
	vref_adj = 0;
#endif // VREF

	calculate_analog_sensor_values();
	udb_callback_read_sensors();
	udb_flags._.a2d_read = 1; // signal the A/D to start the next summation

	udb_servo_callback_prepare_outputs();

#if (USE_I2C1_DRIVER == 1)
		I2C1_trigger_service();
#endif

#if (USE_NV_MEMORY == 1)
		nv_memory_service_trigger();
		storage_service_trigger();
		data_services_trigger();
#endif	

#if (USE_FLEXIFUNCTION_MIXING == 1)
		flexiFunctionServiceTrigger();
#endif

	interrupt_restore_corcon;
}
