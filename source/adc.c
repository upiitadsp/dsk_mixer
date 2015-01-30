#include "adc.h"  
//AIN8 PE5
int adc_sample;
void adc_config(void){
	/*Configuracion de Pines*/	
	SYSCTL->RCGCGPIO|=((0x1<<4)|(0x1<<3)|(0x1<<2)|(0x1<<1)|(0x1<<0));
	SYSCTL->RCGCADC|=(0x1<<0);//habilitamos ADC0
	
	GPIOE->DEN&=~((0x1<<4)|(0x1<<5));
	GPIOB->DEN&=~((0x1<<4)|(0x1<<5));
	GPIOE->AMSEL|=(0x1<<4)|(0x1<<5);
	GPIOB->AMSEL|=(0x1<<4)|(0x1<<5);
	//Configuracion ADC principal
	ADC0->ACTSS&=~(0xF);//desactivamos secuenciadores durantes la configuracion
	ADC0->EMUX=(0x5<<0);//3:0 EM0=0x5 SS0 Trigger Select TIMER
	
	//Configuracion del sequenciador
	ADC0->SSMUX0=(0x8)|(0x8<<4)|(0x8<<8)|(0x8<<12);//samples 1 2 3 4 taken from AIN8
	ADC0->SSCTL0=	((0x1<<2)|// 2 IE0=1  The raw interrrup signal is asserted at end of sample  0
								(0x1<<1));// 1 END0=1 sample 0 is the last sample of the sequence 
	//Desenmacaramos interrupcion por secuenciador 0
	ADC0->IM|=(0x1<<0);
	ADC0->ACTSS|=(0x1<<0);//activamos secuenciador 0
}
