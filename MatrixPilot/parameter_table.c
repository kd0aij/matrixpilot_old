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

#include "parameter_table.h"

#include "gain_variables.h" // Needed for access to internal DCM value

const mavlink_parameter_parser	mavlink_parameter_parsers[] =
	{
	{&mavlink_send_param_null, 						&mavlink_set_param_null, 					MAVLINK_TYPE_FLOAT},
	{&mavlink_send_param_int_as_float, 				&mavlink_set_param_float_to_int, 			MAVLINK_TYPE_FLOAT},
	{&mavlink_send_param_Q14_as_float, 				&mavlink_set_param_float_to_Q14, 			MAVLINK_TYPE_FLOAT},
	{&mavlink_send_param_pwtrim_as_float, 			&mavlink_set_param_float_to_pwtrim,			MAVLINK_TYPE_FLOAT},
	{&mavlink_send_param_gyroscale_Q14_as_float, 	&mavlink_set_param_float_to_gyroscale_Q14, 	MAVLINK_TYPE_FLOAT},
	};

const mavlink_parameter mavlink_parameters_list[] =
	{
#if ( RECORD_FREE_STACK_SPACE ==  1)
	{"MAXSTACK", 0.0 , 4096.0 ,  &mavlink_send_param_maxstack, &mavlink_set_maxstack , READWRITE },
#endif
	{"ROLLKP"         , 0.0 , 0.4    ,  UDB_TYPE_Q14			, PARAMETER_READWRITE,	(void*) &rollkp , sizeof(rollkp) },
	{"ROLLKD"         , 0.0 , 0.4    ,  UDB_TYPE_GYROSCALE_Q14	, PARAMETER_READWRITE,	(void*) &rollkd , sizeof(rollkd) },
	{"YAWKPAIL"       , 0.0 , 0.4    ,  UDB_TYPE_Q14			, PARAMETER_READWRITE,	(void*) &yawkpail , sizeof(yawkpail)  },
	{"YAWKDAIL"       , 0.0 , 0.4    ,  UDB_TYPE_GYROSCALE_Q14	, PARAMETER_READWRITE,	(void*) &yawkdail , sizeof(yawkdail)  },
	{"YAWKPRUD"       , 0.0 , 0.4    ,  UDB_TYPE_Q14			, PARAMETER_READWRITE,	(void*) &yawkprud , sizeof(yawkprud)  },
	{"ROLLKPRUD"      , 0.0 , 0.4    ,  UDB_TYPE_Q14			, PARAMETER_READWRITE,	(void*) &rollkprud , sizeof(rollkprud)  },
	{"PITCHGAIN"      , 0.0 , 0.4    ,  UDB_TYPE_Q14			, PARAMETER_READWRITE,	(void*) &pitchgain , sizeof(pitchgain)  },
	{"RUDELEVMIXGAIN" , 0.0 , 0.7    ,  UDB_TYPE_Q14			, PARAMETER_READWRITE,	(void*) &rudderElevMixGain , sizeof(rudderElevMixGain)  },


//	{"RC_NUM_INPUTS"    , 0.0 	, 32.0    ,  &mavlink_send_param_int_as_float	,	&mavlink_set_param_float_to_int		, PARAMETER_READ	,	(void*) &udb_pwTrim[1], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM1"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[1], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM2"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[2], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM3"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[3], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM4"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[4], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM5"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[5], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM6"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[6], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM7"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[7], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM8"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[8], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM9"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[9], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM10"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[10], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM11"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[11], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM12"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[12], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM13"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[13], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM14"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[14], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM15"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[15], sizeof(udb_pwTrim[0]) },
	{"RC_TRIM16"         , 800.0 , 2500.0  ,  UDB_TYPE_PWM	, PARAMETER_READWRITE,	(void*) &udb_pwTrim[16], sizeof(udb_pwTrim[0]) },
	} ;    

const int count_of_parameters_list = sizeof(mavlink_parameters_list) / sizeof(mavlink_parameter);
