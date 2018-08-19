#ifndef GPO_H
#define GPO_H

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

#define LOW  0
#define HIGH 1

/*
    Function Declarations
*/

int GPIOWrite(const char *pin, int value);

#endif // GPO_H
