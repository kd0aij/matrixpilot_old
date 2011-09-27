#include "flexiFunctionTypes.h"
#include "defines.h"

#include <dsp.h>

#define RMAX15 0b0110000000000000	//	1.5 in 2.14 format
#define RMAX   0b0100000000000000	//	1.0 in 2.14 format


componentReference* findComponentRefWithID(int compID)
{
	componentReference* pScanRef = componentReferences;
	int Index = 0;
	
	while(pScanRef->componentNum != -1)
	{
		if(pScanRef->componentNum == compID) return pScanRef;
	}
	
	return 0;
}


void runFlexiFunctions( functionSetting* pSettings, fractional* pRegisters, unsigned int max_functions)
{
	int 				functionNo = 0;		// Index of mixer in mixer list
	functionSetting* 	pSetting;
	fractional 			output;

	pSetting = &(pSettings[functionNo]);

	// Step through each mixer and run it
	while( (functionNo < max_functions) & (pSetting->functionType != 0) )
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

/*
fractional mixGainLim(MixerSetting* pSetting)
{

};
*/