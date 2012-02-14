#include "flexiFunctionTypes.h"
#include "defines.h"

#include <dsp.h>

#define RMAX15 0b0110000000000000	//	1.5 in 2.14 format
#define RMAX   0b0100000000000000	//	1.0 in 2.14 format


// Run the flexifunction by stepping through the list of functions one-by-one.
void runFlexiFunctions( functionSetting* pSettings, fractional* pRegisters, unsigned int max_functions)
{
	int 				functionNo = 0;		// Index of mixer in mixer list
	functionSetting* 	pSetting;
	fractional 			output;

	pSetting = &(pSettings[functionNo]);

	// Step through each mixer and run it
	while( (functionNo < flexiFunctionsUsed) & (pSetting->functionType != 0) )
	{	
		pRegisters[0] = 0;	// reset the NULL register to make sure

		output  =	flexiFunctions[pSetting->functionType] ( pSetting, pRegisters);

		// Always limit mixer output to +-RMAX15 or 1.5*full scale
		if(output > RMAX15) output = RMAX15;
		else if(output < -RMAX15) output = -RMAX15;

		if(pSetting->setValue == 0)
		{
			pRegisters[pSetting->dest] = output;
		}
		else if(pSetting->setValue == 1)
		{
			pRegisters[pSetting->dest] += output;
			
			// limit final output to +-RMAX15 or 1.5*full scale
			if(pRegisters[pSetting->dest] > RMAX15) 
				pRegisters[pSetting->dest] = RMAX15;
			else if (pRegisters[pSetting->dest] < -RMAX15) 
				pRegisters[pSetting->dest] = -RMAX15;
		}
		else if(pSetting->setValue == 2)
		{
			pRegisters[pSetting->dest] = 0;
		}


		functionNo++;
		pSetting = &(pSettings[functionNo]);
	};
};


fractional null_function(functionSetting* pSetting, fractional* pRegisters)
{
	return 0;
};



fractional gain_offset_function(functionSetting* pSetting, fractional* pRegisters)
{
	union longww 	ltemp;
	fractional 		ftemp;
	ftemp = pRegisters[pSetting->data.gain_offset.src];
	ftemp  -= pSetting->data.gain_offset.Offset;
	if(ftemp > 0)
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.gain_offset.PosGain);
	else
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.gain_offset.NegGain);	
	
	ltemp.WW <<= 2;
	ftemp = (fractional) ltemp._.W1;

	ftemp  += pSetting->data.gain_offset.Constant;

	return ftemp;
};

/*

fractional mixDualSum(MixerSetting* pSetting)
{
	return 0;
};

*/

// Scale output, add offset and subtrim then apply full scale limit.
// This output option is good for HILSIM or non-pre mixed RC controls.
fractional scale_trim_limit_function(functionSetting* pSetting, fractional* pRegisters)
{
	union longww 	ltemp;
	fractional 		ftemp;
	ftemp = pRegisters[pSetting->data.scale_trim_limit.src];
	if(ftemp > 0)
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.scale_trim_limit.scalePos << 2);
	else
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.scale_trim_limit.scaleNeg << 2);	
	
	ftemp = (fractional) ltemp._.W1;

	ftemp += pSetting->data.scale_trim_limit.offset;
	ftemp += pSetting->data.scale_trim_limit.subTrim;

	if(ftemp > pSetting->data.scale_trim_limit.limitMax) 
		ftemp = pSetting->data.scale_trim_limit.limitMax;
	else if (ftemp < pSetting->data.scale_trim_limit.limitMin) 
		ftemp = pSetting->data.scale_trim_limit.limitMin;

	return ftemp;
};


// Scale output, add referenced offset and subtrim then apply full scale limit.
// referenced offset can be a pwInTrim value or similar.
fractional scale_reftrim_limit_function(functionSetting* pSetting, fractional* pRegisters)
{
	union longww 	ltemp;
	fractional 		ftemp;
	ftemp = pRegisters[pSetting->data.scale_reftrim_limit.src];
	if(ftemp > 0)
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.scale_reftrim_limit.scalePos << 2);
	else
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.scale_reftrim_limit.scaleNeg << 2);	
	
	ftemp = (fractional) ltemp._.W1;

	ftemp += pRegisters[pSetting->data.scale_reftrim_limit.refOffset];

	ftemp += pSetting->data.scale_reftrim_limit.subTrim;

	if(ftemp > pSetting->data.scale_reftrim_limit.limitMax) 
		ftemp = pSetting->data.scale_reftrim_limit.limitMax;
	else if (ftemp < pSetting->data.scale_reftrim_limit.limitMin) 
		ftemp = pSetting->data.scale_reftrim_limit.limitMin;

	return ftemp;
};



fractional linear_mux_function(functionSetting* pSetting, fractional* pRegisters)
{
	union longww 	ltemp;
	fractional 		ftemp, ftemp2;
	fractional 		gainTemp, gainTemp2;

	gainTemp =	pRegisters[pSetting->data.linear_mux.Control];

	if(gainTemp < 0)
		gainTemp = 0;
	else if(gainTemp > RMAX)
		gainTemp = RMAX;

	gainTemp2 = RMAX - gainTemp; 

	ftemp = pRegisters[pSetting->data.linear_mux.src2];
	ltemp.WW = __builtin_mulss(ftemp, gainTemp);
	ltemp.WW <<= 2;
	ftemp = (fractional) ltemp._.W1;

	ftemp2 = pRegisters[pSetting->data.linear_mux.src1];
	ltemp.WW = __builtin_mulss(ftemp2, gainTemp2);
	ltemp.WW <<= 2;
	ftemp += (fractional) ltemp._.W1;

	return ftemp;
};


