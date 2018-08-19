#ifndef GPI_H
#define GPI_H

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
    Function decaration
*/

int GPIORead(const char *pin);

#endif // GPI_H
