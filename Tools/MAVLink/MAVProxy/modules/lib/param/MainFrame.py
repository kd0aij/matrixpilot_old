"""Subclass of MainFrameBase, which is generated by wxFormBuilder."""

import wx
import gui
import struct, array
import sys,os
import time
import re


import parameditSettings

# find the mavlink.py module
for d in [ 'pymavlink',
          os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', '..', '..', '..', 'MAVLink', 'pymavlink') ]:
    if os.path.exists(d):
        sys.path.insert(0, d)
        
#        if os.name == 'nt':
#            try:
#                # broken python compilation of mavlink.py on windows!
#                os.unlink(os.path.join(d, 'mavlink.pyc'))
#            except:
#                pass

import mavutil
import mavlinkv10 as mavlink

import pyparameters
import MAVlinkParameterProcesses

from callback_types import callback_messages

class callback_type(object):
# Status changes
    OFFLINE = 0
    ONLINE = 1
    READ_IN_PROGRESS = 2
    READ_COMPLETE = 4
    READ_FAIL = 6
    NV_MEM_WRITE_OK     = 50
    NV_MEM_WRITE_FAIL   = 55
    NV_MEM_READ_OK      = 60
    NV_MEM_READ_FAIL    = 65
    NV_MEM_CLEAR_OK     = 70
    NV_MEM_CLEAR_FAIL   = 75
    
#document changes
    PARAMETER_CHANGED = 100
    PARAMETERS_LOADED = 110

# actions    
    READ_ALL_PARAMS  = 200
    READ_PARAM      = 210
    WRITE_NV_AREA   = 220
    CLEAR_NV_AREA   = 230
    READ_NV_AREA    = 240
    WRITE_ALL_PARAMS = 250
    WRITE_CHANGED_PARAMS = 260

# Implementing MainFrameBase
class MainFrame( gui.MainFrameBase ):
    def __init__( self, parent ):
        gui.MainFrameBase.__init__( self, parent )

        # determine if application is a script file or frozen exe
        if hasattr(sys, 'frozen'):
            self.application_path = os.path.dirname(sys.executable)
        elif __file__:
            self.application_path = os.path.dirname(__file__)

        self.param_handler = pyparameters.parameter_handler(self.data_change_notify)
        
        self.data_change_hint = None
        self.parameter_data     = None
        
        self.callbacks = []
        
        self.m_gridParameters.DeleteRows(0, self.m_gridParameters.GetNumberRows())
        #self.m_gridParameters.AutoSizeRows()
        self.m_gridParameters.SetRowLabelSize(0)
        self.m_gridParameters.SetColLabelSize(0)
        self.m_gridParameters.SetColSize(0,100)
        self.m_gridParameters.SetColSize(1,125)
        self.m_gridParameters.SetColSize(2,60)

                                
        nv_mem = pyparameters.nv_memory()
        self.memory_areas = nv_mem.get_memory_area_list()
        self.parameter_areas = nv_mem.get_parameter_area_list()
        self.m_listBoxMemoryAreas.InsertItems(self.memory_areas, 0)

        REFRESH_TIMER_ID = 10010  # pick a number
        self.refresh_timer = wx.Timer(self, REFRESH_TIMER_ID)  # message will be sent to the panel
        wx.EVT_TIMER(self, REFRESH_TIMER_ID, self.on_refresh_timer)  # call the on_timer function

        self.refresh_timer.Start(100)  # x100 milliseconds
        
        self.section_focus = "ALL"
        self.param_focus = ""

    def m_register_callback(self, callback):
        self.callbacks.append(callback)
        
    def m_call_callbacks(self, callback_type, hint = None):
        for callback in self.callbacks:
            callback(callback_type, hint)
            
    def m_connected(self):
        return

    def m_disconnected(self):
        return            

    def on_refresh_timer(self, event):
        if(self.data_change_hint != None):
            print("Refresh timer found data change")
            if isinstance(self.data_change_hint, list):
                self.parameter_data =  self.data_change_hint
                
                self.m_listCtrlSectionList.DeleteAllItems()
                
#                // Add column
                self.m_listCtrlSectionList.InsertColumn(0, "SECTION")
                self.m_listCtrlSectionList.SetColumnWidth(0, 125)
                
                self.sections = []
                self.sections.append("ALL")
                itemcount = 0
                for param in self.parameter_data:
                    param_id = getattr(param, 'param_id', "DEFAULT")
                    section = param_id.replace('_',' ')
                    section = re.findall(r'\w+', section)
                    if section[0] not in self.sections:
                        self.sections.append(str(section[0]))

                itemcount = 0
                for section in self.sections:
                    self.m_listCtrlSectionList.InsertStringItem(itemcount, section )
                    itemcount += 1
                
                if(self.section_focus in self.sections):
                    self.m_updateParametersGrid(self.section_focus)
                else:
                    self.m_updateParametersGrid("ALL")
            
            if isinstance(self.data_change_hint, pyparameters.memory_update):
                mem_update = self.data_change_hint
                if(mem_update.action == mavlink.MAV_PFS_CMD_WRITE_SPECIFIC):
                    action = "Write specific memory area was "
                elif(mem_update.action == mavlink.MAV_PFS_CMD_READ_SPECIFIC):
                    action = "Read specific memory area was "
                elif(mem_update.action == mavlink.MAV_PFS_CMD_CLEAR_SPECIFIC):
                    action = "Clear specific memory area was "
                else:
                    action = "Non specific action on memory area action was "
                
                if(mem_update.result == mavlink.MAV_CMD_ACK_OK):
                    action += "successful"
                elif(mem_update.result == mavlink.MAV_CMD_ACK_ERR_FAIL):
                    action += "failed"
                elif(mem_update.result == mavlink.MAV_CMD_ACK_ERR_ACCESS_DENIED):
                    action += "denied"
                elif(mem_update.result == mavlink.MAV_CMD_ACK_ERR_NOT_SUPPORTED):
                    action += "not supported"
                else:
                    action += "having non specific result"

                self.data_change_hint = None
                dlg = wx.MessageDialog(self, action, "MEMORY ACTION", wx.OK)
                dlg.ShowModal()

            self.data_change_hint = None
                
    def data_change_notify(self, hint):
        self.data_change_hint = hint
        if(hint is not None):
            print("data change notify")

	
    def m_listCtrlSectionList_ItemSelected( self, event):
        item = self.m_listCtrlSectionList.GetNextItem(-1, wx.LIST_NEXT_ALL, wx.LIST_STATE_SELECTED)
        if(item != -1):
            selected_section = self.m_listCtrlSectionList.GetItemText(item)
            self.m_updateParametersGrid(selected_section)
        else:
            self.section_focus = "ALL"
            self.param_focus = ""

        event.Skip()
        
    def m_updateParametersGrid( self, section_filter):
        itemcount = 0
        if(self.m_gridParameters.GetNumberRows() > 0):
            self.m_gridParameters.DeleteRows(0, self.m_gridParameters.GetNumberRows())
        
        if(section_filter == "ALL"):
            self.m_gridParameters.InsertRows(0, len(self.parameter_data))
        else:            
            # Find number of items with selected section
            itemcount = 0 
            for param in self.parameter_data:
                param_id = getattr(param, 'param_id', "DEFAULT")
                section = param_id.replace('_',' ')
                section = re.findall(r'\w+', section)
                section = section[0]        
                if(section == section_filter):
                    itemcount = itemcount + 1
            self.m_gridParameters.InsertRows(0, itemcount)
                    
        self.section_focus = section_filter
        self.param_focus = ""
            
        #self.m_gridParameters.AutoSizeRows()
        self.m_gridParameters.SetRowLabelSize(0)
        self.m_gridParameters.SetColLabelSize(0)
        self.m_gridParameters.SetColSize(0,125)
        self.m_gridParameters.SetColSize(1,100)
        self.m_gridParameters.SetColSize(2,60)
                
        self.m_gridParameters.EnableEditing(True)
        CellAttr = wx.grid.GridCellAttr()
        CellAttr.SetReadOnly(True)
        self.m_gridParameters.SetColAttr(0, CellAttr)
        self.m_gridParameters.SetColAttr(2, CellAttr)
#                CellAttr.SetReadOnly(False)
#                self.m_gridParameters.SetColAttr(1,CellAttr)
        itemcount = 0
        for param in self.parameter_data:
            param_id = getattr(param, 'param_id', "DEFAULT")
            section = param_id.replace('_',' ')
            section = re.findall(r'\w+', section)
            section = section[0]
            if( ((section_filter == "ALL") or (section_filter == section)) ): #and (param_id != "DEFAULT")
                self.m_gridParameters.SetCellValue(itemcount, 0, str(param_id))
                param_type = getattr(param, 'param_type', mavlink.MAVLINK_TYPE_FLOAT)
                if(param_type == mavlink.MAVLINK_TYPE_INT32_T):
                    param_value = getattr(param, 'param_value', pyparameters.PARAM_UNION(val_int32=0))
                    self.m_gridParameters.SetCellValue(itemcount, 1, str(param_value.val_int32))
                    self.m_gridParameters.SetCellValue(itemcount, 2, "int")
                elif(param_type == mavlink.MAVLINK_TYPE_UINT32_T):
                    param_value = getattr(param, 'param_value', pyparameters.PARAM_UNION(val_uint32=0))
                    self.m_gridParameters.SetCellValue(itemcount, 1, str(param_value.val_uint32))
                    self.m_gridParameters.SetCellValue(itemcount, 2, "uint")
                else:
                    param_value = getattr(param, 'param_value', pyparameters.PARAM_UNION(val_float=0.0))
                    self.m_gridParameters.SetCellValue(itemcount, 1, str(param_value.val_float))
                    self.m_gridParameters.SetCellValue(itemcount, 2, "float")
                param_sync = getattr(param, 'param_sync', False)
                if(param_sync == True):
                    colour = wx.TheColourDatabase.Find("black")
                else:
                    colour = wx.TheColourDatabase.Find("red")
                self.m_gridParameters.SetCellTextColour(itemcount, 0, colour)
                self.m_gridParameters.SetCellTextColour(itemcount, 1, colour )
                self.m_gridParameters.SetCellTextColour(itemcount, 2, colour )
                 
                itemcount += 1      
                                        
                
    def m_gridParameters_CellChange(self, event):
        Row = event.GetRow()
        param_id = self.m_gridParameters.GetCellValue(Row, 0)
        param_str_val = self.m_gridParameters.GetCellValue(Row, 1)
        param = self.m_findParameter(param_id)
                
        self.param_focus = param_id
        
        if(param is not None):
            param_type = getattr(param, 'param_type', mavlink.MAVLINK_TYPE_FLOAT)
            if(param_type == mavlink.MAVLINK_TYPE_INT32_T):
                param_value = pyparameters.PARAM_UNION(val_int32 = int(param_str_val))
            elif(param_type == mavlink.MAVLINK_TYPE_UINT32_T):
                param_value = pyparameters.PARAM_UNION(val_uint32 = uint(param_str_val))
            else:
                param_value = pyparameters.PARAM_UNION(val_float = float(param_str_val))
    
            param.param_value = param_value
            param.param_sync = False
            colour = wx.TheColourDatabase.Find("red")
            self.m_gridParameters.SetCellTextColour(Row, 0, colour)
            self.m_gridParameters.SetCellTextColour(Row, 1, colour )
            self.m_gridParameters.SetCellTextColour(Row, 2, colour )
        event.Skip()

  
    def m_findParameter(self, param_id):
        if(self.parameter_data is not None):
            for param in self.parameter_data:
                p_id = getattr(param, 'param_id', "DEFAULT")
                if(str(p_id) == str(param_id)):
                    return param
        return None


    def m_btClick_WriteParameters(self, event):
        self.m_call_callbacks(callback_messages.WRITE_CHANGED_PARAMS)
        event.Skip()
        
    def m_get_selected_mem_area(self):
        selections = self.m_listBoxMemoryAreas.GetSelections()
        return selections[0]
        
    def m_btClick_LoadMem(self, event):
        self.m_call_callbacks(callback_messages.READ_NV_AREA, self.m_get_selected_mem_area())
#        self.MAVProcesses.read_nv_memory_area(self.m_get_selected_mem_area())
        event.Skip()

    def m_btClick_SaveMem(self, event):
        self.m_call_callbacks(callback_messages.SAVE_NV_AREA, self.m_get_selected_mem_area())
#        self.MAVProcesses.write_nv_memory_area(self.m_get_selected_mem_area())        
        event.Skip()

    def m_btClick_ClearMem(self, event):
        self.m_call_callbacks(callback_messages.CLEAR_NV_AREA, self.m_get_selected_mem_area())
#        self.MAVProcesses.clear_nv_memory_area(self.m_get_selected_mem_area())        
        event.Skip()

    
    def m_panelParameterEditSize ( self, event ):
        frameSize = self.m_panelParameterEdit.GetSize()
        gridSize = self.m_gridParameters.GetMaxSize()

        gridSize.SetWidth(frameSize.GetWidth() - 160)
        gridSize.SetHeight(frameSize.GetHeight() - 40)
        self.m_gridParameters.SetMaxSize(gridSize)
        self.m_gridParameters.SetMinSize(gridSize)

        gridSize.SetWidth(150)
        gridSize.SetHeight(frameSize.GetHeight() - 40)
        self.m_listCtrlSectionList.SetMaxSize(gridSize)
        self.m_listCtrlSectionList.SetMinSize(gridSize)
        
        event.Skip()
        
    def m_panelloadsaveSize(self, event):
        frameSize = self.m_panelloadsave.GetSize()
        gridSize = self.m_listBoxMemoryAreas.GetMaxSize()        
        
        gridSize.SetWidth(frameSize.GetWidth() - 120)
        gridSize.SetHeight(frameSize.GetHeight() - 60)
        self.m_listBoxMemoryAreas.SetMaxSize(gridSize)
        self.m_listBoxMemoryAreas.SetMinSize(gridSize)
        event.Skip()
    
	def m_mniOpenClick( self, event ):
		self.m_rtMain.LoadFile(fdlg.GetPath())
			
	def m_mniSaveClick( self, event ):
		self.m_rtMain.SaveFile(fdlg.GetPath())
			
	def m_mniExitClick( self, event ):
		self.Close()
	
    def m_mniAboutClick( self, event ):
		wx.MessageBox("pyparamedit ","pyparamedit")


    def m_btClick_ReadParameters (self, event):
        self.m_call_callbacks(callback_messages.READ_ALL_PARAMS)
        event.Skip()

    def OnClose(self, event):
        self.refresh_timer.Stop()
                
        event.Skip()

