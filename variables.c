#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	Variables.


int rise[NUM_INPUTS] = {3000, 3000, 3000, 3000, 3000}; // rising edge clock capture for radio inputs
int pwIn[NUM_INPUTS] = {3000, 3000, 3000, 3000, 3000}; // pulse widths of radio inputs
int pwTrim[NUM_INPUTS] = {3000, 3000, 3000, 3000, 3000}; // initial pulse widths for trimming
int pwOut[NUM_OUTPUTS] = {3000, 3000, 3000, 3000, 3000} ; // pulse widths for servo outputs

int dutycycle ; // used to compute PWM duty cycle

int waggle = 0 ;
int calib_timer, standby_timer ;
int pulsesselin = 0 ;
