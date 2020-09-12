#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

int * pulseCalc(int period, float I, float x2, int Ft, float theta, float angVel);

void servoPWM(int g, int tpulse, int toff);

#endif
