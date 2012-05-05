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


#ifndef LIBDCM_H
#define LIBDCM_H


#include "../libUDB/libUDB.h"
#include "libDCM_defines.h"

////////////////////////////////////////////////////////////////////////////////
// libDCM.h defines the API for accessing the location and orientation information
// from the DCM algorithm and GPS.
// 
// Requires libUDB.
// 
// This library is designed to use libUDB, but to remain independent of the 
// sepcifics of the MatrixPilot application.


////////////////////////////////////////////////////////////////////////////////
// Vars
extern union dcm_fbts_word { struct dcm_flag_bits _ ; int W ; } dcm_flags ;


////////////////////////////////////////////////////////////////////////////////

#include "../libDCM/deadReckoning.h"
#include "../libDCM/estWind.h"
#include "../libDCM/estYawDrift.h"
#include "../libDCM/gpsParseCommon.h"
#include "../libDCM/mathLibNAV.h"
#include "../libDCM/rmat.h"

// Functions
void dcm_init( void ) ;
void dcm_calibrate(void) ;
void dcm_set_origin_location(long o_long, long o_lat, long o_alt) ;

// Called once each time the GPS reports a new location.
// After dead reckoning is complete, this callback may go away.
void dcm_callback_gps_location_updated(void) ;				// Callback


// Implement this callback to prepare the pwOut values.
// It is called at 40Hz (once every 25ms).
void dcm_servo_callback_prepare_outputs(void) ;				// Callback

// Convert an absolute location to relative
struct relative3D dcm_absolute_to_relative(struct waypoint3D absolute) ;


#endif // LIBDCM_H
