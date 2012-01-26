#include "flexiFunctionTypes.h"

#include "MIXERVars.h"

/*  component reference structure for reference only
typedef struct tagComponentReference
{
  int	componentNum;   							// The component number
  functionSetting*	pFunctionData;				// The function data table for this component
  flexiFunctionComponentData* pComponentData;		// The function data table for this component
  unsigned char	maxRegs;   					// Maximum number of registers
  unsigned char	maxFuncs;  					// Maximum number of functions
} componentReference;
*/

const componentReference componentReferences[] =
{
	{0, &MIXER_data, &MIXER_componentData, MAX_MIXER_REGS, MAX_MIXER_FUNCS, sizeof(functionData) },
	{-1, 0, 0, 0, 0 },
};



