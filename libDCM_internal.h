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


#include "libDCM.h"

void estYawDrift(void) ;
void estimateWind(void) ;

void dcm_run_imu_step(void) ;	// This needs to be run every 25ms
void rxMagnetometer(void) ;		// This should be called every 250ms


extern signed char	actual_dir ;
extern int velocity_previous  ;
extern boolean skipYawDrift ;

extern fractional dirovergndHRmat[] ;
extern fractional dirovergndHGPS[] ;
extern fractional omega[] ;

extern union longbbbb tow ;
extern union intbb    sog_gps , cog_gps , climb_gps, week_no ;
extern unsigned char  hdop ;
extern union longbbbb xpg , ypg , zpg ;
extern union intbb    xvg , yvg , zvg ;
extern unsigned char  mode1 , mode2 , svs, hdop ;

extern int forward_acceleration  ;

extern unsigned char  	lat_cir ;
extern int				cos_lat ;
