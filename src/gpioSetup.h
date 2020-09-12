/* gpioSetup.h
 * Sets up the Raspberry Pi's GPIO pins
 *
 * 2020-05-28: Ryan Carlomany
 */

#ifndef DIRECT_REG_H
#define DIRECT_REG_H

//General
#define BCM2711_PERI_BASE 0xfe000000 //Base address for main peripherals
#define PAGE_SIZE (4*1024) //Page size is 4kB
#define BLOCK_SIZE (4*1024) //Block size is 4kB

//GPIO
#define GPIO_BASE (BCM2711_PERI_BASE + 0x200000) //GPIO Base address

#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3)) //Accesses GPFSEL registers 0 to 5 for input condition of 000
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3)) //Accesses GFPSEL registers 0 to 5 for output condition of 001 
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3)) //Accesses GFPSEL registers 0 to 5 and allows for alterate pin functions

#define GPIO_SET *(gpio+7) //Accesses GPSET registers 0 and 1 to set a pin a GPIO pin. Only writing ones to an output pin will be set.
#define GPIO_CLR *(gpio+10) // Accesses the GPCLR register 0 and 1 to clear a GPIO pin. Only writing ones to an ouput pin will be cleared.

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // Accesses GPLEV0 register to detect the current value of the GPIO pin.

volatile unsigned * setup_io();

#endif
