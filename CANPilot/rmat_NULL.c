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

//		These are the routines for maintaining a direction cosine matrix
//		that can be used to transform vectors between the earth and plane
//		coordinate systems. The 9 direction cosines in the matrix completely
//		define the orientation of the plane with respect to the earth.
//		The inverse of the matrix is equal to its transpose. This defines
//		the so-called orthogonality conditions, which impose 6 constraints on
//		the 9 elements of the matrix.

//	All numbers are stored in 2.14 format.
//	Vector and matrix libraries work in 1.15 format.
//	This combination allows values of matrix elements between -2 and +2.
//	Multiplication produces results scaled by 1/2.


#define RMAX15 0b0110000000000000	//	1.5 in 2.14 format

#define GGAIN SCALEGYRO*6*(RMAX*0.025)		//	integration multiplier for gyros 15mv/degree/sec
fractional ggain = GGAIN ;

#if ( BOARD_TYPE == UDB3_BOARD )
//Paul's gains corrected for GGAIN
#define KPROLLPITCH 256*5
#define KIROLLPITCH 256
#else
//Paul's gains:
#define KPROLLPITCH 256*10
#define KIROLLPITCH 256*2
#endif

#define KPYAW 256*4
#define KIYAW 32

#define GYROSAT 15000
// threshold at which gyros may be saturated

//	rmat is the matrix of direction cosines relating
//	the body and earth coordinate systems.
//	The columns of rmat are the axis vectors of the plane,
//	as measured in the earth reference frame.
//	rmat is initialized to the identity matrix in 2.14 fractional format
fractional rmat[] = { RMAX , 0 , 0 , 0 , RMAX , 0 , 0 , 0 , RMAX } ;

//	rup is the rotational update matrix.
//	At each time step, the new rmat is equal to the old one, multiplied by rup.
fractional rup[] = { RMAX , 0 , 0 , 0 , RMAX , 0 , 0 , 0 , RMAX } ;

//	gyro rotation vector:
fractional omegagyro[] = { 0 , 0 , 0 } ;
fractional omega[] = { 0 , 0 , 0 } ;

//	gyro correction vectors:
fractional omegacorrP[] = { 0 , 0 , 0 } ;
fractional omegacorrI[] = { 0 , 0 , 0 } ;

//  acceleration, as measured in GPS earth coordinate system
fractional accelEarth[] = { 0 , 0 , 0 } ;

union longww accelEarthFiltered[] = { { 0 } , { 0 } ,  { 0 } } ;

//	correction vector integrators ;
union longww gyroCorrectionIntegral[] =  { { 0 } , { 0 } ,  { 0 } } ;

//	accumulator for computing adjusted omega:
fractional omegaAccum[] = { 0 , 0 , 0 } ;

//	gravity, as measured in plane coordinate system
fractional gplane[] = { 0 , 0 , GRAVITY } ;

//	horizontal velocity over ground, as measured by GPS (Vz = 0 )
fractional dirovergndHGPS[] = { 0 , RMAX/2 , 0 } ;

//	horizontal direction over ground, as indicated by Rmatrix
fractional dirovergndHRmat[] = { 0 , RMAX/2 , 0 } ;

//	rotation angle equal to omega times integration factor:
fractional theta[] = { 0 , 0 , 0 } ;

//	matrix buffer:
fractional rbuff[] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;

//	vector buffer
fractional errorRP[] = { 0 , 0 , 0 } ;
fractional errorYawground[] = { 0 , 0 , 0 } ;
fractional errorYawplane[]  = { 0 , 0 , 0 } ;

//	measure of error in orthogonality, used for debugging purposes:
fractional error = 0 ;

fractional declinationVector[2] ;


void dcm_init_rmat( void )
{
}



int vref_adj ;

void read_gyros()
//	fetch the gyro signals and subtract the baseline offset, 
//	and adjust for variations in supply voltage
{
	return ;
}

//	multiplies omega times speed, and scales appropriately
int omegaSOG ( int omega , unsigned int speed  )
{
}

void adj_accel()
{
	return ;
}

//	The update algorithm!!
void rupdate(void)
//	This is the key routine. It performs a small rotation
//	on the direction cosine matrix, based on the gyro vector and correction.
//	It uses vector and matrix routines furnished by Microchip.
{
	return ;
}

//	normalization algorithm:
void normalize(void)
//	This is the routine that maintains the orthogonality of the
//	direction cosine matrix, which is expressed by the identity
//	relationship that the cosine matrix multiplied by its
//	transpose should equal the identity matrix.
//	Small adjustments are made at each time step to assure orthogonality.
{
	return ;
}

void roll_pitch_drift()
{
	return ;
}

void yaw_drift()
{
	return ;
}


#if (MAG_YAW_DRIFT == 1)

fractional magFieldEarth[3] ;

extern fractional udb_magFieldBody[3] ;
extern fractional udb_magOffset[3] ;

fractional magFieldEarthPrevious[3] ;
fractional magFieldBodyPrevious[3] ;

fractional rmatPrevious[9] ;

int offsetDelta[3] ;

void align_rmat_to_mag(void)
{
	return ;
}

void mag_drift()
{
	return ;
}

#endif


void PI_feedback(void)
{
	return ;
}


extern void dead_reckon(void) ;

void dcm_run_imu_step(void)
//	Read the gyros and accelerometers, 
//	update the matrix, renormalize it, 
//	adjust for roll and pitch drift,
//	and send it to the servos.
{
	return ;
}

