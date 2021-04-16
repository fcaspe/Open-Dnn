#!/bin/bash

for i in 0 1 2
do
    rm -rf sub_net_$i vivado_hls.log
done

echo "Cleaned existing projects!!!"

echo "Run testbench ..."
cp ./tb/ff_test_csim.cpp ./src/ff_test.cpp
vivado_hls -f hls_script_csim.tcl
echo "Run simpler testbench and start generating sub-net IPs ..."
cp ./tb/ff_test_syn.cpp ./src/ff_test.cpp
vivado_hls -f hls_script_synth.tcl

