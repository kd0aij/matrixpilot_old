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

const mavlink_parameter mavlink_parameters_list[] =
	{
#if ( RECORD_FREE_STACK_SPACE ==  1)
	{"MAXSTACK", 0.0 , 4096.0 ,  &mavlink_send_param_maxstack, &mavlink_set_maxstack , READWRITE },
#endif
	{"ROLLKP"         , 0.0 , 0.4    ,  &mavlink_send_param_rollkp     ,  &mavlink_set_rollkp       , PARAMETER_READWRITE },
	{"ROLLKD"         , 0.0 , 0.4    ,  &mavlink_send_param_rollkd     ,  &mavlink_set_rollkd       , PARAMETER_READWRITE },
	{"YAWKPAIL"       , 0.0 , 0.4    ,  &mavlink_send_param_yawkpail   ,  &mavlink_set_yawkpail     , PARAMETER_READWRITE },
	{"YAWKDAIL"       , 0.0 , 0.4    ,  &mavlink_send_param_yawkdail   ,  &mavlink_set_yawkdail     , PARAMETER_READWRITE },
	{"YAWKPRUD"       , 0.0 , 0.4    ,  &mavlink_send_param_yawkprud   ,  &mavlink_set_yawkprud     , PARAMETER_READWRITE },
	{"ROLLKPRUD"      , 0.0 , 0.4    ,  &mavlink_send_param_rollkprud  ,  &mavlink_set_rollkprud    , PARAMETER_READWRITE },
	{"PITCHGAIN"      , 0.0 , 0.4    ,  &mavlink_send_param_pitchgain  ,  &mavlink_set_pitchgain    , PARAMETER_READWRITE },
	{"RUDELEVMIXGAIN" , 0.0 , 0.7    ,  &mavlink_send_param_rudelevgain,  &mavlink_set_rudelevgain  , PARAMETER_READWRITE }
	} ;    

const int count_of_parameters_list =  sizeof mavlink_parameters_list / sizeof mavlink_parameters_list[0] ;
