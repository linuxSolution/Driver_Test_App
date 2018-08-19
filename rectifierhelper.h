#ifndef RECTIFIERHELPER_H
#define RECTIFIERHELPER_H

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static void pabort(const char *s);

static const char *device = "/dev/spidev32765.0";
static uint8_t mode = 1;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay;

extern uint8_t tx[10];

void transfer(int fd);

extern int ret_rect;
extern int fd_rect;

void spidev_initialize();

void close_spidev();

extern unsigned char done;

#endif // RECTIFIERHELPER_H
