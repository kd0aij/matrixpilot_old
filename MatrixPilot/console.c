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


#include "defines.h"
#include "../libUDB/libUDB.h"
#include "../libUDB/interrupt.h"
#include "../libDCM/estAltitude.h"
#include "../libUDB/uart.h"
#include <string.h>
#include <stdio.h>

#if (USE_CONFIGFILE == 1)
#include "config.h"
#include "redef.h"
#endif // USE_CONFIGFILE

#if (CONSOLE_UART != 0)

#define LOWORD(a) ((WORD)(a))
#define HIWORD(a) ((WORD)(((DWORD)(a) >> 16) & 0xFFFF))

void AT45D_FormatFS(void);

typedef struct tagCmds {
	int index;
	void (*fptr)(void);
	const char const * cmdstr;
} cmds_t;


int cmdlen = 0;
char cmdstr[32];
int show_cpu_load = 0;


void cmd_ver(void)
{
	printf("MatrixPilot v0.1, " __TIME__ " " __DATE__ "\r\n");
}

void cmd_format(void)
{
#if (BOARD_TYPE == AUAV3_BOARD)
	printf("formatting dataflash\r\n");
	AT45D_FormatFS();
#endif // BOARD_TYPE
}

void cmd_start(void)
{
	printf("starting.\r\n");
	show_cpu_load = 1;
}

void cmd_stop(void)
{
	printf("stopped.\r\n");
	show_cpu_load = 0;
}

void cmd_on(void)
{
	printf("on.\r\n");
	SRbits.IPL = 0; // turn on all interrupt priorities
}

void cmd_off(void)
{
	printf("off.\r\n");
	SRbits.IPL = 7; // turn off all interrupt priorities
}

void cmd_cpuload(void)
{
#if (USE_MCU_IDLE == 0)
	printf("CPU Load %u%%\r\n", udb_cpu_load());
#else
	printf("CPU Load %5.2f%%\r\n", udb_cpu_ratio()/100.0);
#endif
}

void cmd_crash(void)
{
	static int i;
	char buffer[32];

	sprintf(buffer, "overflowing stack %u.\r\n", i++);
	printf(buffer);
	cmd_crash();
}

void cmd_adc(void)
{
//	printf("ADC vcc %u, 5v %u, rssi %u\r\n", udb_vcc.value, udb_5v.value, udb_rssi.value);
}

void cmd_barom(void)
{
	printf("Barometer temp %i, pres %u, alt %u, agl %u\r\n",
	       get_barometer_temperature(),
	       (uint16_t)get_barometer_pressure(),
	       (uint16_t)get_barometer_altitude(),
	       (uint16_t)get_barometer_agl_altitude()
	      );
}

void cmd_magno(void)
{
}

void cmd_options(void)
{
#if (USE_CONFIGFILE == 1)
	printf("ROLL_STABILIZATION_AILERONS: %u\r\n", ROLL_STABILIZATION_AILERONS);
	printf("ROLL_STABILIZATION_RUDDER: %u\r\n", ROLL_STABILIZATION_RUDDER);
	printf("PITCH_STABILIZATION: %u\r\n", PITCH_STABILIZATION);
	printf("YAW_STABILIZATION_RUDDER: %u\r\n", YAW_STABILIZATION_RUDDER);
	printf("YAW_STABILIZATION_AILERON: %u\r\n", YAW_STABILIZATION_AILERON);
	printf("AILERON_NAVIGATION: %u\r\n", AILERON_NAVIGATION);
	printf("RUDDER_NAVIGATION: %u\r\n", RUDDER_NAVIGATION);
	printf("ALTITUDEHOLD_STABILIZED: %u\r\n", ALTITUDEHOLD_STABILIZED);
	printf("ALTITUDEHOLD_WAYPOINT: %u\r\n", ALTITUDEHOLD_WAYPOINT);
	printf("RACING_MODE: %u\r\n", RACING_MODE);
#endif
}

