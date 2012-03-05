 // This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009, 2010 MatrixPilot Team
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


// ROUTINES FOR CHANGING UAV ONBOARD PARAMETERS
// All paramaters are sent as type (float) between Ground Control Station and MatrixPilot.
// So paramaters have to be converted between type (float) and their normal representation.
// An explanation of the MAVLink protocol for changing paramaters can be found at:
// http://www.qgroundcontrol.org/parameter_interface

#ifndef PARAMETER_TABLE_H
#define PARAMETER_TABLE_H

#include "../libDCM/libDCM_internal.h" // Needed for access to internal DCM valueconst struct mavlink_parameter mavlink_parameters_list[] =
#include "../MAVlink/include/mavlink_types.h"


typedef struct tag_mavlink_parameter 
{ 	const char name[15] ;                       // Name that will be displayed in the GCS
	float min ;               					// Minimum allowed (float) value for parameter
	float max ;               					// Maximum allowed (float) value for parameter
	void (*send_param)(int16_t) ; 			    // Routine to send parameter to GCS after converting to float.
	void (*set_param)(float, int16_t) ;         // Routine to convert from float to local type and set
	char readonly ; 							// Parameter is readonly (true) or Read / Write (false)
	void* pparam ;								// Reference to variable
	unsigned int param_size ;					// parameter size in ram
} mavlink_parameter ;       					


typedef enum
{
	PARAMETER_READWRITE = 0,
	PARAMETER_READONLY,
} PARAMETER_ACCESS;
	

void mavlink_send_param_gyroscale_Q14_as_float( int16_t i ) ;
void mavlink_set_param_float_to_gyroscale_Q14(float setting, int16_t i ) ;

void mavlink_send_param_Q14_as_float( int16_t i ) ;
void mavlink_set_param_float_to_Q14(float setting, int16_t i ) ;

void mavlink_send_param_pwm_as_float( int16_t i ) ;
void mavlink_set_param_float_to_pwm(float setting, int16_t i ) ;

void mavlink_send_param_int_as_float( int16_t i ) ;
void mavlink_set_param_float_to_int(float setting, int16_t i ) ;



extern const mavlink_parameter mavlink_parameters_list[];
extern const int count_of_parameters_list;


typedef struct tag_mavlink_parameter_block
{
	const mavlink_parameter* const 	parameters;
	const unsigned int 				list_size ;
	const unsigned int 				data_storage_area ;
	const unsigned int 				data_storage_flags ;
} mavlink_parameter_block;

extern const mavlink_parameter_block mavlink_parameter_blocks[];
extern const int count_of_parameter_blocks;




#endif 	//PARAMETER_TABLE_H
