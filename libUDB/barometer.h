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


// barometer driver defintion


#ifndef BAROMETER_H
#define BAROMETER_H

#include "libUDB_internal.h"

// callback with return of pressure in uBar.
typedef void (*Barometer_callbackFunc)(unsigned long);

// Trigger service of nv memory in low priority process
void barometer_service_trigger( void );

// Initialise barometer service
void barometer_init( void );

void set_barometer_callback(Barometer_callbackFunc pcallback);

unsigned long barometer_read();

#endif

