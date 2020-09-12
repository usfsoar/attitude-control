//servoControl.c 
//Calculates the required pulse time to move the servo motor to the correct
//angle to compensate the rocket's angle.
//2020-05-28: Ryan Carlomany

#include "servoControl.h"
#include "gpioSetup.h"
#include <stdio.h>
#include <stdlib.h>

int * pulseCalc(int period, float I, float x2, int Ft, float theta, float angVel)
{					
	int *pulses = malloc(sizeof(int)*2);

	*pulses = (((1.55/180)*(((21.081*I*theta)/(x2*Ft)) - ((8*I*angVel)/(x2*Ft)))) + 1.225)*1000;

	*(pulses + 1) = period - *pulses;

	return pulses;

}//pulseCalc


