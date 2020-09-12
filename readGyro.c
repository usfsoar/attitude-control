// MPU6050 interfacing with Raspberry Pi
// Using Wiring Pi
// Ryan Carlomany
//

#include "mpu6050.h"
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

void MPU6050_Init(int fd);
short * read_raw_data(int fd, int addr);

int main()
{

	int fd;

	float Acc_x, Acc_y, Acc_z;
	float Gyro_x, Gyro_y, Gyro_z;
	float Ax = 0, Ay = 0, Az = 0;
	float Gx = 0, Gy = 0, Gz = 0;
	float pitchAngle = 0, yawAngle = 0;
	fd = wiringPiI2CSetup(DEVICE_ADDRESS);
	MPU6050_Init(fd);
	short *readVal;

	while(1)
	{

		for (int i = 0; i < 10; i++)
		{
		// Read raw value of Accelerometer and Gyroscope
		readVal = read_raw_data(fd,ACCEL_XOUT_H);
		Acc_x = *readVal;
		readVal = read_raw_data(fd,ACCEL_YOUT_H);
		Acc_y = *readVal;
		readVal = read_raw_data(fd,ACCEL_ZOUT_H);
		Acc_z = *readVal;

		readVal = read_raw_data(fd,GYRO_XOUT_H);
		Gyro_x = *readVal;
		readVal = read_raw_data(fd,GYRO_YOUT_H);
		Gyro_y = *readVal;
		readVal = read_raw_data(fd,GYRO_ZOUT_H);
		Gyro_z = *readVal;
		 
		//Divide raw values by sensitivity factor
		Ax += Acc_x/16384.0;
		Ay += Acc_y/16384.0;
		Az += Acc_z/16384.0;

		Gx += Gyro_x/131;
		Gy += Gyro_y/131;
		Gz += Gyro_z/131;
		
		pitchAngle = (180/M_PI)*(atan2(Az,Ax)-(M_PI/2));
		yawAngle = (180/M_PI)*(atan2(Az,Ay)-(M_PI/2));
		}
		
		Ax = Ax/10;
		Ay = Ay/10;
		Az = Az/10;

		Gx = Gx/10;
		Gy = Gy/10;
		Gz = Gz/10;

		if (pitchAngle >= 90)
			pitchAngle = 90;
		else if (pitchAngle <= -90)
			pitchAngle = -90;
		
		if (yawAngle >= 90)
			yawAngle = 90;
		else if (yawAngle <= -90)
			yawAngle = -90;

		printf("\n Gx=%.3f deg/s\t Gy=%.3f deg/s\t Gz=%.3f deg/s\t Ax=%.3f g\t Ay=%.3f g\t Az=%.3f g\t Pitch Angle=%.3f deg\t Yaw Angle=%.3f deg\n", Gx, Gy, Gz, Ax, Ay, Az, pitchAngle, yawAngle);
		//printf("\n Gx=%.3f deg/s\tGy=%.3f deg/s\tGz=%.3f deg/s\tAx=%.3f g\tAy=%.3f g\t Az=%.3f g\n", Gx, Gy, Gz, Ax, Ay, Az);
		//delay(500);
	}
	return 0;
}


