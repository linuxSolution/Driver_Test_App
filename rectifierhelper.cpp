#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "rectifierhelper.h"


int ret_rect = 0;
int fd_rect;

unsigned char done=0;



static void pabort(const char *s)
{
    perror(s);
    abort();
}


uint8_t tx[] = {
        0x01, 0x00, 0x94, 0x11, 0xE8, 0x03,
        0x00, 0x00, 0x00, 0x00,
    };

void transfer(int fd)
{
    int ret;

    uint8_t rx[ARRAY_SIZE(tx)] = {0, };
    struct spi_ioc_transfer tr;
    /*= {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = ARRAY_SIZE(tx),
        .delay_usecs = delay,
        .speed_hz = 0,
        .bits_per_word = 0,
    };*/




    tr.tx_buf=(unsigned long)tx;
    tr.rx_buf=(unsigned long)rx;
    tr.len=ARRAY_SIZE(tx);
    tr.delay_usecs=delay;
    tr.speed_hz=0;
    tr.bits_per_word=0;

    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret == 1)
        pabort("can't send spi message");

    for (ret = 0; ret < ARRAY_SIZE(tx); ret++) {
        if (!(ret % 6))
            puts("");
        printf("%.2X ", rx[ret]);
    }
    puts("");
}

void spidev_initialize()
{

    fd_rect = open(device, O_RDWR);
    if (fd_rect < 0)
        pabort("can't open device");

    /*
     * spi mode
     */
    ret_rect = ioctl(fd_rect, SPI_IOC_WR_MODE, &mode);
    if (ret_rect == -1)
        pabort("can't set spi mode");

    ret_rect = ioctl(fd_rect, SPI_IOC_RD_MODE, &mode);
    if (ret_rect == -1)
        pabort("can't get spi mode");

    /*
     * bits per word
     */
    ret_rect = ioctl(fd_rect, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret_rect == -1)
        pabort("can't set bits per word");

    ret_rect = ioctl(fd_rect, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret_rect == -1)
        pabort("can't get bits per word");

    /*
     * max speed hz
     */
    ret_rect = ioctl(fd_rect, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret_rect == -1)
        pabort("can't set max speed hz");

    ret_rect = ioctl(fd_rect, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret_rect == -1)
        pabort("can't get max speed hz");

    printf("spi mode: %d\n", mode);
    printf("bits per word: %d\n", bits);
    printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

}

void close_spidev()
{
  close(fd_rect);

}




