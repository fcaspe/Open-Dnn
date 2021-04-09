#include <iostream>

//Optional 
//#include "/tools/Xilinx/Vivado/2018.3/include/gmp.h"
//#include "/tools/Xilinx/Vivado/2018.3/include/mpfr.h"

#include "ap_fixed.h"
#include "construct_net.h"
#include "../testbench/conv_validate.h"
#include "../testbench/pooling_validate.h"
#include "../testbench/fc_validate.h"

using namespace std;

void construct_para(ap_uint<32>* para);
void print_para_list(ap_uint<32>* para);

int main()
{
	int i,j,k;
	cout <<"Test Begin..."<<endl;

	//ap_uint<32> para_list[1024];
	//ap_int<512> input_image[9662];   //input image (DOUBLE BUFFER)
	//ap_int<512> output0_map[22688];  //Data out accelerator 0
    //ap_int<512> output1_map[14580];  //Data out accelerator 1
    //ap_int<512> weights[1092];  //Data out
    
    ap_uint<32>* para_list = (ap_uint<32>*)malloc(1024*sizeof(ap_uint<32>));
	ap_int<512>* input_image = (ap_int<512>*)malloc(103058*sizeof(ap_int<512>));
    ap_int<512>* output0_map = (ap_int<512>*)malloc(22688*sizeof(ap_int<512>));
    ap_int<512>* output1_map = (ap_int<512>*)malloc(14580*sizeof(ap_int<512>));
    ap_int<512>* weights = (ap_int<512>*)malloc(20300*sizeof(ap_int<512>));

    
	//ap_int<512> data_temp3[2048];
	//ap_int<512> data_temp4[2048];
	//ap_int<512> data_temp5[2048];
	//ap_int<512> data_temp6[2048];

	for(i = 0 ; i < 1024; i++)
		para_list[i] = 0;
	
    for(i = 0 ; i < 103058; i++)
	{
		input_image[i] = 0;
	}

    for(i = 0 ; i < 22688; i++)
    
	{
		output0_map[i] = 0;
	}

    for(i = 0 ; i < 14580; i++)
	{
		output1_map[i] = 0;
	}

    for(i = 0 ; i < 20300; i++)
	{
		weights[i] = 0;
	}

	construct_para(para_list);
	print_para_list(para_list);
	//conv_validate conv_test(para_list);

    /* Run test: Output of one layer is the input of the next layer */
    
	sub_net_0(
			para_list,						//Offset = 0, parameters for the first accelerator. Offset = 512, for the second accelerator
                                            // In 512 words: First 256 are for conv parameters. Second section 256 are for pooling parameters
                                            // Each set of parameters is 16 words. So we can serve 16 different workloads in a single accelerator.

			//conv_test.bias,				//ap_fixed<32,26> bias_in[1024],
			weights,
			input_image,                    //Select = 0 reads from offset=0
			output0_map,                    //Select = 0 writes to offset = 0
			output0_map,                    //Select = 0 reads from offset = 11344
			output1_map,                    //Seledt = 0 writes to offset = 7290
			
            0								//Select just selects which half of the input/output buffer to access, so that the other half can be accessed by the system.
			);
    
    /*Now, enable pool and run accelerator again.*/
    
    para_list[256+16+15] = 1; //pool enable (will take data from output buffer and store in the output buffer too)

	sub_net_0(
			para_list,						//Offset = 0, parameters for the first accelerator. Offset = 512, for the second accelerator
                                            // In 512 words: First 256 are for conv parameters. Second section 256 are for pooling parameters
                                            // Each set of parameters is 16 words. So we can serve 16 different workloads in a single accelerator.

			//conv_test.bias,				//ap_fixed<32,26> bias_in[1024],
			weights,
			input_image,                    //Select = 0 reads from offset=0
			output0_map,                    //Select = 0 writes to offset = 0
			output0_map,                    //Select = 0 reads from offset = 11344
			output1_map,                    //Seledt = 0 writes to offset = 7290
			
            0								//Select just selects which half of the input/output buffer to access, so that the other half can be accessed by the system.
			);
/*
	sub_net_1(
			para_list,						//ap_uint<32> param_port[528],
			//conv_test.                    //ap_fixed<32,26> bias_in[1024],
			conv_test.weight,				//data_type_itf weight_in[2048],
			data_temp2,                     //data_type_itf data_in_0[2048],
			data_temp3,					//data_type_itf data_out_0[2048],
			data_temp3,					//data_type_itf data_in_1[2048],
			data_temp4,//conv_test.output_feature,	    //data_type_itf data_out_1[2048],
			0								//int select
			);


	sub_net_2(
			para_list,						//ap_uint<32> param_port[528],
			//conv_test.bias,					//ap_fixed<32,26> bias_in[1024],
			conv_test.weight,				//data_type_itf weight_in[2048],
			data_temp4,	    //data_type_itf data_in_0[2048],
			data_temp5,						//data_type_itf data_out_0[2048],
			data_temp5,						//data_type_itf data_in_1[2048],
			data_temp6,//conv_test.output_feature,	    //data_type_itf data_out_1[2048],
			0								//int select
			);
*/
	cout <<"Test Finish"<<endl;
	return 0;
}


