#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
MKDIR=mkdir -p
RM=rm -f 
CP=cp 
# Macros
CND_CONF=default

ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MatrixPilot_Car.X.${IMAGE_TYPE}.elf
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MatrixPilot_Car.X.${IMAGE_TYPE}.elf
endif
# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}
# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1018708451/traps_udb_asm.o ${OBJECTDIR}/_ext/682965384/cameraCntrl.o ${OBJECTDIR}/_ext/1018724808/deadReckoning.o ${OBJECTDIR}/_ext/1018708451/osd.o ${OBJECTDIR}/_ext/682965384/navigate.o ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o ${OBJECTDIR}/_ext/1018708451/magneto_udb.o ${OBJECTDIR}/_ext/682965384/servoMix.o ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o ${OBJECTDIR}/_ext/682965384/mp_osd.o ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o ${OBJECTDIR}/_ext/1018724808/estYawDrift.o ${OBJECTDIR}/_ext/682965384/flightplan-logo.o ${OBJECTDIR}/_ext/682965384/behavior.o ${OBJECTDIR}/_ext/1018724808/libDCM.o ${OBJECTDIR}/_ext/682965384/telemetry.o ${OBJECTDIR}/_ext/682965384/yawCntrl.o ${OBJECTDIR}/_ext/1018724808/estWind.o ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o ${OBJECTDIR}/_ext/1018708451/background.o ${OBJECTDIR}/_ext/682965384/servoPrepare.o ${OBJECTDIR}/_ext/682965384/states.o ${OBJECTDIR}/_ext/682965384/rollCntrl.o ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o ${OBJECTDIR}/_ext/682965384/pitchCntrl.o ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o ${OBJECTDIR}/_ext/1018708451/servoOut.o ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o ${OBJECTDIR}/_ext/1018724808/rmat.o ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o ${OBJECTDIR}/_ext/682965384/main.o ${OBJECTDIR}/_ext/1018708451/libUDB.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

