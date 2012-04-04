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

#include "..\libUDB\libUDB.h"

//Note:  The trap flags need to be moved out of telemetry.c and mavlink.c
volatile int trap_flags __attribute__ ((persistent));
volatile long trap_source __attribute__ ((persistent));
volatile int osc_fail_count __attribute__ ((persistent));


// My current thinking is to eliminate the need for these callbacks to exist
//  instead, i propose that each libUDB module that calls them gets intialised
//  with a function pointer, and if it's NULL (aka, unused functionality,
//  then nothing happens, but everything builds just fine.

void udb_barometer_callback_data(long pressure, int temperature, char status)
{
}

void udb_magnetometer_callback_data_available(void)
{
}


void udb_callback_read_sensors(void)
{
}

void udb_servo_callback_prepare_outputs(void)
{
}

void udb_background_callback_periodic(void)
{
}

void udb_background_callback_triggered(void)
{
}

void udb_callback_radio_did_turn_off(void)
{
}


int udb_gps_callback_get_byte_to_send(void)
{
	return 0;
}

void udb_gps_callback_received_byte(char rxchar)
{
}

int udb_serial_callback_get_byte_to_send(void)
{
	return 0;
}

void udb_serial_callback_received_byte(char rxchar)
{
}
