#!/bin/bash

while getopts i:k:h: option
do
    case "${option}"
        in
        i) INFILE=${OPTARG};;
        h) HELP=1;;
    esac
done 

#if HELP==1
#    echo "./run_generator.sh -i input.prototxt to execute the generation!"
#fi

./clean.sh

echo $INFILE
mkdir -p ../gen_proj
mkdir -p ../gen_proj/hls_proj/src
mkdir -p ../gen_proj/hls_proj/testbench
mkdir -p ../gen_proj/impl_proj/aws_impl
mkdir -p ../gen_proj/impl_proj/local_impl

echo "script executed!!!"
#--------------1.param extract-----------------------
#python3.5 paramExtractor/extract.py --model $INFILE
#mv net_config_params.txt dse/

# Skip param extraction (requires caffe and opencv2) and copy pre-extracted example from alexnet.
cp ../examples/AlexNet/net_config_params.txt ./dse/net_config_params.txt
echo "Finished network parameter extraction."
echo " "
#--------------2.design space exploration------------
python3.5 dse/tm_tn_multiAcc.py dse/net_config_params.txt
mv acc_ins_params.txt netGen/
echo "Finished accelerator design space exploration."
echo " "
#--------------3.code generation---------------------
python3.5 netGen/generate_accInst.py --params netGen/acc_ins_params.txt
python3.5 netGen/generate_consNet.py --params netGen/acc_ins_params.txt
echo "Finished accelerators and sub-nets generation."
echo "Constructing the testing and implementation folder..."
#TODO: move all the files into the correct positions, src/testbench/
cp ../fpga_cnn/src/* ../gen_proj/hls_proj/src/
cp ../fpga_cnn/testbench/* ../gen_proj/hls_proj/testbench/
mv *.h ../gen_proj/hls_proj/src/

cp ../scripts/hls_impl/* ../gen_proj/hls_proj/
cp ../scripts/sys_gen/local_impl/* ../gen_proj/impl_proj/local_impl/
cp ../scripts/sys_gen/aws_impl/* ../gen_proj/impl_proj/aws_impl/

echo "Files copied"
echo "Generation done!!!"
echo "NOTE: in acc_instance.h you can update the accelerator template parameters S_max and K_max out of its default values {5,5} to match your workloads, as this is not processed in the parser."
echo "      in ff_test.cpp you can update the input and output buffers sizes according to the description of the subnets found in construct_nets.h"

