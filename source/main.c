#include "TM4C123.h"                    // Device header

void timerConfig(void);
void set_timer(unsigned int, unsigned char);
void timerIRQConfig(unsigned int);
void timerEnable(unsigned int);
void configureLeds(void);
volatile int globalVAR1;
volatile int iterationMax;
volatile int loopActive;

float a=1;
float b=1.5;
float c=0;
int main(){
		int iterationIndex;
 	  timerConfig();
	  set_timer(1133,0);//reset every (0+1)*1133 counts 
	  timerIRQConfig(1);
	  timerEnable(1);
		configureLeds();
		while(1){
			if(globalVAR1>=44100){
				 GPIOF->DATA^=0xE;
				 globalVAR1=0;
			}
			loopActive=1;
			iterationIndex=0;
			c=0.0f;
			a=1.2f;
			b=1.3f;
			while(loopActive){
				c+=(a*b);
				a+=0.125f;
				b+=0.25f;
				iterationIndex++;
			}
			iterationMax=iterationIndex;
		}
}

void configureLeds(){
		SYSCTL->RCGCGPIO|=(0x1<<5);//Enable GPIOF
		GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Set GPIOF[1..3] for digital operation
		GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Set  GPIOF[1..3] as outputs
}


void set_timer(unsigned int count, unsigned char prescale){
	timerEnable(0);
	TIMER0->TAILR=count;
	TIMER0->TAPR=prescale;
}

void timerEnable(unsigned int enable){
		if(enable){
				TIMER0->CTL|=0x01;
		}else{
			  TIMER0->CTL&=~((unsigned int) 0x01);
		}
}

void timerConfig(void){
		SYSCTL->RCGCTIMER|=0x1;//Enable peripherial timer0
	  TIMER0->CTL=0x00;//Disable timer during configuration 
	  TIMER0->CFG=0x4;// a/b 16 bit mode 
	  TIMER0->TAMR=(0x0<<4)|(0x02);//TAM as periodic timer/ down timer
	  TIMER0->TAILR=1023;//set top value as 1023
	  TIMER0->CTL=(0x1<<1);//Enable debug stall
}

void timerIRQConfig(unsigned int enable){
	  TIMER0->IMR=0x01;
	  if(enable){
			NVIC_EnableIRQ(TIMER0A_IRQn);
		}else{
			NVIC_DisableIRQ(TIMER0A_IRQn);
		}
}

void TIMER0A_Handler(){
	TIMER0->ICR=0x01;//clear interrupt
	globalVAR1++;
	loopActive=0;
}
