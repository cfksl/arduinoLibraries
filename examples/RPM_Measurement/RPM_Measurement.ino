/******************************************************************************
    @file     RPM_Measurement.ino
    @author   Tirthankar Chakraborty (CFKSL)
    @license  BSD 

This example will print RPM Value from a Rotary Encoder (Interrupt Based).

Please follow the below mentioned details on how to use it.
mytimer.Start(num) - num is the prescaler to divide the frequency.
Arduino has a Clock Frequency of 16MHz
0 - Frequency/1 i.e. 16MHz
1 - Frequency/8 i.e. 2MHz
2 - Frequency/32 i.e. 500KHz
3 - Frequency/64 i.e. 250KHz
4 - Frequency/128 i.e. 125KHz
5 - Frequency/256 i.e. 62.5KHz
6 - Frequency/1024 i.e. 15.625KHz

mytimer.attachInterruptT0(counter);
[Counter] is the Interrupt Service Routine (ISR Function) which will be called at each Timer Interrupt. Attach Interrupt is just like other interrupt functions.
*********************************************************************************/
/********************************************************************************
Example Calculations of 1 Second 

Prescaler selected 1024 that means timer frequency is 15.625KHz.
Timer will be incremented after every - 1/Freq = 1/15.625 mS = 0.064 mS = 64 uS.
Here Timer 2 is used which is a 8 bit timer. So Timer Overflow occurs after every 255*64 uS = 16.32 mS.
Here a variable is counting the number of overflows. To generate a second delay we need no. of overflows = 1000mS(1 Sec)/16.32 = 61.27 = 61 Approx.
That's why the checking has been done at 61 times to reset the variable.

Here 1000 PPR encoder has been used. It gives 1000 pulses per revolution.
*********************************************************************************/

#include <Timer0.h>

Timer0 mytimer;
long count=0;
long pulses=0;
void setup()
{
  mytimer.Start(6); // Prescaler set at 1024 - Frequency selected at 15.625 KHz
  mytimer.attachInterruptT0(counter); //The name of the function which will be called at every timer interrupt
  attachInterrupt(0, pulse_int, RISING); //External Interrupt at pin no. 2 
  Serial.begin(9600);
}

void loop()
{
    if(count==61) // Refer the above Calculations
    {
      Serial.println(pulses*60/1000); //Revolutions Per Minute - Pulses per second*60. 1000 taken for Rotary Encoder pulses per revolution.
      pulses=0;
      count=0; 
    }
}

void counter() //Timer ISR
{
  count++;
}

void pulse_int()
{
  pulses++;
}