void cmd_gains(void)
{
#if (USE_CONFIGFILE == 1)
	printf("YAWKP_AILERON: %f\r\n", (double)gains.YawKPAileron);
	printf("YAWKD_AILERON: %f\r\n", (double)gains.YawKDAileron);
	printf("ROLLKP: %f\r\n", (double)gains.RollKP);
	printf("ROLLKD: %f\r\n", (double)gains.RollKD);
	printf("AILERON_BOOST: %f\r\n", (double)gains.AileronBoost);
	printf("PITCHGAIN: %f\r\n", (double)gains.Pitchgain);
	printf("PITCHKD: %f\r\n", (double)gains.PitchKD);
	printf("RUDDER_ELEV_MIX: %f\r\n", (double)gains.RudderElevMix);
	printf("ROLL_ELEV_MIX: %f\r\n", (double)gains.RollElevMix);
	printf("ELEVATOR_BOOST: %f\r\n", (double)gains.ElevatorBoost);
	printf("YAWKP_RUDDER: %f\r\n", (double)gains.YawKPRudder);
	printf("YAWKD_RUDDER: %f\r\n", (double)gains.YawKDRudder);
	printf("ROLLKP_RUDDER: %f\r\n", (double)gains.RollKPRudder);
	printf("ROLLKD_RUDDER: %f\r\n", (double)gains.RollKDRudder);
	printf("RUDDER_BOOST: %f\r\n", (double)gains.RudderBoost);
	printf("RTL_PITCH_DOWN: %f\r\n", (double)gains.RtlPitchDown);
	printf("HEIGHT_TARGET_MAX: %f\r\n", (double)gains.HeightTargetMax);
	printf("HEIGHT_TARGET_MIN: %f\r\n", (double)gains.HeightTargetMin);
	printf("ALT_HOLD_THROTTLE_MIN: %f\r\n", (double)gains.AltHoldThrottleMin);
	printf("ALT_HOLD_THROTTLE_MAX,: %f\r\n", (double)gains.AltHoldThrottleMax);
	printf("ALT_HOLD_PITCH_MIN: %f\r\n", (double)gains.AltHoldPitchMin);
	printf("ALT_HOLD_PITCH_MAX: %f\r\n", (double)gains.AltHoldPitchMax);
	printf("ALT_HOLD_PITCH_HIGH: %f\r\n", (double)gains.AltHoldPitchHigh);
#endif
}

void printbin16(int a)
{
	unsigned int i;
	for (i = 0x8000; i > 0; i >>= 1) {
		if (a & i) printf("1");
		else printf("0");
	}
}

const char *byte_to_binary(int x)
{
	static char b[9];
	int z;

	b[0] = '\0';
	for (z = 128; z > 0; z >>= 1) {
		strcat(b, ((x & z) == z) ? "1" : "0");
	}
	return b;
}

const char *word_to_binary(int x)
{
	static char b[17];
	unsigned int z;

	b[0] = '\0';
	for (z = 0x8000; z > 0; z >>= 1) {
		strcat(b, ((x & z) == z) ? "1" : "0");
	}
	return b;
}

void gentrap(void);

void cmd_trap(void)
{
	gentrap();
}

