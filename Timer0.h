/*
  Timer0.h - Library for Accessing Timer in Arduino.
  Created by T.Chakraborty, August 27, 2015.
  Released into the public domain.
*/
#ifndef Timer0_h
#define Timer0_h
#include "Arduino.h"




class Timer0
{
  public:
	void Start(unsigned int scale);
        void Stop();    
        void attachInterruptT0(void (*userFunc)(void) );
            
  private:
    unsigned int _scale;
    
      
};

#endif