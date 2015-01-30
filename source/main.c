#include "TM4C123.h"                    // Device header
#include "fir.h"
#include "timer.h"
#include "adc.h"
volatile int adc_eventCounter;
volatile int pendSV_eventCounter;
volatile int error_fatal=0;
volatile int idle_eventCounter;
volatile float volt_in;
volatile float volt_out;
const float filter_coeff[64] = {
  -0.0009320193785,-0.004670707043,-0.003568851156,-0.004917577375,-0.005164533388,
  -0.004857675172, -0.00368647743,-0.001686632051, 0.001003203099, 0.004066620488,
   0.007042370737, 0.009390991181,  0.01055809669,  0.01008756459, 0.007711261511,
   0.003445450217,-0.002369154012,-0.009046530351,   -0.015611168, -0.02089740708,
   -0.02368940786, -0.02289023623,  -0.0176963564,-0.007748788688, 0.006773100235,
    0.02511152439,  0.04597771168,  0.06766960025,  0.08825633675,   0.1057950556,
     0.1185685247,   0.1252965331,   0.1252965331,   0.1185685247,   0.1057950556,
    0.08825633675,  0.06766960025,  0.04597771168,  0.02511152439, 0.006773100235,
  -0.007748788688,  -0.0176963564, -0.02289023623, -0.02368940786, -0.02089740708,
     -0.015611168,-0.009046530351,-0.002369154012, 0.003445450217, 0.007711261511,
    0.01008756459,  0.01055809669, 0.009390991181, 0.007042370737, 0.004066620488,
   0.001003203099,-0.001686632051, -0.00368647743,-0.004857675172,-0.005164533388,
  -0.004917577375,-0.003568851156,-0.004670707043,-0.0009320193785
};

int main(){
	fir_init(filter_coeff);
	adc_config();
	timerInit();
	timerSet(2000,0);//interrupt every (0+1)*2000 counts 
	timerIRQConfig(1);
	NVIC_EnableIRQ(ADC0SS0_IRQn);
	NVIC_SetPriority(PendSV_IRQn,0x7); 
	ledsInit();
	timerEnable(1);
	while(1){
		if(timer_eventCounter>=10000){
			timer_eventCounter=0;
			GPIOF->DATA^=(0x1<<1)|(0x1<<2)|(0x1<<3);
		}if(error_fatal){
			GPIOF->DATA=(0x1<<1);
		}
		idle_eventCounter++;
	}
}

void ADC0SS0_Handler(){
	ADC0->ISC=(0x1<<0);//Limpiamos interrupcion por secuenciador 0
	adc_sample=ADC0->SSFIFO0;
	adc_eventCounter++;
	if(((SCB->SHCSR)&(SCB_SHCSR_PENDSVACT_Msk))){
		error_fatal=1;
		__disable_irq();
		timerEnable(0);
	}else{
		SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
	}
}

void PendSV_Handler(void){
	volt_in=((((float)adc_sample)*(2.0f/4095.0f))-1.0f);
	volt_out=fir_filter(volt_in);
	pendSV_eventCounter++;
}
