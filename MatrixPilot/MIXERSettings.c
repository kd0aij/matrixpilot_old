#include "flexiFunctionTypes.h"

#include "MIXERVars.h"

#define RMAX15 0b0110000000000000  //  1.5 in 2.14 format
#define RMAX   0b0100000000000000  //  1.0 in 2.14 format


#define PercenttoQ14(n) ((int)(n * 163.84))
#define FloattoQ14(n) ((int)(n * 16384))

functionSetting MIXER_data[MAX_MIXER_FUNCS] = 
{
	{9, 0, 26, 	{.gain_limit = { 1,PercenttoQ14(100),PercenttoQ14(-100),PercenttoQ14(0.0),PercenttoQ14(100.0)} } },
	{9, 0, 27, 	{.gain_limit = { 2,PercenttoQ14(100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(100.0)} } },
	{9, 0, 28, 	{.gain_limit = { 4,PercenttoQ14(100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(100.0)} } },
	{5, 0, 26, 	{.conditional_set = { 26,23,1,1,PercenttoQ14(100.0)} } },
	{5, 0, 27, 	{.conditional_set = { 27,23,1,1,PercenttoQ14(100.0)} } },
	{5, 0, 28, 	{.conditional_set = { 28,23,1,1,PercenttoQ14(100.0)} } },
	{1, 0, 32, 	{.gain_offset = { 21,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{3, 0, 30, 	{.linear_mux = { 15,1,26} } },
	{3, 0, 31, 	{.linear_mux = { 16,2,27} } },
	{3, 1, 32, 	{.linear_mux = { 18,4,28} } },
	{5, 0, 33, 	{.conditional_set = { 17,23,1,1,PercenttoQ14(0.0)} } },
	{1, 0, 34, 	{.gain_offset = { 6,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 35, 	{.gain_offset = { 7,PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 37, 	{.gain_offset = { 30,PercenttoQ14(60.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 41, 	{.gain_offset = { 30,PercenttoQ14(100),PercenttoQ14(60.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 32, 	{.gain_offset = { 30,PercenttoQ14(-40.0),PercenttoQ14(-40.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 38, 	{.gain_offset = { 31,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 40, 	{.gain_offset = { 32,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 39, 	{.gain_offset = { 33,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 37, 	{.gain_offset = { 34,PercenttoQ14(-100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 41, 	{.gain_offset = { 34,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 42, 	{.gain_offset = { 34,PercenttoQ14(-100.0),PercenttoQ14(-100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 43, 	{.gain_offset = { 34,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 37, 	{.gain_offset = { 35,PercenttoQ14(-50.0),PercenttoQ14(-50.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 41, 	{.gain_offset = { 35,PercenttoQ14(50.0),PercenttoQ14(50.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 42, 	{.gain_offset = { 35,PercenttoQ14(120.0),PercenttoQ14(120.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 43, 	{.gain_offset = { 35,PercenttoQ14(-120.0),PercenttoQ14(-120.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 38, 	{.gain_offset = { 35,PercenttoQ14(-35.0),PercenttoQ14(00.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 1, 39, 	{.gain_offset = { 3,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{8, 0, 37, 	{.scale_reftrim_limit = { 37,0,8,1000,1000,2000,4000} } },
	{8, 0, 38, 	{.scale_reftrim_limit = { 38,0,9,1000,1000,2000,4000} } },
	{8, 0, 39, 	{.scale_reftrim_limit = { 39,0,10,1000,1000,2000,4000} } },
	{8, 0, 40, 	{.scale_reftrim_limit = { 40,0,11,1000,1000,2000,4000} } },
	{8, 0, 41, 	{.scale_reftrim_limit = { 41,0,12,1000,1000,2000,4000} } },
	{8, 0, 42, 	{.scale_reftrim_limit = { 42,0,13,1000,1000,2000,4000} } },
	{8, 0, 43, 	{.scale_reftrim_limit = { 43,0,14,1000,1000,2000,4000} } },
	{0, 2, 0, 	{.null = { } } },
	{0, 2, 0, 	{.null = { } } },

};
