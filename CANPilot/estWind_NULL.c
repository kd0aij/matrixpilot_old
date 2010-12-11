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


#include "../libDCM/libDCM_internal.h"

//int groundVelocityHistory[3] = { 0 , 0 , 0 } ;
//int fuselageDirectionHistory[3] = { 0 , 0 , 0 } ;

unsigned int estimatedAirspeed = 0 ;
int estimatedWind[3] = { 0 , 0 , 0 } ;

#define MINROTATION 	( (int)( 0.2 * RMAX ) )


void estimateWind( void )
{
	return ;	
}
