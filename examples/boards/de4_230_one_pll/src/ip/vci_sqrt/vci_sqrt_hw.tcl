# TCL File Generated by Component Editor 12.1
# Thu Apr 04 15:12:21 PDT 2013
# DO NOT MODIFY


# 
# vci_sqrt "MXP CI: A -> B" v1.0
# null 2013.04.04.15:12:21
# 
# 

# 
# request TCL package from ACDS 12.0
# 
package require -exact qsys 12.0


# 
# module vci_sqrt
# 
set_module_property NAME vci_sqrt
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property DISPLAY_NAME "MXP CI: Sqrt(A)"
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL vci_sqrt
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file vci_sqrt/util_pkg.vhd VHDL PATH util_pkg.vhd
add_fileset_file vci_sqrt/sqrt_alt.vhd VHDL PATH sqrt_alt.vhd
add_fileset_file vci_sqrt/vci_sqrt.vhd VHDL PATH vci_sqrt.vhd

add_fileset SIM_VHDL SIM_VHDL "" ""
set_fileset_property SIM_VHDL TOP_LEVEL vci_sqrt
set_fileset_property SIM_VHDL ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file vci_sqrt/util_pkg.vhd VHDL PATH util_pkg.vhd
add_fileset_file vci_sqrt/sqrt_alt.vhd VHDL PATH sqrt_alt.vhd
add_fileset_file vci_sqrt/vci_sqrt.vhd VHDL PATH vci_sqrt.vhd


# 
# parameters
# 
add_parameter VCI_LANES POSITIVE 2
set_parameter_property VCI_LANES DEFAULT_VALUE 2
set_parameter_property VCI_LANES DISPLAY_NAME VCI_LANES
set_parameter_property VCI_LANES TYPE POSITIVE
set_parameter_property VCI_LANES UNITS None
set_parameter_property VCI_LANES HDL_PARAMETER true
add_parameter FXP_BITS NATURAL 0
set_parameter_property FXP_BITS DEFAULT_VALUE 0
set_parameter_property FXP_BITS DISPLAY_NAME FXP_BITS
set_parameter_property FXP_BITS TYPE NATURAL
set_parameter_property FXP_BITS UNITS None
set_parameter_property FXP_BITS HDL_PARAMETER true
add_parameter PIPELINE_STAGES NATURAL 8
set_parameter_property PIPELINE_STAGES DEFAULT_VALUE 8
set_parameter_property PIPELINE_STAGES DISPLAY_NAME PIPELINE_STAGES
set_parameter_property PIPELINE_STAGES TYPE NATURAL
set_parameter_property PIPELINE_STAGES UNITS None
set_parameter_property PIPELINE_STAGES HDL_PARAMETER true


# 
# display items
# 


# 
# connection point conduit_end
# 
add_interface conduit_end conduit end
set_interface_property conduit_end associatedClock ""
set_interface_property conduit_end associatedReset ""
set_interface_property conduit_end ENABLED true

add_interface_port conduit_end vci_clk export Input 1
add_interface_port conduit_end vci_reset export Input 1
add_interface_port conduit_end vci_valid export Input 1
add_interface_port conduit_end vci_signed export Input 1
add_interface_port conduit_end vci_opsize export Input 2
add_interface_port conduit_end vci_vector_start export Input 1
add_interface_port conduit_end vci_vector_end export Input 1
add_interface_port conduit_end vci_byte_valid export Input vci_lanes*4
add_interface_port conduit_end vci_data_a export Input vci_lanes*32
add_interface_port conduit_end vci_flag_a export Input vci_lanes*4
add_interface_port conduit_end vci_data_b export Input vci_lanes*32
add_interface_port conduit_end vci_flag_b export Input vci_lanes*4
add_interface_port conduit_end vci_data_out export Output vci_lanes*32
add_interface_port conduit_end vci_flag_out export Output vci_lanes*4
add_interface_port conduit_end vci_byteenable export Output vci_lanes*4