OS_ORIGINAL="Darwin"
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC=/Applications/microchip/mplabc30/v3.24/bin/pic30-gcc
# MP_BC is not defined
MP_AS=/Applications/microchip/mplabc30/v3.24/bin/pic30-as
MP_LD=/Applications/microchip/mplabc30/v3.24/bin/pic30-ld
MP_AR=/Applications/microchip/mplabc30/v3.24/bin/pic30-ar
# MP_BC is not defined
MP_CC_DIR=/Applications/microchip/mplabc30/v3.24/bin
# MP_BC_DIR is not defined
MP_AS_DIR=/Applications/microchip/mplabc30/v3.24/bin
MP_LD_DIR=/Applications/microchip/mplabc30/v3.24/bin
MP_AR_DIR=/Applications/microchip/mplabc30/v3.24/bin
# MP_BC_DIR is not defined
.build-conf: ${BUILD_SUBPROJECTS}
ifneq ($(OS_CURRENT),$(OS_ORIGINAL))
	@echo "***** WARNING: This make file contains OS dependent code. The OS this makefile is being run is different from the OS it was created in."
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MatrixPilot_Car.X.${IMAGE_TYPE}.elf

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
.PHONY: ${OBJECTDIR}/_ext/1018708451/traps_udb_asm.o
${OBJECTDIR}/_ext/1018708451/traps_udb_asm.o: ../libUDB/traps_udb_asm.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=30F4011  -o ${OBJECTDIR}/_ext/1018708451/traps_udb_asm.o ../libUDB/traps_udb_asm.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,-I"../MatrixPilot"
else
.PHONY: ${OBJECTDIR}/_ext/1018708451/traps_udb_asm.o
${OBJECTDIR}/_ext/1018708451/traps_udb_asm.o: ../libUDB/traps_udb_asm.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${MP_CC}  -omf=elf -c -mcpu=30F4011  -o ${OBJECTDIR}/_ext/1018708451/traps_udb_asm.o ../libUDB/traps_udb_asm.s  -Wa,--defsym=__MPLAB_BUILD=1,-I"../MatrixPilot"
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/682965384/cameraCntrl.o: ../MatrixPilot/cameraCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/cameraCntrl.o ../MatrixPilot/cameraCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d > ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d > ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/deadReckoning.o: ../libDCM/deadReckoning.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d -o ${OBJECTDIR}/_ext/1018724808/deadReckoning.o ../libDCM/deadReckoning.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d > ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d > ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/osd.o: ../libUDB/osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/osd.o.d -o ${OBJECTDIR}/_ext/1018708451/osd.o ../libUDB/osd.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/osd.o.d > ${OBJECTDIR}/_ext/1018708451/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/osd.o.tmp ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/osd.o.d > ${OBJECTDIR}/_ext/1018708451/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/osd.o.tmp ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/navigate.o: ../MatrixPilot/navigate.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/navigate.o.d -o ${OBJECTDIR}/_ext/682965384/navigate.o ../MatrixPilot/navigate.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/navigate.o.d > ${OBJECTDIR}/_ext/682965384/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/navigate.o.tmp ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/navigate.o.d > ${OBJECTDIR}/_ext/682965384/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/navigate.o.tmp ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/altitudeCntrl.o: ../MatrixPilot/altitudeCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o ../MatrixPilot/altitudeCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/magneto_udb.o: ../libUDB/magneto_udb.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d -o ${OBJECTDIR}/_ext/1018708451/magneto_udb.o ../libUDB/magneto_udb.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d > ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d > ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/servoMix.o: ../MatrixPilot/servoMix.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/servoMix.o.d -o ${OBJECTDIR}/_ext/682965384/servoMix.o ../MatrixPilot/servoMix.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/servoMix.o.d > ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/servoMix.o.d > ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/radioIn_udb.o: ../libUDB/radioIn_udb.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d -o ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o ../libUDB/radioIn_udb.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d > ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d > ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/mp_osd.o: ../MatrixPilot/mp_osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/mp_osd.o.d -o ${OBJECTDIR}/_ext/682965384/mp_osd.o ../MatrixPilot/mp_osd.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/mp_osd.o.d > ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/mp_osd.o.d > ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o: ../MatrixPilot/flightplan-waypoints.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d -o ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o ../MatrixPilot/flightplan-waypoints.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o: ../libUDB/analog2digital_udb.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d -o ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o ../libUDB/analog2digital_udb.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d > ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d > ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/estYawDrift.o: ../libDCM/estYawDrift.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d -o ${OBJECTDIR}/_ext/1018724808/estYawDrift.o ../libDCM/estYawDrift.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d > ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d > ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/flightplan-logo.o: ../MatrixPilot/flightplan-logo.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d -o ${OBJECTDIR}/_ext/682965384/flightplan-logo.o ../MatrixPilot/flightplan-logo.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d > ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d > ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/behavior.o: ../MatrixPilot/behavior.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/behavior.o.d -o ${OBJECTDIR}/_ext/682965384/behavior.o ../MatrixPilot/behavior.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/behavior.o.d > ${OBJECTDIR}/_ext/682965384/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/behavior.o.tmp ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/behavior.o.d > ${OBJECTDIR}/_ext/682965384/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/behavior.o.tmp ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/libDCM.o: ../libDCM/libDCM.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/libDCM.o.d -o ${OBJECTDIR}/_ext/1018724808/libDCM.o ../libDCM/libDCM.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/libDCM.o.d > ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/libDCM.o.d > ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/telemetry.o: ../MatrixPilot/telemetry.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/telemetry.o.d -o ${OBJECTDIR}/_ext/682965384/telemetry.o ../MatrixPilot/telemetry.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/telemetry.o.d > ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/telemetry.o.d > ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/yawCntrl.o: ../MatrixPilot/yawCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/yawCntrl.o ../MatrixPilot/yawCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d > ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d > ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/estWind.o: ../libDCM/estWind.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/estWind.o.d -o ${OBJECTDIR}/_ext/1018724808/estWind.o ../libDCM/estWind.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/estWind.o.d > ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/estWind.o.d > ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o: ../libDCM/gpsParseUBX.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d -o ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o ../libDCM/gpsParseUBX.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/background.o: ../libUDB/background.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/background.o.d -o ${OBJECTDIR}/_ext/1018708451/background.o ../libUDB/background.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/background.o.d > ${OBJECTDIR}/_ext/1018708451/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/background.o.tmp ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/background.o.d > ${OBJECTDIR}/_ext/1018708451/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/background.o.tmp ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/servoPrepare.o: ../MatrixPilot/servoPrepare.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d -o ${OBJECTDIR}/_ext/682965384/servoPrepare.o ../MatrixPilot/servoPrepare.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d > ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d > ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/states.o: ../MatrixPilot/states.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/states.o.d -o ${OBJECTDIR}/_ext/682965384/states.o ../MatrixPilot/states.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/states.o.d > ${OBJECTDIR}/_ext/682965384/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/states.o.tmp ${OBJECTDIR}/_ext/682965384/states.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/states.o.d > ${OBJECTDIR}/_ext/682965384/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/states.o.tmp ${OBJECTDIR}/_ext/682965384/states.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/rollCntrl.o: ../MatrixPilot/rollCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/rollCntrl.o ../MatrixPilot/rollCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d > ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d > ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/mathlibNAV.o: ../libDCM/mathlibNAV.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d -o ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o ../libDCM/mathlibNAV.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/pitchCntrl.o: ../MatrixPilot/pitchCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/pitchCntrl.o ../MatrixPilot/pitchCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d > ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d > ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/serialIO_udb.o: ../libUDB/serialIO_udb.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d -o ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o ../libUDB/serialIO_udb.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d > ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d > ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/servoOut.o: ../libUDB/servoOut.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/servoOut.o.d -o ${OBJECTDIR}/_ext/1018708451/servoOut.o ../libUDB/servoOut.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/servoOut.o.d > ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/servoOut.o.d > ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o: ../libDCM/gpsParseSTD.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d -o ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o ../libDCM/gpsParseSTD.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/rmat.o: ../libDCM/rmat.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/rmat.o.d -o ${OBJECTDIR}/_ext/1018724808/rmat.o ../libDCM/rmat.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/rmat.o.d > ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/rmat.o.d > ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o: ../libDCM/gpsParseCommon.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d -o ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o ../libDCM/gpsParseCommon.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/main.o: ../MatrixPilot/main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/main.o.d -o ${OBJECTDIR}/_ext/682965384/main.o ../MatrixPilot/main.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/main.o.d > ${OBJECTDIR}/_ext/682965384/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/main.o.tmp ${OBJECTDIR}/_ext/682965384/main.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/main.o.d > ${OBJECTDIR}/_ext/682965384/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/main.o.tmp ${OBJECTDIR}/_ext/682965384/main.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/libUDB.o: ../libUDB/libUDB.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/libUDB.o.d -o ${OBJECTDIR}/_ext/1018708451/libUDB.o ../libUDB/libUDB.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/libUDB.o.d > ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/libUDB.o.d > ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp}
endif
else
${OBJECTDIR}/_ext/682965384/cameraCntrl.o: ../MatrixPilot/cameraCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/cameraCntrl.o ../MatrixPilot/cameraCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d > ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d > ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/cameraCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/deadReckoning.o: ../libDCM/deadReckoning.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d -o ${OBJECTDIR}/_ext/1018724808/deadReckoning.o ../libDCM/deadReckoning.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d > ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d > ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/deadReckoning.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/osd.o: ../libUDB/osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/osd.o.d -o ${OBJECTDIR}/_ext/1018708451/osd.o ../libUDB/osd.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/osd.o.d > ${OBJECTDIR}/_ext/1018708451/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/osd.o.tmp ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/osd.o.d > ${OBJECTDIR}/_ext/1018708451/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/osd.o.tmp ${OBJECTDIR}/_ext/1018708451/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/osd.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/navigate.o: ../MatrixPilot/navigate.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/navigate.o.d -o ${OBJECTDIR}/_ext/682965384/navigate.o ../MatrixPilot/navigate.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/navigate.o.d > ${OBJECTDIR}/_ext/682965384/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/navigate.o.tmp ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/navigate.o.d > ${OBJECTDIR}/_ext/682965384/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/navigate.o.tmp ${OBJECTDIR}/_ext/682965384/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/navigate.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/altitudeCntrl.o: ../MatrixPilot/altitudeCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o ../MatrixPilot/altitudeCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/altitudeCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/magneto_udb.o: ../libUDB/magneto_udb.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d -o ${OBJECTDIR}/_ext/1018708451/magneto_udb.o ../libUDB/magneto_udb.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d > ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d > ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/magneto_udb.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/servoMix.o: ../MatrixPilot/servoMix.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/servoMix.o.d -o ${OBJECTDIR}/_ext/682965384/servoMix.o ../MatrixPilot/servoMix.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/servoMix.o.d > ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/servoMix.o.d > ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp ${OBJECTDIR}/_ext/682965384/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/servoMix.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/radioIn_udb.o: ../libUDB/radioIn_udb.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d -o ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o ../libUDB/radioIn_udb.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d > ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d > ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/radioIn_udb.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/mp_osd.o: ../MatrixPilot/mp_osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/mp_osd.o.d -o ${OBJECTDIR}/_ext/682965384/mp_osd.o ../MatrixPilot/mp_osd.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/mp_osd.o.d > ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/mp_osd.o.d > ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp ${OBJECTDIR}/_ext/682965384/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/mp_osd.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o: ../MatrixPilot/flightplan-waypoints.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d -o ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o ../MatrixPilot/flightplan-waypoints.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-waypoints.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o: ../libUDB/analog2digital_udb.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d -o ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o ../libUDB/analog2digital_udb.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d > ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d > ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/analog2digital_udb.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/estYawDrift.o: ../libDCM/estYawDrift.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d -o ${OBJECTDIR}/_ext/1018724808/estYawDrift.o ../libDCM/estYawDrift.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d > ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d > ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/estYawDrift.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/flightplan-logo.o: ../MatrixPilot/flightplan-logo.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d -o ${OBJECTDIR}/_ext/682965384/flightplan-logo.o ../MatrixPilot/flightplan-logo.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d > ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d > ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/flightplan-logo.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/behavior.o: ../MatrixPilot/behavior.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/behavior.o.d -o ${OBJECTDIR}/_ext/682965384/behavior.o ../MatrixPilot/behavior.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/behavior.o.d > ${OBJECTDIR}/_ext/682965384/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/behavior.o.tmp ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/behavior.o.d > ${OBJECTDIR}/_ext/682965384/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/behavior.o.tmp ${OBJECTDIR}/_ext/682965384/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/behavior.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/libDCM.o: ../libDCM/libDCM.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/libDCM.o.d -o ${OBJECTDIR}/_ext/1018724808/libDCM.o ../libDCM/libDCM.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/libDCM.o.d > ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/libDCM.o.d > ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp ${OBJECTDIR}/_ext/1018724808/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/libDCM.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/telemetry.o: ../MatrixPilot/telemetry.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/telemetry.o.d -o ${OBJECTDIR}/_ext/682965384/telemetry.o ../MatrixPilot/telemetry.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/telemetry.o.d > ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/telemetry.o.d > ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp ${OBJECTDIR}/_ext/682965384/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/telemetry.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/yawCntrl.o: ../MatrixPilot/yawCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/yawCntrl.o ../MatrixPilot/yawCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d > ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d > ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/yawCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/estWind.o: ../libDCM/estWind.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/estWind.o.d -o ${OBJECTDIR}/_ext/1018724808/estWind.o ../libDCM/estWind.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/estWind.o.d > ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/estWind.o.d > ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp ${OBJECTDIR}/_ext/1018724808/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/estWind.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o: ../libDCM/gpsParseUBX.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d -o ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o ../libDCM/gpsParseUBX.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseUBX.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/background.o: ../libUDB/background.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/background.o.d -o ${OBJECTDIR}/_ext/1018708451/background.o ../libUDB/background.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/background.o.d > ${OBJECTDIR}/_ext/1018708451/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/background.o.tmp ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/background.o.d > ${OBJECTDIR}/_ext/1018708451/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/background.o.tmp ${OBJECTDIR}/_ext/1018708451/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/background.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/servoPrepare.o: ../MatrixPilot/servoPrepare.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d -o ${OBJECTDIR}/_ext/682965384/servoPrepare.o ../MatrixPilot/servoPrepare.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d > ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d > ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp ${OBJECTDIR}/_ext/682965384/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/servoPrepare.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/states.o: ../MatrixPilot/states.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/states.o.d -o ${OBJECTDIR}/_ext/682965384/states.o ../MatrixPilot/states.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/states.o.d > ${OBJECTDIR}/_ext/682965384/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/states.o.tmp ${OBJECTDIR}/_ext/682965384/states.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/states.o.d > ${OBJECTDIR}/_ext/682965384/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/states.o.tmp ${OBJECTDIR}/_ext/682965384/states.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/states.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/rollCntrl.o: ../MatrixPilot/rollCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/rollCntrl.o ../MatrixPilot/rollCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d > ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d > ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/rollCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/mathlibNAV.o: ../libDCM/mathlibNAV.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d -o ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o ../libDCM/mathlibNAV.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/mathlibNAV.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/pitchCntrl.o: ../MatrixPilot/pitchCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d -o ${OBJECTDIR}/_ext/682965384/pitchCntrl.o ../MatrixPilot/pitchCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d > ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d > ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/pitchCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/serialIO_udb.o: ../libUDB/serialIO_udb.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d -o ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o ../libUDB/serialIO_udb.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d > ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d > ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/serialIO_udb.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/servoOut.o: ../libUDB/servoOut.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/servoOut.o.d -o ${OBJECTDIR}/_ext/1018708451/servoOut.o ../libUDB/servoOut.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/servoOut.o.d > ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/servoOut.o.d > ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp ${OBJECTDIR}/_ext/1018708451/servoOut.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/servoOut.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o: ../libDCM/gpsParseSTD.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d -o ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o ../libDCM/gpsParseSTD.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseSTD.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/rmat.o: ../libDCM/rmat.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/rmat.o.d -o ${OBJECTDIR}/_ext/1018724808/rmat.o ../libDCM/rmat.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/rmat.o.d > ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/rmat.o.d > ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp ${OBJECTDIR}/_ext/1018724808/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/rmat.o.tmp}
endif
${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o: ../libDCM/gpsParseCommon.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018724808 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d -o ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o ../libDCM/gpsParseCommon.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1018724808/gpsParseCommon.o.tmp}
endif
${OBJECTDIR}/_ext/682965384/main.o: ../MatrixPilot/main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/682965384 
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/682965384/main.o.d -o ${OBJECTDIR}/_ext/682965384/main.o ../MatrixPilot/main.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/682965384/main.o.d > ${OBJECTDIR}/_ext/682965384/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/main.o.tmp ${OBJECTDIR}/_ext/682965384/main.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/682965384/main.o.d > ${OBJECTDIR}/_ext/682965384/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.d 
	${CP} ${OBJECTDIR}/_ext/682965384/main.o.tmp ${OBJECTDIR}/_ext/682965384/main.o.d 
	${RM} ${OBJECTDIR}/_ext/682965384/main.o.tmp}
