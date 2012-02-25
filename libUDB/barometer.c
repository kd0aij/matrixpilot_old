//
// Copyright 2009-2012 MatrixPilot Team
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
//

#include "libUDB_internal.h"
#include "barometer.h"


/** V A R I A B L E S **********************************************/

static Barometer_callbackFunc callbackFunc;


/** F U N C T I O N S **********************************************/

void barometer_init(void)
{
}

void barometer_service_trigger(void)
{
}

void set_barometer_callback(Barometer_callbackFunc pcallback)
{
    callbackFunc = pcallback;
}

unsigned long barometer_read()
{
}
