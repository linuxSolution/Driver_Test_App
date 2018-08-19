#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <arpa/inet.h>
#include <linux/spi/spidev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static const char *device_adc = "/dev/spidev32766.1";
static uint8_t mode_adc = 0;
static uint8_t bits_adc = 8;
static uint32_t speed_adc = 500000;
static uint16_t delay_adc;

int ret_adc = 0;
int fd_adc;

float voltage0;
float voltage1;
float voltage2;
float voltage3;

void pabort_adc(const char *s)
{
    perror(s);
    abort();
}

float calculate_channel_voltage0(int fd,uint8_t *tx)
{
    int ret1;

    uint8_t rx[ARRAY_SIZE(tx)] = {0, };

    struct spi_ioc_transfer tr;
    tr.tx_buf=(unsigned long)tx;
    tr.rx_buf=(unsigned long)rx;
    tr.len=ARRAY_SIZE(tx);
    tr.delay_usecs=delay_adc;
    tr.speed_hz=0;
    tr.bits_per_word=0;

    ret1 = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret1 == 1)
        pabort_adc("can't send spi message");

    for (ret1 = 0; ret1 < ARRAY_SIZE(tx); ret1++) {
        if (!(ret1 % 6))
            puts("");
        //printf("%.2X ", rx[ret1]);
    }
    puts("");

       int32_t adc_code,c;
       c=*((uint32_t*) rx);
        adc_code=htonl(c);

       if (adc_code == 0x00000000)
      {
        adc_code = 0x20000000;
      }

  adc_code -= 0x20000000;             //! 1) Converts offset binary to binary
  voltage0=(float) adc_code;
  voltage0 = voltage0 / 536870912.0;    //! 2) This calculates the input as a fraction of the reference voltage (dimensionless)
  voltage0 = voltage0 * 5;           //! 3) Multiply fraction by Vref to get the actual voltage at the input (in volts)
  return(voltage0);
}

int adc_spi_initialize()
{
        //parse_opts(argc, argv);

    fd_adc = open(device_adc, O_RDWR);
    if (fd_adc < 0)
        pabort_adc("can't open device");

    /*
     * spi mode
     */
    ret_adc = ioctl(fd_adc, SPI_IOC_WR_MODE, &mode_adc);
    if (ret_adc == -1)
        pabort_adc("can't set spi mode");

    ret_adc = ioctl(fd_adc, SPI_IOC_RD_MODE, &mode_adc);
    if (ret_adc == -1)
        pabort_adc("can't get spi mode");

    /*
     * bits per word
     */
    ret_adc = ioctl(fd_adc, SPI_IOC_WR_BITS_PER_WORD, &bits_adc);
    if (ret_adc == -1)
        pabort_adc("can't set bits per word");

    ret_adc = ioctl(fd_adc, SPI_IOC_RD_BITS_PER_WORD, &bits_adc);
    if (ret_adc == -1)
        pabort_adc("can't get bits per word");

    /*
     * max speed hz
     */
    ret_adc = ioctl(fd_adc, SPI_IOC_WR_MAX_SPEED_HZ, &speed_adc);
    if (ret_adc == -1)
        pabort_adc("can't set max speed hz");

    ret_adc = ioctl(fd_adc, SPI_IOC_RD_MAX_SPEED_HZ, &speed_adc);
    if (ret_adc == -1)
        pabort_adc("can't get max speed hz");

    printf("spi mode: %d\n", mode_adc);
    printf("bits per word: %d\n", bits_adc);
    printf("max speed: %d Hz (%d KHz)\n", speed_adc, speed_adc/1000);



}

void close_spi_adc()
{
    close(fd_adc);
}

////

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1


int ADC_Channnel_Volatge_Read(int channel_no)
{
#define VALUE_MAX 100
    char path[VALUE_MAX];
    char value_str[3];
    int fd;

    snprintf(path, VALUE_MAX, "/sys/bus/iio/devices/iio\:device0/in_voltage%d_raw", channel_no);
        printf("\n%s\n\n",path);
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open %s gpio value for reading!\n",channel_no);
        return(-1);
    }

    if (-1 == read(fd, value_str, 6)) {
        fprintf(stderr, "Failed to read value!\n");
        return(-1);
    }

    close(fd);

    return(atoi(value_str));
}

float get_scale_value()
{
#define VALUE_MAX 100
    char path[VALUE_MAX];
    char value_str[3];
    int fd;

    snprintf(path, VALUE_MAX, "/sys/bus/iio/devices/iio\:device0/in_voltage_scale");
        printf("\n%s\n\n",path);
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to get scale value for reading!\n");
        return(-1);
    }

    if (-1 == read(fd, value_str, 6)) {
        fprintf(stderr, "Failed to read value!\n");
        return(-1);
    }

    close(fd);

    return(atof(value_str));
}
