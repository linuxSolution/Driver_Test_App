#ifndef EXTADC_H
#define EXTADC_H

#include <stdint.h>

int txrxspi(uint8_t *tx, uint8_t *rx,uint8_t len);
int spiadcinit(void);
float adc1valueget(void);
float adc2valueget(void);
float adc3valueget(void);
float adc4valueget(void);
#endif // EXTADC_H
