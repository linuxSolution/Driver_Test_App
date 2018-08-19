#ifndef MBUSHELPER_H
#define MBUSHELPER_H

#include "modbus/modbus.h"
#include "modbus/modbus-rtu.h"

#define SERVER_ID 1
#define UART_PORT "/dev/ttyS2"
#define BAUD_RATE 9600
#define PARITY 'N'
#define BYTESIZE 8
#define STOPBITS 1

#define BCM_PIN_NO 33

#define REGISTER_ADDRESS 100
#define NO_OF_REGISTERS 2

static modbus_t *ctx=NULL;

extern int rc;

extern float rvolt,yvolt,bvolt,freq,kwh;

int initialize_modbus();

void modbus_meter_reading();

void close_modbus();

#endif // MBUSHELPER_H
