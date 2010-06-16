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


// used in the IXZ Tester

#define	ADCON2CONFIG 0b0010010000011000 ; // Vref+ ref, scana ch0, int every 7, 16word, usa A only


#define	yrateBUFF	ADCBUF3 
#define	zrateBUFF	ADCBUF2
#define	xrateBUFF	ADCBUF1
#define	xaccelBUFF	ADCBUF4
#define	yaccelBUFF	ADCBUF5
#define	zaccelBUFF	ADCBUF6

#define XSIGN +
#define YSIGN +
#define ZSIGN -

//#define VREF

#define SCALEGYRO 4.95
#define SCALEACCEL 2.64