endif
${OBJECTDIR}/_ext/1018708451/libUDB.o: ../libUDB/libUDB.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1018708451 
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=30F4011 -Wall -I"../MatrixPilot" -I"../libUDB" -I"../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1018708451/libUDB.o.d -o ${OBJECTDIR}/_ext/1018708451/libUDB.o ../libUDB/libUDB.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1018708451/libUDB.o.d > ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1018708451/libUDB.o.d > ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp ${OBJECTDIR}/_ext/1018708451/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1018708451/libUDB.o.tmp}
endif
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MatrixPilot_Car.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -mcpu=30F4011  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/MatrixPilot_Car.X.${IMAGE_TYPE}.elf ${OBJECTFILES}   /Applications/microchip/mplabc30/v3.24/lib/libdsp-elf.a    -Wl,--defsym=__MPLAB_BUILD=1,-L"../MatrixPilot/C:/Program Files/Microchip/MPLAB C30/lib",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem,--report-mem,-Tp30f4011.gld,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/MatrixPilot_Car.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -mcpu=30F4011  -o dist/${CND_CONF}/${IMAGE_TYPE}/MatrixPilot_Car.X.${IMAGE_TYPE}.elf ${OBJECTFILES}   /Applications/microchip/mplabc30/v3.24/lib/libdsp-elf.a    -Wl,--defsym=__MPLAB_BUILD=1,-L"../MatrixPilot/C:/Program Files/Microchip/MPLAB C30/lib",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem,--report-mem,-Tp30f4011.gld
	${MP_CC_DIR}/pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MatrixPilot_Car.X.${IMAGE_TYPE}.elf -omf=elf
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