void cmd_reg(void)
{
#if (BOARD_TYPE == AUAV3_BOARD)
	printf("USB Registers:\r\n");
	printf("\tU1OTGSTAT = %s\r\n", word_to_binary(U1OTGSTAT));
	printf("\tU1OTGCON  = %s\r\n", word_to_binary(U1OTGCON));
	printf("\tU1STAT    = %s\r\n", word_to_binary(U1STAT));
	printf("\tU1CON     = %s\r\n", word_to_binary(U1CON));
	printf("\tU1CNFG1   = %s\r\n", word_to_binary(U1CNFG1));
	printf("\tU1CNFG2   = %s\r\n", word_to_binary(U1CNFG2));
	printf("\tU1OTGIR   = %s\r\n", word_to_binary(U1OTGIR));
	printf("\tU1OTGIE   = %s\r\n", word_to_binary(U1OTGIE));

	printf("IC Registers:\r\n");
	printf("\tIC1CON1 = %s %04x\r\n", word_to_binary(IC1CON1), IC1CON1);
	printf("\tIC1CON2 = %s %04x\r\n", word_to_binary(IC1CON2), IC1CON2);
	printf("\tIC2CON1 = %s %04x\r\n", word_to_binary(IC2CON1), IC2CON1);
	printf("\tIC2CON2 = %s %04x\r\n", word_to_binary(IC2CON2), IC2CON2);
#endif // BOARD_TYPE
/*
UxOTGSTAT: USB OTG STATUS REGISTER
VBUSVD: A-VBUS Valid Indicator bit
1 = The VBUS voltage is above VA_VBUS_VLD (as defined in the USB OTG Specification) on the A device
0 = The VBUS voltage is below VA_VBUS_VLD on the A device


UxOTGCON: USB ON-THE-GO CONTROL REGISTER
bit 3 VBUSON: VBUS Power-on bit(1)
1 = VBUS line is powered
0 = VBUS line is not powered

UxCNFG2: USB CONFIGURATION REGISTER 2
 */
}

#if (RECORD_FREE_STACK_SPACE == 1)
extern uint16_t maxstack;
#endif

void cmd_stack(void)
{
#if (RECORD_FREE_STACK_SPACE == 1)
	printf("maxstack %x\r\n", maxstack);
	printf("SP_start %x\r\n", SP_start());
	printf("SP_limit %x\r\n", SP_limit());
	printf("SP_current %x\r\n", SP_current());
	printf("stack usage %u\r\n", maxstack - SP_start());
#else
	printf("stack reporting disabled.\r\n");
#endif
}

void cmd_reset(void)
{
	asm("reset");
}

void cmd_help(void);

void log_close(void);

void cmd_close(void)
{
#if (USE_TELELOG == 1)
	log_close();
#endif
}

const cmds_t cmdslist[] = {
	{ 0, cmd_help,   "help" },
	{ 0, cmd_ver,    "ver" },
	{ 0, cmd_format, "format" },
	{ 0, cmd_start,  "start" },
	{ 0, cmd_stop,   "stop" },
	{ 0, cmd_on,     "on" },
	{ 0, cmd_off,    "off" },
	{ 0, cmd_stack,  "stack" },
	{ 0, cmd_reg,    "reg" },
	{ 0, cmd_adc,    "adc" },
	{ 0, cmd_barom,  "bar" },
	{ 0, cmd_cpuload,"cpu" },
	{ 0, cmd_magno,  "mag" },
	{ 0, cmd_crash,  "crash" },
	{ 0, cmd_gains,  "gains" },
	{ 0, cmd_options,"options" },
	{ 0, cmd_reset,  "reset" },
	{ 0, cmd_trap,   "trap" },
	{ 0, cmd_close,  "close" },
};

void cmd_help(void)
{
	int i;

	printf("Commands:\r\n");
	for (i = 0; i < (sizeof(cmdslist)/sizeof(cmdslist[0])); i++) {
		printf("\t%s\r\n", cmdslist[i].cmdstr);
	}
}

void command(char* cmdstr)
{
	int i;

	for (i = 0; i < (sizeof(cmdslist)/sizeof(cmdslist[0])); i++) {
		if (strcmp(cmdslist[i].cmdstr, cmdstr) == 0) {
			cmdslist[i].fptr();
		}
	}
}

void console(void)
{
	if (kbhit()) {
		char ch = getch();
		if (cmdlen < sizeof(cmdstr)) {
			cmdstr[cmdlen] = ch;
			if ((ch == '\r') || (ch == '\n')) {
				cmdstr[cmdlen] = '\0';
				cmdlen = 0;
				if (strlen(cmdstr) > 0) {
					putch('\r');
					command(cmdstr);
				}
			} else {
				putch(ch);
				cmdlen++;
			}
		} else {
			cmdlen = 0;
		}
	}
}

#endif // CONSOLE_UART
