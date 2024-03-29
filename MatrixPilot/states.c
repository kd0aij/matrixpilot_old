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


#include "defines.h"
#include "heartbeat.h"
#include "mode_switch.h"

#ifdef USE_MAVLINK_DBGIO
#include "mavlink_types.h"
int16_t mavlink_serial_send(mavlink_channel_t chan, uint8_t buf[], uint16_t len);
extern uint8_t dbg_buff[50];
#endif

#ifdef USE_DEBUG_IO
#define DPRINT printf
#else
#define DPRINT(args...)
#endif

union fbts_int flags;
int16_t waggle = 0;
static int wagInterval = 0;

//uint8_t counter = 0;

//#define CALIB_PAUSE (5 * HEARTBEAT_HZ)    // wait for 5 seconds of runs through the state machine
//#define STANDBY_PAUSE 8		// pause for 4 seconds

#define CALIB_PAUSE (10 * HEARTBEAT_HZ)    // wait for 10 seconds of runs through the state machine

#define STANDBY_PAUSE 48		// pause for 24 seconds after first GPS fix
#define NUM_WAGGLES   4     // waggle 4 times during the end of the standby pause (this number must be less than STANDBY_PAUSE)
#define WAGGLE_SIZE   300

static int16_t calib_timer = CALIB_PAUSE;
static int16_t standby_timer = STANDBY_PAUSE;

static void startS(void);
static void calibrateS(void);
static void acquiringS(void);
static void manualS(void);
static void stabilizedS(void);
static void waypointS(void);
static void returnS(void);

static void ent_returnS(void);

//	Implementation of state machine.
//	Examine the state of the radio and GPS and supervisory channel to decide how to control the plane.

void (*stateS)(void) = &startS;

void init_states(void)
{
#ifdef USE_MAVLINK_DBGIO
	int len = snprintf((char*)dbg_buff, 50, "init_states()\r\n");
	mavlink_serial_send(0, dbg_buff, len);
#else
	DPRINT("init_states()\r\n");
#endif
	flags.WW = 0;
	waggle = 0;
	gps_data_age = HEARTBEAT_HZ * (GPS_DATA_MAX_AGE + 1);
	dcm_flags._.dead_reckon_enable = 0;
	stateS = &startS;
}

void udb_callback_radio_did_turn_off(void)
{
}

// Called at HEARTBEAT_HZ

void udb_background_callback_periodic(void)
{
	// read flight mode switch (sets flags bits)
	flight_mode_switch_check_set();
	// Update the nav capable flag. If the GPS has a lock, gps_data_age will be small.
	// For now, nav_capable will always be 0 when the Airframe type is AIRFRAME_HELI.
#if (AIRFRAME_TYPE != AIRFRAME_HELI)
	if (gps_data_age < (HEARTBEAT_HZ * GPS_DATA_MAX_AGE)) gps_data_age++;
	dcm_flags._.nav_capable = (gps_data_age < (HEARTBEAT_HZ * GPS_DATA_MAX_AGE));
#endif

#ifdef USE_MAVLINK_DBGIO
    static int xcnt = 0;
    if (xcnt++ > HEARTBEAT_HZ) {
        xcnt = 0;
        int len = snprintf((char*) dbg_buff, 50, "gps_data_age: %i, nav_capable: %i\r\n", gps_data_age, dcm_flags._.nav_capable);
        mavlink_serial_send(0, dbg_buff, len);
    }
#endif
        // Execute the activities for the current state.
	(*stateS)();
}

//	Functions that are executed upon first entrance into a state.

//	Calibrate state is used to wait for the filters to settle before recording A/D offsets.

static void ent_calibrateS(void)
{
	//	DPRINT("ent_calibrateS\r");

	flags._.GPS_steering = 0;
	flags._.pitch_feedback = 0;
	flags._.altitude_hold_throttle = 0;
	flags._.altitude_hold_pitch = 0;
	waggle = 0;
	stateS = &calibrateS;
	calib_timer = CALIB_PAUSE;
	LED_RED = LED_ON; // turn on mode led
}

//	Acquire state is used to wait for the GPS to achieve lock.

