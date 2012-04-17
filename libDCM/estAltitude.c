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


#include "libDCM.h"
#include "../libUDB/barometer.h"
#include "estAltitude.h"
#include <stdio.h>

//	The origin is recorded as the altitude of the plane during power up of the control.


#if (BAROMETER_ALTITUDE == 1)
void udb_barometer_callback_data(long pressure, int temperature, char status)
{
	const float ground_altitude = 308.0;	// altitude at valley heights - this needs to be somehow set by the user - TODO
//	const float p0 = 101325;     // Pressure at sea level (Pa)  -- standard
//	const float p0 = 101660;     // Pressure at sea level (Pa)  -- currently according to BMCC weather station
	float altitude;
	float sea_level_pressure;

	sea_level_pressure = ((float)pressure / powf((1 - (ground_altitude/44330.0)), 5.255));

// 	altitude = (float)44330 * (1 - pow(((float) pressure/p0), 0.190295));
 	altitude = (float)44330 * (1 - pow(((float) pressure/sea_level_pressure), 0.190295));  // this is just the reverse of the sea_level_pressure algorithm for testing

//	printf( "T = %.1f C, P = %.2f mB, A = %.2f m\r\n", (double)temperature / 10.0, (double)pressure / 100.0, (double)altitude);
	printf( "barom %.1f, %.2f, %.2f, slp %.2f\r\n", (double)temperature / 10.0, (double)pressure / 100.0, (double)altitude, (double)sea_level_pressure / 100.0);
}
#endif

#if 0
/*
float temperature;
const float p0 = 101325;     // Pressure at sea level (Pa)

float scp1000_pressure_to_height(float pressure, float temperature)
{
        //return 44330.0 * (1.0 - powf(pressure / 101325.0, 0.19));
        //return logf(pressure / 101000.f) * (273.f + temperature) * (287.05f / 9.81f);

//        return log(pressure / 101000.0) * (273.0 + 20.0) * (-287.05 / 9.81);
        return log(pressure / p0) * (273.0 + temperature) * (-287.05 / 9.81);
}      
 
 */
#endif // 0


//extern signed char actual_altitude;
//extern signed char calculated_altitude;

void estAltitude(void)
{
	return ;
}
