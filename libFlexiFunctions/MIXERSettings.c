#include "flexiFunctionTypes.h"

#include "MIXERVars.h"

#define RMAX15 0b0110000000000000  //  1.5 in 2.14 format
#define RMAX   0b0100000000000000  //  1.0 in 2.14 format


#define PercenttoQ14(n) ((int)(n * 163.84))
#define FloattoQ14(n) ((int)(n * 16384))



functionSetting flexifunction_buffer[80] = {};


functionSetting MIXER_data[MAX_MIXER_FUNCS] = 
{
	{9, 0, 21, 	{.gain_limit = { 1,PercenttoQ14(100),PercenttoQ14(-100),PercenttoQ14(0.0),PercenttoQ14(100.0)} } },
	{9, 0, 22, 	{.gain_limit = { 2,PercenttoQ14(100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(100.0)} } },
	{9, 0, 23, 	{.gain_limit = { 4,PercenttoQ14(100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(100.0)} } },
	{5, 0, 21, 	{.conditional_set = { 21,18,1,1,PercenttoQ14(100.0)} } },
	{5, 0, 22, 	{.conditional_set = { 22,18,1,1,PercenttoQ14(100.0)} } },
	{5, 0, 23, 	{.conditional_set = { 23,18,1,1,PercenttoQ14(100.0)} } },
	{1, 0, 27, 	{.gain_offset = { 16,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{3, 0, 25, 	{.linear_mux = { 10,1,21} } },
	{3, 0, 26, 	{.linear_mux = { 11,2,22} } },
	{3, 1, 27, 	{.linear_mux = { 13,4,23} } },
	{5, 0, 28, 	{.conditional_set = { 12,20,1,1,PercenttoQ14(0.0)} } },
	{1, 0, 29, 	{.gain_offset = { 6,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 30, 	{.gain_offset = { 7,PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 32, 	{.gain_offset = { 25,PercenttoQ14(60.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 36, 	{.gain_offset = { 25,PercenttoQ14(100),PercenttoQ14(60.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 35, 	{.gain_offset = { 25,PercenttoQ14(-40.0),PercenttoQ14(-40.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 33, 	{.gain_offset = { 26,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 35, 	{.gain_offset = { 27,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 34, 	{.gain_offset = { 28,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 32, 	{.gain_offset = { 29,PercenttoQ14(-100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 36, 	{.gain_offset = { 29,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 37, 	{.gain_offset = { 29,PercenttoQ14(-100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 38, 	{.gain_offset = { 29,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 39, 	{.gain_offset = { 29,PercenttoQ14(-100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 40, 	{.gain_offset = { 29,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 41, 	{.gain_offset = { 30,PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 32, 	{.gain_offset = { 30,PercenttoQ14(-50.0),PercenttoQ14(-50.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 36, 	{.gain_offset = { 30,PercenttoQ14(50.0),PercenttoQ14(50.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 37, 	{.gain_offset = { 30,PercenttoQ14(120.0),PercenttoQ14(120.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 38, 	{.gain_offset = { 30,PercenttoQ14(-120.0),PercenttoQ14(-120.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 39, 	{.gain_offset = { 30,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 40, 	{.gain_offset = { 30,PercenttoQ14(-100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 37, 	{.gain_offset = { 25,PercenttoQ14(20.0),PercenttoQ14(40.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 38, 	{.gain_offset = { 25,PercenttoQ14(40.0),PercenttoQ14(20.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 39, 	{.gain_offset = { 25,PercenttoQ14(0.0),PercenttoQ14(15.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 40, 	{.gain_offset = { 25,PercenttoQ14(15.0),PercenttoQ14(0.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 33, 	{.gain_offset = { 30,PercenttoQ14(-35.0),PercenttoQ14(00.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 33, 	{.gain_offset = { 3,PercenttoQ14(-10.0),PercenttoQ14(0.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 34, 	{.gain_offset = { 3,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{7, 0, 32, 	{.scale_trim_limit = { 32,0,3030,800,800,2000,4000} } },
	{7, 0, 33, 	{.scale_trim_limit = { 33,0,3030,800,800,2000,4000} } },
	{7, 0, 34, 	{.scale_trim_limit = { 34,0,2200,1600,0,2200,4000} } },
	{7, 0, 35, 	{.scale_trim_limit = { 35,0,3030,800,800,2000,4000} } },
	{7, 0, 36, 	{.scale_trim_limit = { 36,0,3030,1000,1000,2000,4000} } },
	{7, 0, 37, 	{.scale_trim_limit = { 37,0,3030,800,800,2000,4000} } },
	{7, 0, 38, 	{.scale_trim_limit = { 38,0,3030,800,800,2000,4000} } },
	{7, 0, 39, 	{.scale_trim_limit = { 39,0,3030,800,800,2000,4000} } },
	{7, 0, 40, 	{.scale_trim_limit = { 40,0,3030,800,800,2000,4000} } },
	{7, 0, 41, 	{.scale_trim_limit = { 41,0,3030,800,800,2000,4000} } },
	{0, 2, 0, 	{.null = { } } },
	{0, 2, 0, 	{.null = { } } },
	{0, 2, 0, 	{.null = { } } },
	{0, 2, 0, 	{.null = { } } },

};
