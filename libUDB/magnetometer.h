#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H


// global variables
extern int udb_magFieldBody[] ;				// magnetic field in the body frame of reference 
extern int udb_magOffset[] ; // = { 0 , 0 , 0 } ;  	// magnetic offset in the body frame of reference
extern int magGain[] ;       // = { RMAX , RMAX , RMAX } ; 	// magnetometer calibration gains
extern int rawMagCalib[] ;   // = { 0 , 0 , 0 } ;
extern int magFieldRaw[] ;
extern int magMessageb;      // = 0 ;   // message type


typedef void (*magnetometer_callback_funcptr)(void);

void rxMagnetometer(magnetometer_callback_funcptr) ;  // service the magnetometer

//void rxMagnetometer(void) ;  // service the magnetometer


#endif // MAGNETOMETER_H
