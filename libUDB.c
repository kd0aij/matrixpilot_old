#include "libUDB_internal.h"

boolean timer_5_on = 0 ;
boolean needSaveExtendedState = 0 ;
int defaultCorcon = 0 ;


void udb_init(void)
{
	defaultCorcon = CORCON ;
	
	TRISFbits.TRISF0 = 0 ; //what is this doing?
	udb_init_ADC() ;
	udb_init_clock() ;
	udb_init_capture() ;
	udb_init_I2C() ;
	udb_init_GPS2() ;
	udb_init_USART1() ;
	udb_init_pwm() ;
	SRbits.IPL = 0 ;	// turn on all interrupt priorities
	
	return ;
}


void udb_run(void)
{
	while (1)			//  nothing else to do...entirely interrupt driven
	{
		indicate_loading_main ;
	}
	return ;
}


// the compiler does not respect the resource used by the Microchip math
// library, so interrupts need to save and restore extended state, and
// reset CORCON if firing in the middle of a math lib call.
void udb_setDSPLibInUse(boolean inUse)
{
	needSaveExtendedState = inUse ;
	return ;
}
