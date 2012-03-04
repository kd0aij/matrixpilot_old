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

const mavlink_parameter mavlink_parameters_list[] =
	{
#if ( RECORD_FREE_STACK_SPACE ==  1)
	{"MAXSTACK", 0.0 , 4096.0 ,  &mavlink_send_param_maxstack, &mavlink_set_maxstack , READWRITE },
#endif
	{"ROLLKP"         , 0.0 , 0.4    ,  &mavlink_send_param_Q14_as_float   			,	&mavlink_set_param_float_to_Q14				, PARAMETER_READWRITE,	(void*) &rollkp },
	{"ROLLKD"         , 0.0 , 0.4    ,  &mavlink_send_param_gyroscale_Q14_as_float	,	&mavlink_set_param_float_to_gyroscale_Q14	, PARAMETER_READWRITE,	(void*) &rollkd },
	{"YAWKPAIL"       , 0.0 , 0.4    ,  &mavlink_send_param_Q14_as_float   			,	&mavlink_set_param_float_to_Q14				, PARAMETER_READWRITE,	(void*) &yawkpail  },
	{"YAWKDAIL"       , 0.0 , 0.4    ,  &mavlink_send_param_gyroscale_Q14_as_float	,	&mavlink_set_param_float_to_gyroscale_Q14	, PARAMETER_READWRITE,	(void*) &yawkdail  },
	{"YAWKPRUD"       , 0.0 , 0.4    ,  &mavlink_send_param_Q14_as_float			,	&mavlink_set_param_float_to_Q14				, PARAMETER_READWRITE,	(void*) &yawkprud  },
	{"ROLLKPRUD"      , 0.0 , 0.4    ,  &mavlink_send_param_Q14_as_float			,	&mavlink_set_param_float_to_Q14				, PARAMETER_READWRITE,	(void*) &rollkprud  },
	{"PITCHGAIN"      , 0.0 , 0.4    ,  &mavlink_send_param_Q14_as_float			,	&mavlink_set_param_float_to_Q14				, PARAMETER_READWRITE,	(void*) &pitchgain  },
	{"RUDELEVMIXGAIN" , 0.0 , 0.7    ,  &mavlink_send_param_Q14_as_float			,	&mavlink_set_param_float_to_Q14				, PARAMETER_READWRITE,	(void*) &rudderElevMixGain  }
	} ;    

const int count_of_parameters_list =  sizeof mavlink_parameters_list / sizeof mavlink_parameters_list[0] ;
