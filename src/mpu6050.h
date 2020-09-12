// MPU6050.h
// Uses the wiringPI library to read accelerometer and gyroscope values from MPU6050.
// Gyro value is the angular velocity, pitch and yaw angles are calculated.
//
// 2020-05-29: Ryan Carlomany

#ifndef MPU6050_H
#define MPU6050_H

#define DEVICE_ADDRESS	0x68

#define PWR_MGMT_1	0x6B
#define SMPLRT_DIV	0x19
#define CONFIG		0x1A
#define GYRO_CONFIG	0x1B
#define INT_ENABLE	0x38
#define ACCEL_XOUT_H	0x3B
#define ACCEL_YOUT_H	0x3D
#define ACCEL_ZOUT_H	0x3F
#define GYRO_XOUT_H	0x43
#define GYRO_YOUT_H	0x45
#define GYRO_ZOUT_H	0x47

void MPU6050_Init(int fd);
short * read_raw_data(int fd, int addr);


#endif
