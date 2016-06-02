#include "fir.h"
#define FIR_ORDER 64

float h_fir0[(FIR_ORDER*2)];
float h_fir1[(FIR_ORDER*2)];
float h_fir2[(FIR_ORDER*2)];
float h_fir3[(FIR_ORDER*2)];
float h_fir4[(FIR_ORDER*2)];

int headPointer = 0;

float *h_response0;
float *h_response1;
float *h_response2;
float *h_response3;
float *h_response4;

float *center_pointer0;
float *center_pointer1;
float *center_pointer2;
float *center_pointer3;
float *center_pointer4;

float gain_0 = 1;
float gain_1 = 1;
float gain_2 = 1;
float gain_3 = 1;
float gain_4 = 1;

float x_fir[FIR_ORDER];

void fir_init(const float *h_coff_0,const float *h_coff_1,const float *h_coff_2,const float *h_coff_3,const float *h_coff_4){
    for(int i=0; i<FIR_ORDER; i++){
        h_fir_0[i]=h_coff_0[(FIR_ORDER-1)-i];
        h_fir_0[i+FIR_ORDER]=h_coff_0[(FIR_ORDER-1)-i];
    }
    center_pointer_0 = &h_fir_0[(FIR_ORDER-1)];

    for(int i=0; i<FIR_ORDER; i++){
        h_fir_1[i]=h_coff_1[(FIR_ORDER-1)-i];
        h_fir_1[i+FIR_ORDER]=h_coff_1[(FIR_ORDER-1)-i];
    }
    center_pointer_1 = &h_fir_1[(FIR_ORDER-1)];

    for(int i=0; i<FIR_ORDER; i++){
        h_fir_2[i]=h_coff_2[(FIR_ORDER-1)-i];
        h_fir_2[i+FIR_ORDER]=h_coff_2[(FIR_ORDER-1)-i];
    }
    center_pointer_2 = &h_fir_2[(FIR_ORDER-1)];

    for(int i=0; i<FIR_ORDER; i++){
        h_fir_3[i]=h_coff_3[(FIR_ORDER-1)-i];
        h_fir_3[i+FIR_ORDER]=h_coff_3[(FIR_ORDER-1)-i];
    }
    center_pointer_3 = &h_fir_3[(FIR_ORDER-1)];

    for(int i=0; i<FIR_ORDER; i++){
        h_fir_4[i]=h_coff_4[(FIR_ORDER-1)-i];
        h_fir_4[i+FIR_ORDER]=h_coff_4[(FIR_ORDER-1)-i];
    }
    center_pointer_4 = &h_fir_4[(FIR_ORDER-1)];

    head_pointer = 0;
}

float fir_filter(float new_sample){
    float accumulator_0 = 0;
    float accumulator_1 = 0;
    float accumulator_2 = 0;
    float accumulator_3 = 0;
    float accumulator_4 = 0;
    float y_out = 0;

    x_fir[headPointer] = new_sample;

    h_response_0 = center_pointer_0 - headPointer;
    h_response_1 = center_pointer_1 - headPointer;
    h_response_2 = center_pointer_2 - headPointer;
    h_response_3 = center_pointer_3 - headPointer;
    h_response_4 = center_pointer_4 - headPointer;

    for(int i=0;i<FIR_ORDER;i++){
        accumulator_0 += x_fir[i] * h_response_0[i];
        accumulator_1 += x_fir[i] * h_response_1[i];
        accumulator_2 += x_fir[i] * h_response_2[i];
        accumulator_3 += x_fir[i] * h_response_3[i];
        accumulator_4 += x_fir[i] * h_response_4[i];
    }

    y_out += accumulator_0 * gain_0;
    y_out += accumulator_1 * gain_1;
    y_out += accumulator_2 * gain_2;
    y_out += accumulator_3 * gain_3;
    y_out += accumulator_4 * gain_4;

    headPointer++;
    headPointer &= (FIR_ORDER-1);
    return y_out;
}
