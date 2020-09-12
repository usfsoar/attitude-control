//thrustVector.c
//The main program that reads in the current theta and angular velocity values
//to control the servo motor to make the proper thrust deflection angle.
//2020-05-28: Ryan Carlomany

#include "gpioSetup.h"
#include "servoControl.h"
#include "mpu6050.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

volatile unsigned * setup_io();
int * pulseCalc(int period, float I, float x2, int Ft, float theta, float angVel);
void MPU6050_Init(int fd);
short * read_raw_data(int fd, int addr);

int main(void)
{ 
	int i2c_fd;
	float Acc_x, Acc_y, Acc_z;
	float Gyro_x, Gyro_y, Gyro_z;
	float Ax = 0, Ay = 0, Az = 0;
	float Gx = 0, Gy = 0, Gz = 0;
	float pitchAngle = 0, yawAngle = 0;

	int g = 17;
	int rep = 0;
 	int period = 20000;
  	float tpulse; 
  	int toff;
  	float I = 0.6856;
  	float x2 = 0.6350;
  	int Ft = 20;
  	//float theta;
  	//float angVel;

	i2c_fd = wiringPiI2CSetup(DEVICE_ADDRESS);
	MPU6050_Init(i2c_fd);
	short *readVal;

	/*
	printf("Enter the current angle of the rocket:\n");
  	scanf("%f", &theta);
	printf("Enter the current angular velocity\n");
  	scanf("%f", &angVel);
	*/

  	volatile unsigned *gpio = setup_io();
	int *pulses;

  	INP_GPIO(g);
  	OUT_GPIO(g);
  
  	while(1)
  	{
		readVal = read_raw_data(i2c_fd, ACCEL_XOUT_H);
		Acc_x = *readVal;
		readVal = read_raw_data(i2c_fd, ACCEL_YOUT_H);
		Acc_y = *readVal;
		readVal = read_raw_data(i2c_fd, ACCEL_ZOUT_H);
		Acc_z = *readVal;

		readVal = read_raw_data(i2c_fd, GYRO_XOUT_H);
		Gyro_x = *readVal;
		readVal = read_raw_data(i2c_fd, GYRO_YOUT_H);
		Gyro_y = *readVal;
		readVal = read_raw_data(i2c_fd, GYRO_ZOUT_H);
		Gyro_z = *readVal;

		Ax = Acc_x/16384.0;
		Ay = Acc_y/16384.0;
		Az = Acc_z/16384.0;
  		
		Gx = Gyro_x/131;
		Gy = Gyro_y/131;
		Gz = Gyro_z/131;

		pitchAngle = (180/M_PI)*(atan2(Az,Ax)-(M_PI/2));

		if (pitchAngle >= 90)
			pitchAngle = 90;
		else if (pitchAngle <= -90)
			pitchAngle = -90;
		
		
		printf("Ay=%.3f g\t Az=%.3f g\t Gy=%.3f deg/s\t pitchAngle=%.3f deg\n", Ay, Az, Gy, pitchAngle);
	
		pulses = pulseCalc(period, I, x2, Ft, pitchAngle, Gy);
		tpulse = *pulses;
		toff = *(pulses + 1);
		
    		GPIO_SET = (1 << g);
    		usleep(tpulse); 
 
    		GPIO_CLR = (1 << g);
    		usleep(toff);
    
    		/*if (theta > 0)
    			theta--;
    		else if (theta < 0)
			theta += 2;
    		else
			break;*/
  	}
	  
  	if(!GET_GPIO(g))
    		GPIO_SET = (1 << g);

  	printf("stable\n");

  	return 0;

}//main
