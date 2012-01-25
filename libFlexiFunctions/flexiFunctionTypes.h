#ifndef FLEXIFUNCTION_TYPES_H
#define FLEXIFUNCTION_TYPES_H


#include <dsp.h>


/****************************************************************/
// pyFEdit generated file - DO NOT EDIT


typedef struct tagFuncData_NULL
{
} FuncData_null;


typedef struct tagFuncData_GAIN_OFFSET
{
	unsigned int	src;
	fractional	PosGain;
	fractional	NegGain;
	fractional	Offset;
	fractional	Constant;
} FuncData_gain_offset;


typedef struct tagFuncData_MULTIPLY
{
	unsigned int	src1;
	unsigned int	src2;
} FuncData_multiply;


typedef struct tagFuncData_LINEAR_MUX
{
	unsigned int	src1;
	unsigned int	src2;
	unsigned int	Control;
} FuncData_linear_mux;


typedef struct tagFuncData_CONDITIONAL_SET_REF
{
	unsigned int	src;
	unsigned int	srcCond;
	int	condMax;
	int	condMin;
	fractional	condInvalidOffset;
	fractional	condValidOffset;
} FuncData_conditional_set_ref;


typedef struct tagFuncData_CONDITIONAL_SET
{
	unsigned int	src;
	unsigned int	srcCond;
	int	condMax;
	int	condMin;
	fractional	setValue;
} FuncData_conditional_set;


typedef struct tagFuncData_CONDITIONAL_GAIN
{
	unsigned int	src;
	unsigned int	srcCond;
	int	condMax;
	int	condMin;
	fractional	condInvalidGain;
	fractional	condValidGain;
} FuncData_conditional_gain;


typedef struct tagFuncData_SCALE_TRIM_LIMIT
{
	unsigned int	src;
	int	subTrim;
	int	offset;
	int	scalePos;
	int	scaleNeg;
	int	limitMin;
	int	limitMax;
} FuncData_scale_trim_limit;


typedef struct tagFuncData_SCALE_REFTRIM_LIMIT
{
	unsigned int	src;
	int	subTrim;
	unsigned int	refOffset;
	int	scalePos;
	int	scaleNeg;
	int	limitMin;
	int	limitMax;
} FuncData_scale_reftrim_limit;


typedef struct tagFuncData_GAIN_LIMIT
{
	unsigned int	src;
	fractional	posGain;
	fractional	negGain;
	fractional	limitNeg;
	fractional	limitPos;
} FuncData_gain_limit;


typedef union
{
	FuncData_null	null;
	FuncData_gain_offset	gain_offset;
	FuncData_multiply	multiply;
	FuncData_linear_mux	linear_mux;
	FuncData_conditional_set_ref	conditional_set_ref;
	FuncData_conditional_set	conditional_set;
	FuncData_conditional_gain	conditional_gain;
	FuncData_scale_trim_limit	scale_trim_limit;
	FuncData_scale_reftrim_limit	scale_reftrim_limit;
	FuncData_gain_limit	gain_limit;
} functionData;


/****************************************************************/
// Function Settings


typedef struct tagFunctionSettings
{
  unsigned int    functionType        : 6 ;   // The type of function
  unsigned int    setValue            : 2 ;   // The destination is set(0) added(1) or cleared (2)
  unsigned int    dest                : 8 ;   // The destination register
  functionData    data;
} functionSetting;


/****************************************************************/
// Mixer functions


typedef int (*pflexFunction)(functionSetting*, fractional*); 


extern fractional null_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional gain_offset_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional multiply_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional linear_mux_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional conditional_set_ref_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional conditional_set_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional conditional_gain_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional scale_trim_limit_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional scale_reftrim_limit_function(functionSetting* pSetting, fractional* pRegisters);
extern fractional gain_limit_function(functionSetting* pSetting, fractional* pRegisters);



extern void runFlexiFunctions( functionSetting* pSettings, fractional* pRegisters, unsigned int max_functions );


extern const pflexFunction flexiFunctions [];


/****************************************************************/
// Component references to support MAVlink


typedef char registerName[16];


typedef struct tagflexiFunctionComponentData
{
  unsigned char	numberRegs;   				// Number of registers used
  unsigned char	numberFuncs;  				// Number of functions used
} flexiFunctionComponentData;


typedef struct tagComponentReference
{
  int	componentNum;   							// The component number
  functionSetting*	pFunctionData;				// The function data table for this component
  flexiFunctionComponentData* pComponentData;		// The function data table for this component
  unsigned char	maxRegs;   					// Maximum number of registers
  unsigned char	maxFuncs;  					// Maximum number of functions
} componentReference;


// Table of flexifunction data for different MAVlinkj components
extern const componentReference componentReferences[];


// Helper function for finding component information from an array of component references
extern componentReference* findComponentRefWithID(int compID);


#endif
