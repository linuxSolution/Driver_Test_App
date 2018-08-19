#ifndef CANHELPER_H
#define CANHELPER_H

#include <linux/can.h>
#include <linux/can/raw.h>

extern int soc;
extern int read_can_port;

int open_port(const char *);
int send_port(struct can_frame *);
struct can_frame read_port();

int close_port();

#endif // CANHELPER_H
