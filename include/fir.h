#ifndef _FIR_H_
#define _FIR_H_

void fir_init(const float *h_coff_0,const float *h_coff_1,const float *h_coff_2,const float *h_coff_3,const float *h_coff_4);

float fir_filter(float new_sample);

#endif
