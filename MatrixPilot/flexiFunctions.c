#include "flexiFunctionTypes.h"
#include "defines.h"

#include <dsp.h>

#define RMAX15 0b0110000000000000	//	1.5 in 2.14 format
#define RMAX   0b0100000000000000	//	1.0 in 2.14 format


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



fractional sum_offset_function(functionSetting* pSetting, fractional* pRegisters)
{
	union longww 	ltemp;
	fractional 		ftemp;
	ftemp = pRegisters[pSetting->data.sum_offset.src];
	ftemp  -= pSetting->data.sum_offset.Offset;
	if(ftemp > 0)
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.sum_offset.PosGain);
	else
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.sum_offset.NegGain);	
	
	ltemp.WW <<= 2;
	ftemp = (fractional) ltemp._.W1;

	ftemp  += pSetting->data.sum_offset.Constant;

	return ftemp;
};

/*

fractional mixDualSum(MixerSetting* pSetting)
{
	return 0;
};

// Scale output, add offset and subtrim then apply full scale limit.
// This output option is good for HILSIM or non-pre mixed RC controls.
fractional mixScaleOffLim(MixerSetting* pSetting)
{
	union longww 	ltemp;
	fractional 		ftemp;
	ftemp = mix_registers[pSetting->data.scaleTrimLimit.src];
	if(ftemp > 0)
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.scaleTrimLimit.scalePos << 2);
	else
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.scaleTrimLimit.scaleNeg << 2);	
	
	ftemp = (fractional) ltemp._.W1;

	ftemp += pSetting->data.scaleTrimLimit.offset;
	ftemp += pSetting->data.scaleTrimLimit.subTrim;

	if(ftemp > pSetting->data.scaleTrimLimit.limitPos) 
		ftemp = pSetting->data.scaleTrimLimit.limitPos;
	else if (ftemp < pSetting->data.scaleTrimLimit.limitNeg) 
		ftemp = pSetting->data.scaleTrimLimit.limitNeg;

	return ftemp;
};


// Scale output, add referenced offset and subtrim then apply full scale limit.
// referenced offset can be a pwInTrim value or similar.
fractional mixScaleRefOffLim(MixerSetting* pSetting)
{
	union longww 	ltemp;
	fractional 		ftemp;
	ftemp = mix_registers[pSetting->data.scaleTrimLimit.src];
	if(ftemp > 0)
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.scaleTrimLimit.scalePos << 2);
	else
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.scaleTrimLimit.scaleNeg << 2);	
	
	ftemp = (fractional) ltemp._.W1;

	ftemp += mix_registers[pSetting->data.scaleRefTrimLimit.offsetRef];

	ftemp += pSetting->data.scaleTrimLimit.subTrim;

	if(ftemp > pSetting->data.scaleTrimLimit.limitPos) 
		ftemp = pSetting->data.scaleTrimLimit.limitPos;
	else if (ftemp < pSetting->data.scaleTrimLimit.limitNeg) 
		ftemp = pSetting->data.scaleTrimLimit.limitNeg;

	return ftemp;
};
*/


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

/*
fractional mixConditionalGain(MixerSetting* pSetting)
{
	union longww 	ltemp;
	fractional 		ftemp;
	fractional		fgain;
	boolean			state;

	// collect the reference condition value
	ftemp = mix_registers[pSetting->data.conditionalGain.srcCond];

	state = ( (ftemp >= pSetting->data.conditionalGain.condMin) & 
			(ftemp <= pSetting->data.conditionalGain.condMax) );

	
	ftemp = mix_registers[pSetting->data.conditionalGain.src];

	if(state == 0)
		fgain = pSetting->data.conditionalGain.cond1Gain;
	else
		fgain = pSetting->data.conditionalGain.cond2Gain;

	ltemp.WW = __builtin_mulss(ftemp, fgain);
	ltemp.WW <<= 2;
	ftemp = (fractional) ltemp._.W1;

	return ftemp;

};


fractional mixConditionalOffset(MixerSetting* pSetting)
{
	return 0;
};


fractional mixConditionalSet(MixerSetting* pSetting)
{
	fractional 		ctemp;
	fractional 		ftemp;

	// collect the reference condition value
	ctemp = mix_registers[pSetting->data.conditionalSet.srcCond];

	ftemp = mix_registers[pSetting->data.conditionalSet.src];

	if(( (ctemp >= pSetting->data.conditionalSet.condMin) & 
			(ctemp <= pSetting->data.conditionalSet.condMax) ))
		ftemp = pSetting->data.conditionalSet.setValue;
	else
		ftemp = mix_registers[pSetting->data.conditionalSet.src];

	return ftemp;
};


fractional mixGainLim(MixerSetting* pSetting)
{
	union longww 	ltemp;
	fractional 		ftemp;
	ftemp = mix_registers[pSetting->data.gainLimit.src];

	if(ftemp > 0)
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.gainLimit.posGain);
	else
		ltemp.WW = __builtin_mulss(ftemp, pSetting->data.gainLimit.negGain);	
	
	ltemp.WW <<= 2;
	ftemp = (fractional) ltemp._.W1;

	if(ftemp > pSetting->data.gainLimit.posLimit)
		ftemp = pSetting->data.gainLimit.posLimit;
	else if(ftemp < pSetting->data.gainLimit.negLimit)
		ftemp = pSetting->data.gainLimit.negLimit;

	return ftemp;
};
*/