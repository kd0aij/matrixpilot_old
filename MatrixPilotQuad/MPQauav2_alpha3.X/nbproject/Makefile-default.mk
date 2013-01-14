#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPQauav2_alpha3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPQauav2_alpha3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1077471063/deadReckoning.o ${OBJECTDIR}/_ext/1077471063/estWind.o ${OBJECTDIR}/_ext/1077471063/estYawDrift.o ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o ${OBJECTDIR}/_ext/1077471063/libDCM.o ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o ${OBJECTDIR}/_ext/1077471063/rmat.o ${OBJECTDIR}/_ext/1077454706/background.o ${OBJECTDIR}/_ext/1077454706/libUDB.o ${OBJECTDIR}/_ext/1077454706/servoOut.o ${OBJECTDIR}/_ext/1077454706/filters.o ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o ${OBJECTDIR}/_ext/1077454706/mpu6000.o ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o ${OBJECTDIR}/_ext/1077454706/spiUtils.o ${OBJECTDIR}/_ext/1077454706/events.o ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o ${OBJECTDIR}/main.o ${OBJECTDIR}/motorCntrl.o ${OBJECTDIR}/telemetry.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d ${OBJECTDIR}/_ext/1077471063/estWind.o.d ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.d ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d ${OBJECTDIR}/_ext/1077471063/libDCM.o.d ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d ${OBJECTDIR}/_ext/1077471063/rmat.o.d ${OBJECTDIR}/_ext/1077454706/background.o.d ${OBJECTDIR}/_ext/1077454706/libUDB.o.d ${OBJECTDIR}/_ext/1077454706/servoOut.o.d ${OBJECTDIR}/_ext/1077454706/filters.o.d ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.d ${OBJECTDIR}/_ext/1077454706/mpu6000.o.d ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.d ${OBJECTDIR}/_ext/1077454706/spiUtils.o.d ${OBJECTDIR}/_ext/1077454706/events.o.d ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/motorCntrl.o.d ${OBJECTDIR}/telemetry.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1077471063/deadReckoning.o ${OBJECTDIR}/_ext/1077471063/estWind.o ${OBJECTDIR}/_ext/1077471063/estYawDrift.o ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o ${OBJECTDIR}/_ext/1077471063/libDCM.o ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o ${OBJECTDIR}/_ext/1077471063/rmat.o ${OBJECTDIR}/_ext/1077454706/background.o ${OBJECTDIR}/_ext/1077454706/libUDB.o ${OBJECTDIR}/_ext/1077454706/servoOut.o ${OBJECTDIR}/_ext/1077454706/filters.o ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o ${OBJECTDIR}/_ext/1077454706/mpu6000.o ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o ${OBJECTDIR}/_ext/1077454706/spiUtils.o ${OBJECTDIR}/_ext/1077454706/events.o ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o ${OBJECTDIR}/main.o ${OBJECTDIR}/motorCntrl.o ${OBJECTDIR}/telemetry.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPQauav2_alpha3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP708A
MP_LINKER_FILE_OPTION=,-Tp33FJ128GP708A.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1077471063/deadReckoning.o: ../../libDCM/deadReckoning.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.ok ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d" -o ${OBJECTDIR}/_ext/1077471063/deadReckoning.o ../../libDCM/deadReckoning.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/estWind.o: ../../libDCM/estWind.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.ok ${OBJECTDIR}/_ext/1077471063/estWind.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/estWind.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/estWind.o.d" -o ${OBJECTDIR}/_ext/1077471063/estWind.o ../../libDCM/estWind.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/estYawDrift.o: ../../libDCM/estYawDrift.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.ok ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d" -o ${OBJECTDIR}/_ext/1077471063/estYawDrift.o ../../libDCM/estYawDrift.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o: ../../libDCM/gpsParseCommon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.ok ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d" -o ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o ../../libDCM/gpsParseCommon.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o: ../../libDCM/gpsParseMTEK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.ok ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.d" -o ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o ../../libDCM/gpsParseMTEK.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o: ../../libDCM/gpsParseSTD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.ok ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d" -o ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o ../../libDCM/gpsParseSTD.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o: ../../libDCM/gpsParseUBX.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.ok ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d" -o ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o ../../libDCM/gpsParseUBX.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/libDCM.o: ../../libDCM/libDCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.ok ${OBJECTDIR}/_ext/1077471063/libDCM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/libDCM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/libDCM.o.d" -o ${OBJECTDIR}/_ext/1077471063/libDCM.o ../../libDCM/libDCM.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/mathlibNAV.o: ../../libDCM/mathlibNAV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.ok ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d" -o ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o ../../libDCM/mathlibNAV.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/rmat.o: ../../libDCM/rmat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.ok ${OBJECTDIR}/_ext/1077471063/rmat.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/rmat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/rmat.o.d" -o ${OBJECTDIR}/_ext/1077471063/rmat.o ../../libDCM/rmat.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/background.o: ../../libUDB/background.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/background.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/background.o.ok ${OBJECTDIR}/_ext/1077454706/background.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/background.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/background.o.d" -o ${OBJECTDIR}/_ext/1077454706/background.o ../../libUDB/background.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/libUDB.o: ../../libUDB/libUDB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.ok ${OBJECTDIR}/_ext/1077454706/libUDB.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/libUDB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/libUDB.o.d" -o ${OBJECTDIR}/_ext/1077454706/libUDB.o ../../libUDB/libUDB.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/servoOut.o: ../../libUDB/servoOut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/servoOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/servoOut.o.ok ${OBJECTDIR}/_ext/1077454706/servoOut.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/servoOut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/servoOut.o.d" -o ${OBJECTDIR}/_ext/1077454706/servoOut.o ../../libUDB/servoOut.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/filters.o: ../../libUDB/filters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/filters.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/filters.o.ok ${OBJECTDIR}/_ext/1077454706/filters.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/filters.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/filters.o.d" -o ${OBJECTDIR}/_ext/1077454706/filters.o ../../libUDB/filters.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/serialIO_auav.o: ../../libUDB/serialIO_auav.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.ok ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.d" -o ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o ../../libUDB/serialIO_auav.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/mpu6000.o: ../../libUDB/mpu6000.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/mpu6000.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/mpu6000.o.ok ${OBJECTDIR}/_ext/1077454706/mpu6000.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/mpu6000.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/mpu6000.o.d" -o ${OBJECTDIR}/_ext/1077454706/mpu6000.o ../../libUDB/mpu6000.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o: ../../libUDB/analog2digital_auav2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.ok ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.d" -o ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o ../../libUDB/analog2digital_auav2.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/spiUtils.o: ../../libUDB/spiUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/spiUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/spiUtils.o.ok ${OBJECTDIR}/_ext/1077454706/spiUtils.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/spiUtils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/spiUtils.o.d" -o ${OBJECTDIR}/_ext/1077454706/spiUtils.o ../../libUDB/spiUtils.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/events.o: ../../libUDB/events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/events.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/events.o.ok ${OBJECTDIR}/_ext/1077454706/events.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/events.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/events.o.d" -o ${OBJECTDIR}/_ext/1077454706/events.o ../../libUDB/events.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o: ../../libUDB/eeprom_auav2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.ok ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.d" -o ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o ../../libUDB/eeprom_auav2.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/motorCntrl.o: motorCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/motorCntrl.o.d 
	@${RM} ${OBJECTDIR}/motorCntrl.o.ok ${OBJECTDIR}/motorCntrl.o.err 
	@${FIXDEPS} "${OBJECTDIR}/motorCntrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/motorCntrl.o.d" -o ${OBJECTDIR}/motorCntrl.o motorCntrl.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/telemetry.o: telemetry.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/telemetry.o.d 
	@${RM} ${OBJECTDIR}/telemetry.o.ok ${OBJECTDIR}/telemetry.o.err 
	@${FIXDEPS} "${OBJECTDIR}/telemetry.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/telemetry.o.d" -o ${OBJECTDIR}/telemetry.o telemetry.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
