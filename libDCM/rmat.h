#ifndef RMAT_H
#define RMAT_H

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


// Outside of libDCM, these should all be treated as read-only

#if (MAG_YAW_DRIFT == 1)
extern fractional magFieldEarth[3] ;
#endif

extern fractional rmat[] ;			//	gyro rotation vector:
extern fractional omegaAccum[] ;	//	accumulator for computing adjusted omega:
extern fractional omegagyro[] ;
extern fractional accelEarth[] ;	//  acceleration, as measured in GPS earth coordinate system
extern fractional gplane[];
extern fractional dirovergndHGPS[];	//	horizontal velocity over ground, as measured by GPS (Vz = 0 )
extern fractional dirovergndHRmat[];//	horizontal direction over ground, as indicated by Rmatrix

extern union intbb dcm_declination_angle ;	// Declination +-32767 = +-360deg

void dcm_init_rmat(void);
void dcm_run_imu_step(void);

void read_gyros(void);
void read_accel(void);


#endif // RMAT_H
