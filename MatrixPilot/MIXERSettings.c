#include "flexFunctionTypes.h"

#include "MIXERVars.h"

#define RMAX15 0b0110000000000000  //  1.5 in 2.14 format
#define RMAX   0b0100000000000000  //  1.0 in 2.14 format


#define PercenttoQ14(n) ((int)(n * 163.84))
#define FloattoQ14(n) ((int)(n * 16384))

MixerSetting MIXER_data[MAX_MIXER_FUNCS] = 
{
	{1, 0, 25	{{.sum_offset_function = { 1,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 26	{{.sum_offset_function = { 2,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 27	{{.sum_offset_function = { 3,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{1, 0, 28	{{.sum_offset_function = { 4,PercenttoQ14(100.0),PercenttoQ14(100.0),PercenttoQ14(0.0),PercenttoQ14(0.0)} } },
	{6, 0, 25	{{.scale_trim_limit_function = { 0,0,PercenttoQ14(0),1000,1000,2000,4000} } },
	{6, 0, 26	{{.scale_trim_limit_function = { 0,0,PercenttoQ14(0),1000,1000,2000,4000} } },
	{6, 0, 27	{{.scale_trim_limit_function = { 0,0,PercenttoQ14(0),1000,1000,2000,4000} } },
	{6, 0, 28	{{.scale_trim_limit_function = { 0,0,PercenttoQ14(0),1000,1000,2000,4000} } },
	{6, 0, 29	{{.scale_trim_limit_function = { 0,0,PercenttoQ14(0),1000,1000,2000,4000} } },
	{6, 0, 30	{{.scale_trim_limit_function = { 0,0,PercenttoQ14(0),1000,1000,2000,4000} } },
	{6, 2, 31	{{.scale_trim_limit_function = { 0,0,PercenttoQ14(0),1000,1000,2000,4000} } },

};
