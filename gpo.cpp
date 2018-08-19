#include "gpo.h"

int GPIOWrite(const char *pin, int value)
{
    static const char s_values_str[] = "01";

    #define VALUE_MAX 30

    char path[VALUE_MAX];
    int fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/%s/value", pin);
    printf("\n%s\n",path);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open %s gpio value for writing!\n",pin);
        return(-1);
    }

    if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
        fprintf(stderr, "Failed to write value!\n");
        return(-1);
    }

    close(fd);
    return(0);
}