else
${OBJECTDIR}/_ext/1077471063/deadReckoning.o: ../../libDCM/deadReckoning.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.ok ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d" -o ${OBJECTDIR}/_ext/1077471063/deadReckoning.o ../../libDCM/deadReckoning.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/estWind.o: ../../libDCM/estWind.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.ok ${OBJECTDIR}/_ext/1077471063/estWind.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/estWind.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/estWind.o.d" -o ${OBJECTDIR}/_ext/1077471063/estWind.o ../../libDCM/estWind.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/estYawDrift.o: ../../libDCM/estYawDrift.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.ok ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d" -o ${OBJECTDIR}/_ext/1077471063/estYawDrift.o ../../libDCM/estYawDrift.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o: ../../libDCM/gpsParseCommon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.ok ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d" -o ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o ../../libDCM/gpsParseCommon.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o: ../../libDCM/gpsParseMTEK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.ok ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o.d" -o ${OBJECTDIR}/_ext/1077471063/gpsParseMTEK.o ../../libDCM/gpsParseMTEK.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o: ../../libDCM/gpsParseSTD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.ok ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d" -o ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o ../../libDCM/gpsParseSTD.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o: ../../libDCM/gpsParseUBX.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.ok ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d" -o ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o ../../libDCM/gpsParseUBX.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/libDCM.o: ../../libDCM/libDCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.ok ${OBJECTDIR}/_ext/1077471063/libDCM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/libDCM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/libDCM.o.d" -o ${OBJECTDIR}/_ext/1077471063/libDCM.o ../../libDCM/libDCM.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/mathlibNAV.o: ../../libDCM/mathlibNAV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.ok ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d" -o ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o ../../libDCM/mathlibNAV.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077471063/rmat.o: ../../libDCM/rmat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	@${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.ok ${OBJECTDIR}/_ext/1077471063/rmat.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077471063/rmat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077471063/rmat.o.d" -o ${OBJECTDIR}/_ext/1077471063/rmat.o ../../libDCM/rmat.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/background.o: ../../libUDB/background.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/background.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/background.o.ok ${OBJECTDIR}/_ext/1077454706/background.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/background.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/background.o.d" -o ${OBJECTDIR}/_ext/1077454706/background.o ../../libUDB/background.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/libUDB.o: ../../libUDB/libUDB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.ok ${OBJECTDIR}/_ext/1077454706/libUDB.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/libUDB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/libUDB.o.d" -o ${OBJECTDIR}/_ext/1077454706/libUDB.o ../../libUDB/libUDB.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/servoOut.o: ../../libUDB/servoOut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/servoOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/servoOut.o.ok ${OBJECTDIR}/_ext/1077454706/servoOut.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/servoOut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/servoOut.o.d" -o ${OBJECTDIR}/_ext/1077454706/servoOut.o ../../libUDB/servoOut.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/filters.o: ../../libUDB/filters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/filters.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/filters.o.ok ${OBJECTDIR}/_ext/1077454706/filters.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/filters.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/filters.o.d" -o ${OBJECTDIR}/_ext/1077454706/filters.o ../../libUDB/filters.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/serialIO_auav.o: ../../libUDB/serialIO_auav.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.ok ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/serialIO_auav.o.d" -o ${OBJECTDIR}/_ext/1077454706/serialIO_auav.o ../../libUDB/serialIO_auav.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/mpu6000.o: ../../libUDB/mpu6000.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/mpu6000.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/mpu6000.o.ok ${OBJECTDIR}/_ext/1077454706/mpu6000.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/mpu6000.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/mpu6000.o.d" -o ${OBJECTDIR}/_ext/1077454706/mpu6000.o ../../libUDB/mpu6000.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o: ../../libUDB/analog2digital_auav2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.ok ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o.d" -o ${OBJECTDIR}/_ext/1077454706/analog2digital_auav2.o ../../libUDB/analog2digital_auav2.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/spiUtils.o: ../../libUDB/spiUtils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/spiUtils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/spiUtils.o.ok ${OBJECTDIR}/_ext/1077454706/spiUtils.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/spiUtils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/spiUtils.o.d" -o ${OBJECTDIR}/_ext/1077454706/spiUtils.o ../../libUDB/spiUtils.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/events.o: ../../libUDB/events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/events.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/events.o.ok ${OBJECTDIR}/_ext/1077454706/events.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/events.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/events.o.d" -o ${OBJECTDIR}/_ext/1077454706/events.o ../../libUDB/events.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o: ../../libUDB/eeprom_auav2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	@${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.ok ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o.d" -o ${OBJECTDIR}/_ext/1077454706/eeprom_auav2.o ../../libUDB/eeprom_auav2.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/motorCntrl.o: motorCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/motorCntrl.o.d 
	@${RM} ${OBJECTDIR}/motorCntrl.o.ok ${OBJECTDIR}/motorCntrl.o.err 
	@${FIXDEPS} "${OBJECTDIR}/motorCntrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/motorCntrl.o.d" -o ${OBJECTDIR}/motorCntrl.o motorCntrl.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
${OBJECTDIR}/telemetry.o: telemetry.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/telemetry.o.d 
	@${RM} ${OBJECTDIR}/telemetry.o.ok ${OBJECTDIR}/telemetry.o.err 
	@${FIXDEPS} "${OBJECTDIR}/telemetry.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../MPQauav2_alpha3.X" -mlarge-code -mlarge-data -MMD -MF "${OBJECTDIR}/telemetry.o.d" -o ${OBJECTDIR}/telemetry.o telemetry.c    -legacy-libc --save-temps  -D_ADDED_C_LIB
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPQauav2_alpha3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/MPQauav2_alpha3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -legacy-libc -Wl,--defsym=__MPLAB_BUILD=1,--heap=0,-l"dsp",-l"q",-L"../C:/Program Files/Microchip/MPLAB C30/lib",-Map="${DISTDIR}/MatrixPilotQuad-udb4.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPQauav2_alpha3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPQauav2_alpha3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -legacy-libc -Wl,--defsym=__MPLAB_BUILD=1,--heap=0,-l"dsp",-l"q",-L"../C:/Program Files/Microchip/MPLAB C30/lib",-Map="${DISTDIR}/MatrixPilotQuad-udb4.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}/pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MPQauav2_alpha3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