static void ent_acquiringS(void)
{
#ifdef USE_MAVLINK_DBGIO
	int len = snprintf((char*)dbg_buff, 50, "ent_acquiringS\r\n");
	mavlink_serial_send(0, dbg_buff, len);
#else
	DPRINT("\r\nent_acquiringS\r\n");
#endif

	flags._.GPS_steering = 0;
	flags._.pitch_feedback = 0;
	flags._.altitude_hold_throttle = 0;
	flags._.altitude_hold_pitch = 0;

	// almost ready to turn the control on, save the trims and sensor offsets
#if (FIXED_TRIMPOINT != 1)	// Do not alter trims from preset when they are fixed
#if(USE_NV_MEMORY == 1)
	if (udb_skip_flags.skip_radio_trim == 0)
	{
		udb_servo_record_trims();
	}
#else
	udb_servo_record_trims();
#endif
#endif
	dcm_calibrate();

	wagInterval = 0;
	waggle = WAGGLE_SIZE;
	throttleFiltered._.W1 = 0;
	stateS = &acquiringS;
	standby_timer = STANDBY_PAUSE;
	LED_RED = LED_OFF;
	LED_BLUE = LED_ON;
}

//	Manual state is used for direct pass-through control from radio to servos.

static void ent_manualS(void)
{
#ifdef USE_MAVLINK_DBGIO
	int len = snprintf((char*)dbg_buff, 50, "ent_manualS\r\n");
	mavlink_serial_send(0, dbg_buff, len);
#else
	DPRINT("ent_manualS\r\n");
#endif

	flags._.GPS_steering = 0;
	flags._.pitch_feedback = 0;
	flags._.altitude_hold_throttle = 0;
	flags._.altitude_hold_pitch = 0;
	waggle = 0;
	LED_RED = LED_OFF;
	stateS = &manualS;
}

//	Auto state provides augmented control.

static void ent_stabilizedS(void)
{
#ifdef USE_MAVLINK_DBGIO
	int len = snprintf((char*)dbg_buff, 50, "ent_stabilizedS\r\n");
	mavlink_serial_send(0, dbg_buff, len);
#else
	DPRINT("ent_stabilizedS\r\n");
#endif

#if (ALTITUDEHOLD_STABILIZED == AH_PITCH_ONLY)
	// When using pitch_only in stabilized mode, maintain the altitude
	// that the plane was at when entering stabilized mode.
	setTargetAltitude(IMUlocationz._.W1);
#endif

	flags._.GPS_steering = 0;
	flags._.pitch_feedback = 1;
	flags._.altitude_hold_throttle = (ALTITUDEHOLD_STABILIZED == AH_FULL);
	flags._.altitude_hold_pitch = (ALTITUDEHOLD_STABILIZED == AH_FULL || ALTITUDEHOLD_STABILIZED == AH_PITCH_ONLY);
	waggle = 0;
	LED_RED = LED_ON;
	stateS = &stabilizedS;
}

//	Same as the come home state, except the radio is on.
//	Come home is commanded by the mode switch channel (defaults to channel 4).

static void ent_waypointS(void)
{
#ifdef USE_MAVLINK_DBGIO
	int len = snprintf((char*)dbg_buff, 50, "ent_waypointS\r\n");
	mavlink_serial_send(0, dbg_buff, len);
#else
	DPRINT("ent_waypointS\r\n");
#endif

	flags._.GPS_steering = 1;
	flags._.pitch_feedback = 1;
	flags._.altitude_hold_throttle = (ALTITUDEHOLD_WAYPOINT == AH_FULL);
	flags._.altitude_hold_pitch = (ALTITUDEHOLD_WAYPOINT == AH_FULL || ALTITUDEHOLD_WAYPOINT == AH_PITCH_ONLY);

	if (!(FAILSAFE_TYPE == FAILSAFE_MAIN_FLIGHTPLAN && stateS == &returnS))
	{
		init_flightplan(0); // Only reset non-rtl waypoints if not already following waypoints
	}

	waggle = 0;
	LED_RED = LED_ON;
	stateS = &waypointS;
}

//	Come home state, entered when the radio signal is lost, and gps is locked.

static void ent_returnS(void)
{
#ifdef USE_MAVLINK_DBGIO
	int len = snprintf((char*)dbg_buff, 50, "ent_returnS\r\n");
	mavlink_serial_send(0, dbg_buff, len);
#else
	DPRINT("ent_returnS\r\n");
#endif

	flags._.GPS_steering = 1;
	flags._.pitch_feedback = 1;
	flags._.altitude_hold_throttle = (ALTITUDEHOLD_WAYPOINT == AH_FULL);
	flags._.altitude_hold_pitch = (ALTITUDEHOLD_WAYPOINT == AH_FULL || ALTITUDEHOLD_WAYPOINT == AH_PITCH_ONLY);
#if (FAILSAFE_HOLD == 1)
	flags._.rtl_hold = 1;
#endif	
#if (FAILSAFE_TYPE == FAILSAFE_RTL)
	init_flightplan(1);
#elif (FAILSAFE_TYPE == FAILSAFE_MAIN_FLIGHTPLAN)
	if (stateS != &waypointS)
	{
		init_flightplan(0); // Only reset non-rtl waypoints if not already following waypoints
	}
#endif

	waggle = 0;
	LED_RED = LED_ON;
	stateS = &returnS;
}

