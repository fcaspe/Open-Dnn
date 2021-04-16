##############################################################################
## This file is modified from the tcl script generated with vivado_hls 2018.2.
## This modified version is used to ease the run of synthesis of the sub_nets.
## Please edit based on the user manual if necessary.
##############################################################################

#if { $argc != 1} {
#    puts "The hls_script.tcl script requires only one input."
#    puts "For example. hls_script.tcl 0"
#    puts "Please try again"
#} else {
#    puts [$PNUM = $argv 0]
#}

open_project ip_gen


#add design files to the project
add_files ./src/data_type.h -cflags "-g"
add_files ./src/config.h -cflags "-g"
add_files ./src/activation_functions.h -cflags "-g"
add_files ./src/conv_acc_2ibuf.h -cflags "-g"
add_files ./src/max_pool_acc_innerpp.h -cflags "-g"
add_files ./src/fc_acc_innerpp.h -cflags "-g"
add_files ./src/acc_instance.h -cflags "-g"
add_files ./src/construct_net.h -cflags "-g"
add_files ./src/ff_test.cpp -cflags "-g"

add_files -tb ./testbench/conv_validate.h -cflags "-g"
add_files -tb ./testbench/conv_validate.cpp -cflags "-g"
add_files -tb ./testbench/pooling_validate.h -cflags "-g"
add_files -tb ./testbench/pooling_validate.cpp -cflags "-g"
add_files -tb ./testbench/fc_validate.h -cflags "-g"
add_files -tb ./testbench/fc_validate.cpp -cflags "-g"
add_files -tb ./testbench/print_array.h -cflags "-g"
add_files -tb ./src/ff_test.cpp -cflags "-g"

for {set i 0} {$i < 1} {incr i} {
    set_top sub_net_$i

    open_solution -reset "sub_net_$i"
    # UltraScale+ 
    set_part {xcvu9p-flgb2104-2-i} -tool vivado

    create_clock -period 1.6 -name default
    config_compile -name_max_length 500 -pipeline_loops 0
    #Set stack size big enough to host all arrays in testbench without malloc.
    csim_design -clean -compiler gcc
    #csynth_design

    # If the co-sim is required for verification, uncomment the following line.
    #cosim_design -compiler gcc -trace_level all

    #export_design -flow syn -rtl verilog -format ip_catalog
    #export_design -rtl verilog -format ip_catalog
}

exit

}
