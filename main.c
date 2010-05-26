#include "libDCM.h"
#include "defines.h"

//	main program for testing the IMU.
//	Select device options:

_FOSC( CSW_FSCM_OFF & HS ) ; 	// external high speed crystal
_FWDT( WDT_OFF ) ;				// no watchdog timer
_FBORPOR( 	PBOR_OFF & // brown out detection off
			MCLR_EN &  // enable MCLR
			RST_PWMPIN & // pwm pins as pwm
			PWMxH_ACT_HI & // PWMH is active high
			PWMxL_ACT_HI ) ; // PMWL is active high
_FGS( CODE_PROT_OFF ) ; // no protection
_FICD( 0xC003 ) ;		// normal use of debugging port


int main (void)
{
	udb_init() ;
	init_servoPrepare() ;
	init_states() ;
	init_behavior() ;
	
	udb_run() ;
	// This never returns.
	
	return 0 ;
}
	
