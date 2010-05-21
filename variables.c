#include "libUDB.h"


//	Variables.

int udb_pwIn[MAX_INPUTS+1] ;	// pulse widths of radio inputs
int udb_pwTrim[MAX_INPUTS+1] ;	// initial pulse widths for trimming
int udb_pwOut[MAX_OUTPUTS+1] ;	// pulse widths for servo outputs

int pitch_control, roll_control, yaw_control, altitude_control ;

int dutycycle ;				// used to compute PWM duty cycle

int waggle = 0 ;
int calib_timer, standby_timer ;
int gps_data_age;

boolean timer_5_on = 0 ;
boolean needSaveExtendedState = 0 ;
int defaultCorcon = 0 ;
