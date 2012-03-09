#!/usr/bin/env python

'''
Use pyparam to generate MatrixPilot mavlink parameter and nv memory tables from XML database description

Copyright Matthew Coleman 2012
Released under GNU GPL version 3 or later
'''

import os, sys, glob, re

import SubParameterDatabase as ParameterDB

# allow import from the MAVlink/pymavlink directory, where mavutil.py is
#sys.path.insert(0, os.path.join(os.path.dirname(os.path.realpath(__file__)), '../MAVLink/pymavlink'))


class ParameterTableGenerator():
    def __init__( self ):
        self.filePath = ""
        
    def openXMLDatabase( self ):
        self.ParamDBMain = ParameterDB.parse("ParameterDatabase.xml")


    def writeUDBTypesHeader( self ):
        headerFile = open(self.filePath + "parameter_datatypes.h", "w")
        
        headerFile.write("#ifndef PARAMETER_DATATYPES_H\n")
        headerFile.write("#define PARAMETER_DATATYPES_H\n")

        headerFile.write("// pyparam generated file - DO NOT EDIT\n\n")
        
#        headerFile.write('#include "parameter_table.h"\n')
        headerFile.write('#include "../MAVlink/include/mavlink_types.h"\n\n')
        
        
        dataTypes = self.ParamDBMain.get_udbTypes().get_udbType()
    
        headerFile.write("typedef enum\n    {\n")
        
        for dataType in dataTypes:
            headerFile.write("    " + dataType.get_typeName() + ",\n");
        
        headerFile.write("    } udb_internal_type_t;\n\n")
            
        for dataType in dataTypes:
            headerFile.write("extern void " + dataType.get_sendFunction() + "( int16_t i ) ;\n")
            headerFile.write("extern void " + dataType.get_setFunction() + "(mavlink_param_union_t setting, int16_t i ) ;\n\n")
            
    
        headerFile.write("#endif    // PARAMETER_DATATYPES_H\n")
        
    def findMAVlinkParamType(self, udb_type):
        dataTypes = self.ParamDBMain.get_udbTypes().get_udbType()
        for dataType in dataTypes:
            if(dataType.get_typeName() == udb_type):
                return dataType.get_mavlinkType()
        return ""
        


    def writeParameterTable( self ):
        headerFile = open(self.filePath + "parameter_table.c", "w")
        
        headerFile.write("// pyparam generated file - DO NOT EDIT\n\n\n")
        
        headerFile.write('#include "parameter_table.h"\n')
        headerFile.write('#include "parameter_datatypes.h"\n')
        headerFile.write('#include "gain_variables.h"        // Needed for access to internal DCM value"\n\n\n')

        
        dataTypes = self.ParamDBMain.get_udbTypes().get_udbType()
        paramBlocks = self.ParamDBMain.get_parameterBlocks().get_parameterBlock()
        
        
        headerFile.write('const mavlink_parameter_parser    mavlink_parameter_parsers[] = {\n')
        
        for dataType in dataTypes:
            headerFile.write("    { &" + dataType.get_sendFunction() + ", &" + dataType.get_setFunction() + ", " + dataType.get_mavlinkType() + "},\n")
            
        headerFile.write("    };\n\n")


        headerFile.write("const mavlink_parameter mavlink_parameters_list[] = {\n ")

        for paramBlock in paramBlocks:
#            print(paramBlock.get_blockName());
            if(paramBlock.get_in_mavlink_parameters() == True):
                for parameter in paramBlock.get_parameters().get_parameter():
                    headerFile.write('    {"' + parameter.get_parameterName() + '" , {.')
                    mavlinkType = self.findMAVlinkParamType(parameter.get_udb_param_type())
                    
                    if(mavlinkType == "MAVLINK_TYPE_FLOAT"):
                        headerFile.write('param_float=')
                    if(mavlinkType == "MAVLINK_TYPE_INT32_T"):
                        headerFile.write('param_int32=')
                    if(mavlinkType == "MAVLINK_TYPE_UINT32_T"):
                        headerFile.write('param_uint32=')
    
                    headerFile.write( parameter.get_min() + '} , {.')
    
                    if(mavlinkType == "MAVLINK_TYPE_FLOAT"):
                        headerFile.write('param_float=')
                    if(mavlinkType == "MAVLINK_TYPE_INT32_T"):
                        headerFile.write('param_int32=')
                    if(mavlinkType == "MAVLINK_TYPE_UINT32_T"):
                        headerFile.write('param_uint32=')
                        
                    headerFile.write( parameter.get_max() + '} , ' + parameter.get_udb_param_type() + ', ')
                    
                    if(parameter.get_readonly() == "true"):
                        headerFile.write('PARAMETER_READONLY')
                    else:
                        headerFile.write('PARAMETER_READWRITE')
                    
                    headerFile.write(', (void*) &' + parameter.get_variable_name() + ', sizeof(' + parameter.get_variable_name() + ') },\n')
            headerFile.write('\n')
        headerFile.write("    };\n\n")

        headerFile.write("const int count_of_parameters_list = sizeof(mavlink_parameters_list) / sizeof(mavlink_parameter);\n\n\n")


             

paramGen = ParameterTableGenerator()
paramGen.openXMLDatabase()
paramGen.writeUDBTypesHeader()
paramGen.writeParameterTable()


        
        