#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"


//	Variables.

int rise[MAX_INPUTS] ;		// rising edge clock capture for radio inputs
int pwIn[MAX_INPUTS] ;		// pulse widths of radio inputs
int pwTrim[MAX_INPUTS] ;	// initial pulse widths for trimming
int pwOut[MAX_OUTPUTS] ;	// pulse widths for servo outputs

int pitch_control, roll_control ;

int dutycycle ;				// used to compute PWM duty cycle

int waggle = 0 ;
int calib_timer, standby_timer ;
int pulsesselin = 0 ;
int gps_data_age;
