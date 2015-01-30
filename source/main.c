#include "TM4C123.h"                    // Device header
#include "fir.h"
#include "timer.h"
#include "adc.h"

int adc_eventCounter;

int main(){
	adc_config();
	timerInit();
	timerSet(5000,0);//interrupt every (0+1)*5000 counts 
	timerIRQConfig(1);
	NVIC_EnableIRQ(ADC0SS0_IRQn);
	ledsInit();
	timerEnable(1);
	while(1){
		if(timer_eventCounter>=10000){
			timer_eventCounter=0;
			GPIOF->DATA^=(0x1<<1)|(0x1<<2)|(0x1<<3);
		}
	}
}

void ADC0SS0_Handler(){
	ADC0->ISC=(0x1<<0);//Limpiamos interrupcion por secuenciador 0
	adc_sample=ADC0->SSFIFO0;
	adc_eventCounter++;
}
