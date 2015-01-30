#ifndef _TIMER_H_ 
#define _TIMER_H_
#include "TM4C123.h"                    // Device header
void timerInit(void);
void timerSet(unsigned int, unsigned char);
void timerIRQConfig(unsigned int);
void timerEnable(unsigned int);
void ledsInit(void);

extern volatile int timer_eventCounter;
#endif
