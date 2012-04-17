// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


#include "libDCM.h"
#include "gpsParseCommon.h"
#include "HILSIM.h"


#if ( HILSIM == 1 )

#if ( USE_VARIABLE_HILSIM_CHANNELS != 1 )
static unsigned char SIMservoOutputs[] = {
									0xFF, 0xEE,		//sync
									0x03, 0x04,		//S1
									0x05, 0x06,		//S2
									0x07, 0x08,		//S3
									0x09, 0x0A,		//S4
									0x0B, 0x0C,		//S5
									0x0D, 0x0E,		//S6
									0x0F, 0x10,		//S7
									0x11, 0x12,		//S8
									0x13, 0x14		//checksum
									};
 #define HILSIM_NUM_SERVOS 8
#else
#define HILSIM_NUM_SERVOS NUM_OUTPUTS
unsigned char SIMservoOutputs[(NUM_OUTPUTS*2) + 5] = {	0xFE, 0xEF,		//sync
														0x00			// output count
																		// Two checksum on the end
														};
#endif	// USE_VARIABLE_HILSIM_CHANNELS

static union intbb u_dot_sim_, v_dot_sim_, w_dot_sim_ ;
static union intbb u_dot_sim, v_dot_sim, w_dot_sim ;
static union intbb p_sim_, q_sim_, r_sim_ ;
static union intbb p_sim, q_sim, r_sim ;

// These are the data being delivered from the hardware-in-the-loop simulator
static unsigned char * const msg_BODYRATES_parse[] = {
			&p_sim_._.B0, &p_sim_._.B1, 							// roll rate
			&q_sim_._.B0, &q_sim_._.B1, 							// pitch rate
			&r_sim_._.B0, &r_sim_._.B1, 							// yaw rate
			&u_dot_sim_._.B0, &u_dot_sim_._.B1, 					// x accel (body frame)
			&v_dot_sim_._.B0, &v_dot_sim_._.B1, 					// y accel (body frame)
			&w_dot_sim_._.B0, &w_dot_sim_._.B1, 					// z accel (body frame)
};


int HILSIM_bodyrates_len(void)
{
	return (sizeof(msg_BODYRATES_parse) / sizeof(msg_BODYRATES_parse[0]));
}

void HILSIM_bodyrates_data(int index, char data)
{
	*msg_BODYRATES_parse[index] = data ;
}
#endif // HILSIM

void HILSIM_read_gyro(int* omegagyro)
{
#if ( HILSIM == 1 )
	omegagyro[0] = q_sim.BB;
	omegagyro[1] = p_sim.BB;
	omegagyro[2] = r_sim.BB;  
#endif
}

void HILSIM_read_accel(int* gplane)
{
#if ( HILSIM == 1 )
	gplane[0] = v_dot_sim.BB;
	gplane[1] = u_dot_sim.BB; 
	gplane[2] = w_dot_sim.BB;
#endif
}


void HILSIM_send_outputs( void )
{
#if ( HILSIM == 1 )

	// Setup outputs for HILSIM
	int i ;
	unsigned char CK_A = 0 ;
	unsigned char CK_B = 0 ;
	union intbb TempBB ;
	
#if(USE_VARIABLE_HILSIM_CHANNELS != 1)
	for (i=1; i<=NUM_OUTPUTS; i++)
	{
		TempBB.BB = udb_pwOut[i] ;
		SIMservoOutputs[2*i] = TempBB._.B1 ;
		SIMservoOutputs[(2*i)+1] = TempBB._.B0 ;
	}

	for (i=2; i<HILSIM_NUM_SERVOS*2+2; i++)
	{
		CK_A += SIMservoOutputs[i] ;
		CK_B += CK_A ;
	}
	SIMservoOutputs[i] = CK_A ;
	SIMservoOutputs[i+1] = CK_B ;
	
	// Send HILSIM outputs
	gpsoutbin(HILSIM_NUM_SERVOS*2+4, SIMservoOutputs) ;	

#else
	for (i=1; i<=NUM_OUTPUTS; i++)
	{
		TempBB.BB = udb_pwOut[i] ;
		SIMservoOutputs[(2*i)+1] = TempBB._.B1 ;
		SIMservoOutputs[(2*i)+2] = TempBB._.B0 ;
	}

	SIMservoOutputs[2] = NUM_OUTPUTS;

	// Calcualte checksum
	for (i=3; i<(NUM_OUTPUTS*2)+3; i++)
	{
		CK_A += SIMservoOutputs[i] ;
		CK_B += CK_A ;
	}
	SIMservoOutputs[i] = CK_A ;
	SIMservoOutputs[i+1] = CK_B ;
	
	// Send HILSIM outputs
	gpsoutbin((HILSIM_NUM_SERVOS*2)+5, SIMservoOutputs) ;	

#endif	//USE_VARIABLE_HILSIM_CHANNELS
	
#endif // ( HILSIM == 1 )
	
	return ;
}

void HILSIM_commit_bodyrate_data( void )
{
#if ( HILSIM == 1 )
	u_dot_sim = u_dot_sim_ ;
	v_dot_sim = v_dot_sim_ ;
	w_dot_sim = w_dot_sim_ ;
	p_sim = p_sim_ ;
	q_sim = q_sim_ ;
	r_sim = r_sim_ ;
#endif	
	return ;
}
