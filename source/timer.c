#include "timer.h"

volatile int timer_eventCounter;

void ledsInit(){
		SYSCTL->RCGCGPIO|=(0x1<<5);//Enable GPIOF
		GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Set GPIOF[1..3] for digital operation
		GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Set  GPIOF[1..3] as outputs
}

void timerSet(unsigned int count, unsigned char prescale){
	timerEnable(0);
	TIMER0->TAILR=count;
	TIMER0->TAPR=prescale;
}

void timerEnable(unsigned int enable){
		if(enable){
				TIMER0->CTL|=0x01;//Start Timer
		}else{
			  TIMER0->CTL&=~((unsigned int) 0x01);//Stop Timer
		}
}

void timerInit(void){
		SYSCTL->RCGCTIMER|=0x1;//Enable peripherial timer0
	  TIMER0->CTL=0x00;//Disable timer during configuration 
	  TIMER0->CFG=0x4;// a/b 16 bit mode 
	  TIMER0->TAMR=(0x0<<4)|(0x02);//TAM as periodic timer/ down timer
	  TIMER0->TAILR=0x01;//set top value as 0x01
		TIMER0->TAPR=0x0;//set prescaler to 0x00
		TIMER0->CTL=(0x1<<1)|(0x1<<5);//Enable debug stall and ADC triggering
}

void timerIRQConfig(unsigned int enable){
	  if(enable){
			NVIC_EnableIRQ(TIMER0A_IRQn);
			TIMER0->IMR=0x01;
		}else{
			NVIC_DisableIRQ(TIMER0A_IRQn);
			TIMER0->IMR=0x00;
		}
}

void TIMER0A_Handler(){
	TIMER0->ICR=0x01;//clear interrupt flag
	timer_eventCounter++;
}
