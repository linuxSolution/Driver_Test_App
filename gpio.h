#ifndef GPIO_H
#define GPIO_H

/*
    include files
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    hash defines
*/

#define IN  0
#define OUT 1

/*
    Function decaration
*/

int GPIOUnexport(int pin);
int GPIOExport(int pin);
int GPIODirection(const char *pin, int dir);

#endif // GPIO_H



