#include "fir.h"
#define FIR_ORDER 64
float h_fir[(FIR_ORDER*2)];
float x_fir[FIR_ORDER];
int headPointer=0;
float accumulator=0;
float *h_response;
float *center_pointer;
void fir_init(const float *h_coff){
	for(int i=0; i<FIR_ORDER; i++){
		h_fir[i]=h_coff[(FIR_ORDER-1)-i];
		h_fir[i+FIR_ORDER]=h_coff[(FIR_ORDER-1)-i];
	}
	center_pointer=&h_fir[(FIR_ORDER-1)];
}

float fir_filter(float new_sample){
	h_response=center_pointer-headPointer;
	x_fir[headPointer]=new_sample;
	accumulator=0;
	for(int i=0;i<FIR_ORDER;i++){
		accumulator+=x_fir[i]*h_response[i];
	}
	headPointer++;
	headPointer&=(FIR_ORDER-1);
	return accumulator;
}