void construct_para(ap_uint<32>* para)
{
	  int i;
	  //0-1.layer_num
	  para[0] = 1; /*number of layer tasks to be executed by this accelerator. Subsequent layer information can be added in para[32+...], para[48+...], and so on/*/
	  //0-1.conv para (First task, alexnet first layer)
	  para[16+0] = 3;//N
	  para[16+1] = 11;//K
	  para[16+2] = 96;//M
	  para[16+3] = 227;//Rin
	  para[16+4] = 227;//Cin
	  para[16+5] = 55;//R
	  para[16+6] = 55;//C
	  para[16+7] = 4;//S
	  para[16+8] = 0;//P
	  para[16+9] = 1;//act
	  para[16+10] = 0;//weight_offset
	  para[16+11] = 0;//bias_offset
	  para[16+12] = 0;//in_offset
	  para[16+13] = 0;//out_offset
	  para[16+14] = 0; //inport: 0= Use AXI interface to load data from. 1= Use local BRAM for data (ie: Use when computing intermediate tasks)
	  para[16+15] = 0;

/*	  //0-1.conv para (First task)
	  para[16+0] = 1;//N
	  para[16+1] = 3;//K
	  para[16+2] = 1;//M
	  para[16+3] = 16;//Rin
	  para[16+4] = 16;//Cin
	  para[16+5] = 16;//R
	  para[16+6] = 16;//C
	  para[16+7] = 1;//S
	  para[16+8] = 1;//P
	  para[16+9] = 1;//act
	  para[16+10] = 0;//weight_offset
	  para[16+11] = 0;//bias_offset
	  para[16+12] = 0;//in_offset
	  para[16+13] = 0;//out_offset
	  para[16+14] = 0;//inport
	  para[16+15] = 0;*/


    /*Pooling parameters*/

	  //1-1.layer_num
	  para[256+0] = 1;
	  //1-2. Pool params
	  para[256+16+0] = 55; //R_in
	  para[256+16+1] = 55; //C_in
	  para[256+16+2] = 96; //N
	  para[256+16+3] = 2;  //K
	  para[256+16+4] = 27; //R
	  para[256+16+5] = 27; //C
	  para[256+16+6] = 2; //S
	  para[256+16+7] = 0;  //P
	  para[256+16+8] = 0;  //act
	  para[256+16+9] = 0;  //in_offset
	  para[256+16+10] = 0; //out_offset
	  para[256+16+11] = 0;
	  para[256+16+12] = 0;
	  para[256+16+13] = 0;
	  para[256+16+14] = 0;
	  para[256+16+15] = 0; //pool enable (will take data from output buffer and store in the output buffer too)
/*
	  //1-3.conv_para
	  para[256+32+0] = 1; //N
	  para[256+32+1] = 3; //K
	  para[256+32+2] = 1; //M
	  para[256+32+3] = 16; //Rin
	  para[256+32+4] = 16; //Cin
	  para[256+32+5] = 16;  //R
	  para[256+32+6] = 16;  //C
	  para[256+32+7] = 1;  //S
	  para[256+32+8] = 1;  //P
	  para[256+32+9] = 1;  //act
	  para[256+32+10] = 0; //weight_offset
	  para[256+32+11] = 0; //bias_offset
	  para[256+32+12] = 0; //in_offset
	  para[256+32+13] = 512; //out_offset
	  para[256+32+14] = 1; //inport
	  para[256+32+15] = 0;

	  //1-4.conv_para
	  para[256+48+0] = 1; //N
	  para[256+48+1] = 3; //K
	  para[256+48+2] = 1; //M
	  para[256+48+3] = 16; //Rin
	  para[256+48+4] = 16; //Cin
	  para[256+48+5] = 16;  //R
	  para[256+48+6] = 16;  //C
	  para[256+48+7] = 1;  //S
	  para[256+48+8] = 1;  //P
	  para[256+48+9] = 1;  //act
	  para[256+48+10] = 0; //weight_offset
	  para[256+48+11] = 0; //bias_offset
	  para[256+48+12] = 512; //in_offset
	  para[256+48+13] = 0; //out_offset
	  para[256+48+14] = 1; //inport
	  para[256+48+15] = 0;

*/




}
void print_para_list(ap_uint<32>* para)
{
	int i,j;
    
	for(i = 0 ; i < 32; i++)
	{
        if(i == 0) cout << "Conv Task Execution Parameters" << endl;
        if(i == 1) cout << "Conv Parameters" << endl;
        if(i == 16) cout << "Pool Task Execution Parameters" << endl;
        if(i == 17) cout << "Pool Parameters" << endl;
    	for(j = 0 ; j < 16; j++)
			cout << para[i*16+j] <<" ";
		cout << endl;
	}
}
