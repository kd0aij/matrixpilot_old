#include "libUDB_internal.h"

void udb_init()
{
	defaultCorcon = CORCON;
	
	udb_init_ADC() ;
	udb_init_clock() ;
	udb_init_capture() ;
	udb_init_I2C() ;
	udb_init_GPS2() ;
	udb_init_USART1() ;
	udb_init_pwm() ;
	
	return ;
}
