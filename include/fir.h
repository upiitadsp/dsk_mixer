#ifndef _FIR_H_ 
#define _FIR_H_
void fir_init(const float *h_coff);
float fir_filter(float new_sample);
#endif
