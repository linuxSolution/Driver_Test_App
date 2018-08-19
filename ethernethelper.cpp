#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int ethernet_status=-1;

int check_ethernet_connection()
{
#define VALUE_MAX 100
    char path[VALUE_MAX];
    char value_str[4];

    int fd;

    snprintf(path, VALUE_MAX, "/sys/class/net/eth0/operstate");
        printf("\n%s\n\n",path);
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open value for ethernet checking!\n");
        return(-1);
    }

    if (-1 == read(fd,value_str,6)) {
        fprintf(stderr, "Failed to read value!\n");
        return(-1);
    }

    close(fd);

    if(value_str[0]=='d')
    {
        printf("\n entering into strcmp \n");
        ethernet_status=0;
    }

    if(value_str[0]=='u')
    ethernet_status=1;

    printf("value of the status %d",ethernet_status);

    return((ethernet_status));
}
