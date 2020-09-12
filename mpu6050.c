// MPU6050.h
// Uses the wiringPi library to read accelerometer and gyroscope values from MPU6050.
// Gyro value is the angular velocity, pitch and yaw angles are calculated.
//
// 2020-05-29: Ryan Carlomany

#include "mpu6050.h"
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>

void MPU6050_Init(int fd)
{
	wiringPiI2CWriteReg8(fd,SMPLRT_DIV, 0x07);
	wiringPiI2CWriteReg8(fd,PWR_MGMT_1, 0x01);
	wiringPiI2CWriteReg8(fd,CONFIG, 0);
	wiringPiI2CWriteReg8(fd,GYRO_CONFIG, 24);
	wiringPiI2CWriteReg8(fd,INT_ENABLE, 0x01);
}

short * read_raw_data(int fd, int addr)
{
	short high_byte, low_byte;
	short *value = malloc(sizeof(short)*2);
	high_byte = wiringPiI2CReadReg8(fd, addr);
	low_byte = wiringPiI2CReadReg8(fd, addr);
	*value = (high_byte << 8) | low_byte;
	
return value;
}
