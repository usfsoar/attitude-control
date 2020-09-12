# makefile to create thrustVector
# 2020-05-28: Ryan Carlomany

# link object files and system libraries to create an executable
thrustVector: thrustVector.o gpioSetup.o servoControl.o mpu6050.o
	gcc -o thrustVector thrustVector.o gpioSetup.o servoControl.o mpu6050.o -l wiringPi -lm

#compile/assemble source files to create object files
thrustVector.o: thrustVector.c gpioSetup.h servoControl.h
	gcc -g -c thrustVector.c -l wiringPi -lm

gpioSetup.o: gpioSetup.c gpioSetup.h
	gcc -g -c gpioSetup.c

servoControl.o: servoControl.c servoControl.h
	gcc -g -c servoControl.c

mpu6050.o: mpu6050.c mpu6050.h
	gcc -g -c mpu6050.c -l wiringPi

#remove object files and backup files
clean:
	rm -i *.o
