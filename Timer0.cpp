/*
  Timer0.h - Library for Accessing Timer in Arduino.
  Created by T.Chakraborty, August 27, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Timer0.h"
#include "WInterrupts.c"

volatile static voidFuncPtr t0IntFunc;

void Timer0::Start(unsigned int scale)
{
	TCCR2A=0x00;
	TIMSK2=0x01; // Timer Interrupt Enable
	//TCCR2B=0x05;
	switch(scale)
	{
		case 0: TCCR2B=0x01;break; // Selects prescaler division factor 1
		case 1: TCCR2B=0x02;break; // Selects prescaler division factor 8
		case 2: TCCR2B=0x03;break; // Selects prescaler division factor 32
		case 3: TCCR2B=0x04;break; // Selects prescaler division factor 64
		case 4: TCCR2B=0x05;break; // Selects prescaler division factor 128
		case 5: TCCR2B=0x06;break; // Selects prescaler division factor 256
		case 6: TCCR2B=0x07;break; // Selects prescaler division factor 1024
		
	}

		
}

void Timer0::Stop() //Timer Stop
{
  TCCR2A=0x00;
  TCCR2B=0x00;
  TIMSK2=0x00;
}

void Timer0::attachInterruptT0(void (*userFunc)(void) ) {
  t0IntFunc = userFunc;
}


ISR(TIMER2_OVF_vect) {
  if(t0IntFunc)
    t0IntFunc();
}

