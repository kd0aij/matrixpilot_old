#include "libDCM.h"
#include "defines.h"

//	main program for testing the IMU.

//	Select device options:
UDB_INCLUDE_CHIP_CONFIG_OPTIONS


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
	
