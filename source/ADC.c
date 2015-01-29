#include "TM4C123.h"                    // Device header


void config_ADC(void);
void start_ADC(void);

int ADC_samples[4];
int ADC_samplesOk;
int ADC_samplesEND=1;
int a=0;
int main(){
	config_ADC();
	
	while(1){
		if (ADC_samplesEND){
		start_ADC();
		}
		a++;
		
		
	}
}

void config_ADC(void){
	//configuracion de pines 
	SYSCTL->RCGCGPIO|=(0x1<<4)|(0x1<<1)|(0x1<<3)|(0x1<<0);//habilitamos solo los gPIO que contenga las ADC analogico 
	GPIOE->DEN&=~((0x1<<4)|(0x1<<5));
	GPIOB->DEN&=~((0x1<<4)|(0x1<<5));
	GPIOE->AMSEL|=((0x1<<4)|(0x1<<5)); 
	GPIOB->AMSEL|=((0x1<<4)|(0x1<<5)); 
	
	//Configuracion ADC principal 
	SYSCTL->RCGCADC|=(0x1);//habilitamos el adc 0 
	ADC0->ACTSS&=~(0xF);//desactivacion de los secuenciadores durante la configuracion 
	ADC0->EMUX  = (0x5<<0);//  para habilitar el trigger por timer  para scc0 
	
	
	//configuracion del secuenciador 
	ADC0->SSMUX0=(0x8)|(0x9<<4)|(0xA<<8)|(0xB<<12); //ordenamiento de forma de sampleo (recuerda la asignacion es en letra o enible alto)
	ADC0->SSCTL0=(0x1<<14)|(0x1<<13);//final de secuencia en muestra 3 y genera la interrupcion 
	ADC0->IM|=(0x1<<0); //interrupcion por mascara 
	ADC0->ACTSS|=(0x1<<0);//Activando los secuenciadores del 0  
}
void ADC0_Handler(void){
	ADC0->ISC=(0x1<<0);//limpieando la interrupcion por sample 0  
	//leer fifo0
	int i;
	for(i=0;i<4;i++){
		if(ADC0->SSFSTAT0&(0x1<<8)){
		break;
		}
	   ADC_samples[i]=ADC0->SSFIFO0;	
	}
	if(((ADC0->SSFSTAT0&(0x1<<8))!=0)&&i==4){
	ADC_samplesOk=1;
	}
	else{
	ADC_samplesOk=0;
	}
}
void start_ADC(){
  ADC0->PSSI=(0x1<<0);//inicia el secuenciador 0
  
	
}