fractional conditional_gain_function(functionSetting* pSetting, fractional* pRegisters)
{
	union longww 	ltemp;
	fractional 		ftemp;
	fractional		fgain;
	boolean			state;

	// collect the reference condition value
	ftemp = pRegisters[pSetting->data.conditional_gain.srcCond];

	state = ( (ftemp >= pSetting->data.conditional_gain.condMin) & 
			(ftemp <= pSetting->data.conditional_gain.condMax) );

	
	ftemp = pRegisters[pSetting->data.conditional_gain.src];

	if(state == 0)
		fgain = pSetting->data.conditional_gain.condInvalidGain;
	else
		fgain = pSetting->data.conditional_gain.condValidGain;

	ltemp.WW = __builtin_mulss(ftemp, fgain);
	ltemp.WW <<= 2;
	ftemp = (fractional) ltemp._.W1;

	return ftemp;

};

fractional multiply_function(functionSetting* pSetting, fractional* pRegisters)
{
	return 0;
};

fractional gain_limit_function(functionSetting* pSetting, fractional* pRegisters)
{
	union longww 	ltemp;
	fractional 		ftemp;
	ftemp = pRegisters[pSetting->data.gain_limit.src];

	if(ftemp > 0)
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.gain_limit.posGain);
	else
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.gain_limit.negGain);	
	
	ltemp.WW <<= 2;
	ftemp = (fractional) ltemp._.W1;

	if(ftemp > pSetting->data.gain_limit.limitPos)
		ftemp = pSetting->data.gain_limit.limitPos;
	else if(ftemp < pSetting->data.gain_limit.limitNeg)
		ftemp = pSetting->data.gain_limit.limitNeg;

	return ftemp;
};

fractional conditional_set_ref_function(functionSetting* pSetting, fractional* pRegisters)
{
	return 0;
};

/*
fractional mixConditionalOffset(MixerSetting* pSetting)
{
	return 0;
};
*/

fractional conditional_set_function(functionSetting* pSetting, fractional* pRegisters)
{
	fractional 		ctemp;
	fractional 		ftemp;

	// collect the reference condition value
	ctemp = pRegisters[pSetting->data.conditional_set.srcCond];

	ftemp = pRegisters[pSetting->data.conditional_set.src];

	if(( (ctemp >= pSetting->data.conditional_set.condMin) & 
			(ctemp <= pSetting->data.conditional_set.condMax) ))
		ftemp = pSetting->data.conditional_set.setValue;
	else
		ftemp = pRegisters[pSetting->data.conditional_set.src];

	return ftemp;
};


fractional three_point_function(functionSetting* pSetting, fractional* pRegisters)
{
	fractional output;
	fractional X1;
	fractional X2;
	fractional Y1;
	fractional Y2;
	fractional 		delta;
	union longww 	ltemp;

	int 			gain = 0;

	fractional input = pRegisters[pSetting->data.three_point.src];

	if(input <= pSetting->data.three_point.inputLow)
		return pSetting->data.three_point.outputLow;

	if(input >= pSetting->data.three_point.inputHigh)
		return pSetting->data.three_point.outputHigh;

	if(input >= pSetting->data.three_point.inputMid)
	{
		X1 = pSetting->data.three_point.inputMid;
		X2 = pSetting->data.three_point.inputHigh;
		Y1 = pSetting->data.three_point.outputMid;
		Y2 = pSetting->data.three_point.outputHigh;
	}
	else
	{
		X1 = pSetting->data.three_point.inputLow;
		X2 = pSetting->data.three_point.inputMid;
		Y1 = pSetting->data.three_point.outputLow;
		Y2 = pSetting->data.three_point.outputMid;
	}
	
	input -= X1;
	if(X2 <= X1) return pSetting->data.three_point.outputLow;
	if(Y1 == Y2) return pSetting->data.three_point.outputLow;

	delta = X2 - X1;

	// Find the gain required to increase delta to be in range RMAX to RMAX/2
	while(delta < RMAX/2)
	{
		gain++;
		delta <<= 1;
	}

	if(delta > RMAX)
	{
		gain--;
		delta >>= 1;
	}

	ltemp.WW = 0;
	ltemp._.W1 = (Y2 - Y1);		//  does this need to be inverted???


	// Limit numerator to +-RMAX/4 and adjust gain
	if(ltemp.WW > 0)
	{
		while(ltemp._.W1 > RMAX/4)
		{
			gain++;
			ltemp.WW >>= 1;
		}
	}
	else
	{
		while(ltemp._.W1 < -RMAX/4)
		{
			gain++;
			ltemp.WW >>= 1;
		}
	}

	output = __builtin_divsd( ltemp.WW,  delta ); //(int) (fractional)

	
	ltemp.WW = __builtin_mulss(output, input);	
//	ltemp.WW <<= 1;									// To correct for input RMAX
	ltemp.WW <<= gain;
	output = (fractional) (ltemp._.W1 + Y1);

	return output;
}

/*
fractional mixGainLim(MixerSetting* pSetting)
{

};
*/
