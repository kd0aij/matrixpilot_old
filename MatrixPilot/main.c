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


#include "defines.h"

unsigned int squares[] = { 0 , 1 , 4 , 9 , 25 , 36 , 49 , 64 ,  81 , 100 , 1000 , 10000 , 65535 } ;
unsigned long int long_squares[] = {
					0 ,
					1 ,
					4 ,
				//	9 ,
					16 ,
				//	9 ,
				//	16 ,
					32 ,
				//	25 ,
				//	36 ,
				//	49 ,
					64 ,
				//	81 ,
				//	100 ,
					128 ,
				//	144 ,
				//	225 ,
					256 ,
					512 ,
					1024 ,
					2048 ,
					4096 ,
					8192 ,
					16384 ,
					32768 ,
					65536	,
					131072	,
					262144,
					524288	,
					1048576	,
					2097152	,
					4194304	,
					8388608	,
					16777216	,
					33554432	,
					67108864	,
					0b01000000000000000000000000000000,
					0xFFFFFFFF	,
				} ;								
unsigned int roots[28] ;
int count ;
extern unsigned int square_root_int ( unsigned int ) ;
extern unsigned int square_root_long_int ( unsigned long int ) ;

int main (void)
{
	count = 28 ;
	count = 28 ;
	while ( count )
	{
		count -- ;
		roots[count] = square_root_long_int( long_squares[count] ) ;
	}
	count = 28 ;
	count = 28 ;
	while(1)
	{
	}
}

/*

//	main program for testing the IMU.

int main (void)
{
	udb_init() ;
	dcm_init() ;
	init_servoPrepare() ;
	init_states() ;
	init_behavior() ;
	init_serial() ;
	
	udb_run() ;
	// This never returns.
	
	return 0 ;
}
*/
