
#ifndef _CONSTRUCT_NET_H_
#define _CONSTRUCT_NET_H_

#include <iostream>
#include <ap_fixed.h>
#include "acc_instance.h"

using namespace std;

void sub_net_0(  
        Tparam param_port[1024],
        data_type_itf weight_in[20300],
        
        data_type_itf data_in_0[9662],
        data_type_itf data_out_0[22688],
        data_type_itf data_in_1[22688],
        data_type_itf data_out_1[14580],
        int select ) {
        
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=select bundle=CRTL_BUS

#pragma HLS INTERFACE s_axilite port=param_port bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=param_port offset=slave depth=1024 bundle=PARAM_IN
//#pragma HLS INTERFACE s_axilite port=bias_in bundle=CRTL_BUS
//#pragma HLS INTERFACE m_axi port=bias_in offset=slave depth=20300 bundle=BIAS_IN
#pragma HLS INTERFACE s_axilite port=weight_in bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=weight_in offset=slave depth=20300 bundle=WEIGHT_IN 
    
#pragma HLS INTERFACE s_axilite port=data_in_0 bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=data_in_0 offset=slave depth=9662 bundle=DATA_IN     
    
#pragma HLS INTERFACE ap_memory port=data_out_0 latency=3
#pragma HLS INTERFACE ap_memory port=data_in_1 latency=3
#pragma HLS INTERFACE bram port=data_out_1        
         
    int acc0_mem_inport_offset = 0;
	int acc0_mem_outport_offset = 0;
	int acc1_mem_inport_offset = 0;
	int acc1_mem_outport_offset = 0;

	if (select == 0)
	{
		acc0_mem_inport_offset = 0;
		acc0_mem_outport_offset = 0;
		acc1_mem_inport_offset = 11344;
		acc1_mem_outport_offset = 7290;
	}
	else
	{
		acc0_mem_inport_offset = 4831;
		acc0_mem_outport_offset = 11344;
		acc1_mem_inport_offset = 0;
		acc1_mem_outport_offset = 0;
	}
     
    conv_pool_acc_0(param_port + 0,       
                //bias_in,       
                weight_in,  
                data_in_0 + acc0_mem_inport_offset,  
                data_out_0 +acc0_mem_outport_offset); 
    
    conv_pool_acc_1(param_port + 512,       
                //bias_in,       
                weight_in,  
                data_in_1 + acc1_mem_inport_offset,  
                data_out_1 +acc1_mem_outport_offset); 
     };

void sub_net_1(  
        Tparam param_port[1024],
        data_type_itf weight_in[27660],
        
        data_type_itf data_in_0[2704],
        data_type_itf data_out_0[4056],
        int select ) {
        
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=select bundle=CRTL_BUS

#pragma HLS INTERFACE s_axilite port=param_port bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=param_port offset=slave depth=1024 bundle=PARAM_IN
//#pragma HLS INTERFACE s_axilite port=bias_in bundle=CRTL_BUS
//#pragma HLS INTERFACE m_axi port=bias_in offset=slave depth=27660 bundle=BIAS_IN
#pragma HLS INTERFACE s_axilite port=weight_in bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=weight_in offset=slave depth=27660 bundle=WEIGHT_IN 
    
#pragma HLS INTERFACE s_axilite port=data_in_0 bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=data_in_0 offset=slave depth=2704 bundle=DATA_IN     
    
#pragma HLS INTERFACE ap_memory port=data_out_0 latency=3
     
    int acc0_mem_inport_offset = 0;
    int acc0_mem_outport_offset = 0;
    
    if (select == 0)
    {
        acc0_mem_inport_offset = 0;
        acc0_mem_outport_offset = 0;
    }
    else
    {
        acc0_mem_inport_offset = 0;
        acc0_mem_outport_offset = 0;
    }
     
    conv_pool_acc_0(param_port + 0,       
                //bias_in,       
                weight_in,  
                data_in_0 + acc0_mem_inport_offset,  
                data_out_0 +acc0_mem_outport_offset); 
     };

void sub_net_2(  
        Tparam param_port[1024],
        data_type_itf weight_in[69140],
        
        data_type_itf data_in_0[4056],
        data_type_itf data_out_0[4056],
        data_type_itf data_in_1[4056],
        data_type_itf data_out_1[3380],
        int select ) {
        
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=select bundle=CRTL_BUS

#pragma HLS INTERFACE s_axilite port=param_port bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=param_port offset=slave depth=1024 bundle=PARAM_IN
//#pragma HLS INTERFACE s_axilite port=bias_in bundle=CRTL_BUS
//#pragma HLS INTERFACE m_axi port=bias_in offset=slave depth=69140 bundle=BIAS_IN
#pragma HLS INTERFACE s_axilite port=weight_in bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=weight_in offset=slave depth=69140 bundle=WEIGHT_IN 
    
#pragma HLS INTERFACE s_axilite port=data_in_0 bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=data_in_0 offset=slave depth=4056 bundle=DATA_IN     
    
#pragma HLS INTERFACE ap_memory port=data_out_0 latency=3
#pragma HLS INTERFACE ap_memory port=data_in_1 latency=3
#pragma HLS INTERFACE bram port=data_out_1        
         
    int acc0_mem_inport_offset = 0;
	int acc0_mem_outport_offset = 0;
	int acc1_mem_inport_offset = 0;
	int acc1_mem_outport_offset = 0;

	if (select == 0)
	{
		acc0_mem_inport_offset = 0;
		acc0_mem_outport_offset = 0;
		acc1_mem_inport_offset = 2028;
		acc1_mem_outport_offset = 1690;
	}
	else
	{
		acc0_mem_inport_offset = 2028;
		acc0_mem_outport_offset = 2028;
		acc1_mem_inport_offset = 0;
		acc1_mem_outport_offset = 0;
	}
     
    conv_pool_acc_0(param_port + 0,       
                //bias_in,       
                weight_in,  
                data_in_0 + acc0_mem_inport_offset,  
                data_out_0 +acc0_mem_outport_offset); 
    
    conv_pool_acc_1(param_port + 512,       
                //bias_in,       
                weight_in,  
                data_in_1 + acc1_mem_inport_offset,  
                data_out_1 +acc1_mem_outport_offset); 
     };

#endif
