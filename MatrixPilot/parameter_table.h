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
#include "parameter_datatypes.h"

// Includes of all the data references required to build the parameter table.
#include "gain_variables.h"        // Needed for access to internal DCM value"


#if ( MAG_YAW_DRIFT == 1)
extern int udb_magOffset[];  // magnetic offset in the body frame of reference
extern int magGain[]; // magnetometer calibration gains
extern int rawMagCalib[];
#endif

// callback type for data services user
typedef void (*PT_callbackFunc)(boolean);

typedef union 
{
	float param_float;
	int32_t param_int32;
	uint32_t param_uint32;
} param_union_t;

typedef struct tag_mavlink_parameter_parser
{
	void (*send_param)(int16_t) ;
	void (*set_param)(mavlink_param_union_t, int16_t) ;
	const mavlink_message_type_t mavlink_type ;
} mavlink_parameter_parser;

extern const mavlink_parameter_parser	mavlink_parameter_parsers[];


typedef struct tag_mavlink_parameter 
{ 	const char name[15] ;                       // Name that will be displayed in the GCS
	param_union_t min ;    						// Minimum allowed value for parameter
	param_union_t max ;            				// Maximum allowed value for parameter
	udb_internal_type_t udb_param_type ;		// The internal UDB type for parsing
	char readonly ; 							// Parameter is readonly (true) or Read / Write (false)
	unsigned char* pparam ;						// Reference to variable
	unsigned int param_size ;					// parameter size in ram
} mavlink_parameter ;       					


typedef enum
{
	PARAMETER_READWRITE = 0,
	PARAMETER_READONLY,
} PARAMETER_ACCESS;


extern const mavlink_parameter mavlink_parameters_list[];
extern const int count_of_parameters_list;


// callback type for data services user
// TODO : MODE THIS FROM HERE????
//typedef void (*DSRV_callbackFunc)(boolean);


typedef struct tag_mavlink_parameter_block
{
	const unsigned int 				data_storage_area ;
	const unsigned int				block_start_index ;
	const unsigned int 				block_size ;
	const unsigned int 				data_storage_flags ;
	PT_callbackFunc					ploadCallback;
} mavlink_parameter_block;

extern const mavlink_parameter_block mavlink_parameter_blocks[];
extern const unsigned int mavlink_parameter_block_count;


// Collection of data on all memory areas served
//extern const mavlink_parameter_block data_services_table[];

// Length of the data service table in entries, not bytes
//extern const unsigned int data_service_table_count;



//*****************************************************************/
// Defines required to complete parameter table if these are not defined in
// options.h

//#if(MAG_YAW_DRIFT == 0)
//extern unsigned int null_int[3];
//#define udb_magOffset 	null_int;
//#define magGain 		null_int;
//#define rawMagCalib 	null_int;
//#endif

#ifndef AILERON_INPUT_CHANNEL
#define AILERON_INPUT_CHANNEL 0
#endif

#ifndef RUDDER_INPUT_CHANNEL
#define RUDDER_INPUT_CHANNEL 0
#endif

#ifndef ELEVATOR_INPUT_CHANNEL
#define ELEVATOR_INPUT_CHANNEL 0
#endif

#ifndef AILERON_SECONDARY_INPUT_CHANNEL
#define AILERON_SECONDARY_INPUT_CHANNEL 0
#endif


#ifndef ROLL_INPUT_CHANNEL
#define ROLL_INPUT_CHANNEL 0
#endif

#ifndef YAW_INPUT_CHANNEL
#define YAW_INPUT_CHANNEL 0
#endif

#ifndef PITCH_INPUT_CHANNEL
#define PITCH_INPUT_CHANNEL 0
#endif

#ifndef FLAP_INPUT_CHANNEL
#define FLAP_INPUT_CHANNEL 0
#endif

#ifndef CAMBER_INPUT_CHANNEL
#define CAMBER_INPUT_CHANNEL 0
#endif

#ifndef BRAKE_INPUT_CHANNEL
#define BRAKE_INPUT_CHANNEL 0
#endif

#ifndef SPOILER_INPUT_CHANNEL
#define SPOILER_INPUT_CHANNEL 0
#endif

#ifndef CROW_INPUT_CHANNEL
#define CROW_INPUT_CHANNEL 0
#endif



#endif 	//PARAMETER_TABLE_H