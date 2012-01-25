#ifndef MIXER_OPTIONS_H
#define MIXER_OPTIONS_H

#include "flexifunction_options.h"

// Fix this to your particular radio at 100% travel
#define MIX_PWM_RANGE 800

/*#if(FIXED_TRIMPOINT == 1)
	#define MIX_PWM_MID CHANNEL_TRIMPOINT
#else
	#define MIX_PWM_MID	3030

#define MIX_PWM_MIN	(MIX_PWM_MID-MIX_PWM_RANGE)
#define MIX_PWM_MAX	(MIX_PWM_MID+MIX_PWM_RANGE)
*/

#define MAX_MIXER_FUNCS 	80
#define MAX_MIXER_REGS 		60

#if(MAX_BUFFER_FUNCS < MAX_MIXER_FUNCS)
 #error("Maximum mixer function count does not fit in the buffer")
#endif

#endif