static void startS(void)
{
#ifdef USE_MAVLINK_DBGIO
	int len = snprintf((char*)dbg_buff, 50, "startS\r\n");
	mavlink_serial_send(0, dbg_buff, len);
#else
	DPRINT("startS()\r\n");
#endif

	ent_calibrateS();
}

static void calibrateS(void)
{
#if (NORADIO == 1)
	if (1)
#else
	if (udb_flags._.radio_on)
#endif
	{
		if ((calib_timer % (HEARTBEAT_HZ / 2)) == 0) {
			udb_led_toggle(LED_RED);
#ifdef USE_MAVLINK_DBGIO
			int len = snprintf((char*) dbg_buff, 50, "calibrateS %d\r\n", calib_timer);
			mavlink_serial_send(0, dbg_buff, len);
#endif
		}
		calib_timer--;
		if (calib_timer <= 0)
			ent_acquiringS();
	}
	else
	{
		//		DPRINT("calibrateS()\r\n");
		ent_calibrateS();
	}
}

static void acquiringS(void)
{
	wagInterval++;
#if (AIRFRAME_TYPE == AIRFRAME_HELI)
	ent_manualS();
	return;
#endif

	if (dcm_flags._.nav_capable && ((MAG_YAW_DRIFT == 0) || (magMessage == 7)))
	{
#if (NORADIO == 1)
		if (1)
#else
		if (udb_flags._.radio_on)
#endif
		{
			if (wagInterval >= (HEARTBEAT_HZ / 2))
			{
				wagInterval = 0;
				standby_timer--;
				udb_led_toggle(LED_BLUE);
				if (standby_timer == (NUM_WAGGLES + 1))
					waggle = WAGGLE_SIZE;
				else if (standby_timer <= NUM_WAGGLES)
					waggle = -waggle;
				else
					waggle = 0;
			}
			if (standby_timer == 6)
			{
				flags._.save_origin = 1;
			}
			else if (standby_timer == 2)
			{
				dcm_flags._.dead_reckon_enable = 1;
			}
			else if (standby_timer <= 0)
			{
				LED_BLUE = LED_OFF;
				waggle = 0;
				ent_manualS();
			}
		}
		//		else
//		{
//			waggle = 0;
//		}
	}
	else
	{
			if (wagInterval >= (HEARTBEAT_HZ / 2))
			{
				wagInterval = 0;
				waggle = 0;
			}
	}
}

static void manualS(void)
{
	if (udb_flags._.radio_on)
	{
		if (flight_mode_switch_waypoints() & dcm_flags._.nav_capable)
			ent_waypointS();
		else if (flight_mode_switch_stabilize())
			ent_stabilizedS();
	}
	else
	{
		if (dcm_flags._.nav_capable)
			ent_returnS();
		else
			ent_stabilizedS();
	}
}

static void stabilizedS(void)
{
	if (udb_flags._.radio_on)
	{
		if (flight_mode_switch_waypoints() & dcm_flags._.nav_capable)
			ent_waypointS();
		else if (flight_mode_switch_manual())
			ent_manualS();
	}
	else
	{
		if (dcm_flags._.nav_capable)
			ent_returnS();
	}
}

static void waypointS(void)
{
	static int blinkInterval = 0;
	if (blinkInterval++ >= (HEARTBEAT_HZ / 2))
	{
		blinkInterval = 0;
		udb_led_toggle(LED_RED);
	}

	if (udb_flags._.radio_on)
	{
		if (flight_mode_switch_manual())
			ent_manualS();
		else if (flight_mode_switch_stabilize())
			ent_stabilizedS();
	}
	else
	{
		ent_returnS();
	}
}

static void returnS(void)
{
	if (udb_flags._.radio_on)
	{
		if (flight_mode_switch_manual())
			ent_manualS();
		else if (flight_mode_switch_stabilize())
			ent_stabilizedS();
		else if (flight_mode_switch_waypoints() & dcm_flags._.nav_capable)
			ent_waypointS();
	}
	else
	{
#if (FAILSAFE_HOLD == 1)
		flags._.rtl_hold = 1;
#endif
	}
}
