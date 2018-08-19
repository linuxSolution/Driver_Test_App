
#include <QDebug>
#include <sys/types.h>
#include <linux/hdreg.h>
#include <fcntl.h>

#include <fstream>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <arpa/inet.h>
#include <linux/spi/spidev.h>

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char device_adc[30] ="/dev/spidev32766.1";
uint8_t mode_adc= 0;
uint8_t bits_adc= 8;
uint32_t speed_adc= 500000;
uint16_t delay_adc = 0;
int fadc =-1;
int spiintdone =2;

int txrxspi(uint8_t *tx, uint8_t *rx,uint8_t len);

float adc1valueget(void)
{
    float value;
    uint8_t len;
    uint32_t adc_code,c;
    uint8_t adctx[] = {0xB0, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00};
    uint8_t adcrx[] = {0xB0, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00};  //RX value  should not equal to tx, just to make sure array in line

    len = 8;

    txrxspi(adctx,adcrx,len);


    //I am not sure about this methode
    //Please check datasheet if ISIL ADC and get back to result.
    //You can check print of return value of SPI. That shoud not of 0x00 or 0xFF;

    c=*((uint32_t*) adcrx);     //I am not at all confident on this, this need to change. Or for long run this pointer will crash and creat memory holes.
    adc_code=htonl(c);

    if (adc_code == 0x00000000)
    {
        adc_code = 0x20000000;
    }

    adc_code -= 0x20000000;             //! 1) Converts offset binary to binary
    value=(float) adc_code;
    value = value / 536870912.0;    //! 2) This calculates the input as a fraction of the reference voltage (dimensionless)
    value = value * 5;           //! 3) Multiply fraction by Vref to get the actual voltage at the input (in volts)
    return(value);



}

float adc2valueget(void)
{
    float value;
    uint8_t len;
    uint32_t adc_code,c;
    uint8_t adctx[] = {0xB8, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00};
    uint8_t adcrx[] = {0xB8, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00};  //RX value  should not equal to tx, just to make sure array in line

    len = 4;

    txrxspi(adctx,adcrx,len);

    c=*((uint32_t*) adcrx);
    adc_code=htonl(c);

    if (adc_code == 0x00000000)
    {
        adc_code = 0x20000000;
    }

    adc_code -= 0x20000000;             //! 1) Converts offset binary to binary
    value=(float) adc_code;
    value = value / 536870912.0;    //! 2) This calculates the input as a fraction of the reference voltage (dimensionless)
    value = value * 5;           //! 3) Multiply fraction by Vref to get the actual voltage at the input (in volts)
    return(value);



}

float adc3valueget(void)
{
    float value;
    uint8_t len;
    uint32_t adc_code,c;
    uint8_t adctx[] = {0xB1, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00};
    uint8_t adcrx[] = {0xB1, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00};  //RX value  should not equal to tx, just to make sure array in line

    len = 4;

    txrxspi(adctx,adcrx,len);


    c=*((uint32_t*) adcrx);
    adc_code=htonl(c);

    if (adc_code == 0x00000000)
    {
        adc_code = 0x20000000;
    }

    adc_code -= 0x20000000;             //! 1) Converts offset binary to binary
    value=(float) adc_code;
    value = value / 536870912.0;    //! 2) This calculates the input as a fraction of the reference voltage (dimensionless)
    value = value * 5;           //! 3) Multiply fraction by Vref to get the actual voltage at the input (in volts)
    return(value);



}

float adc4valueget(void)
{
    float value;
    uint8_t len;
    uint32_t adc_code,c;
    uint8_t adctx[] = {0xB9, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00};
    uint8_t adcrx[] = {0xB9, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00};  //RX value  should not equal to tx, just to make sure array in line

    len = 4;

    txrxspi(adctx,adcrx,len);


    c=*((uint32_t*) adcrx);
    adc_code=htonl(c);

    if (adc_code == 0x00000000)
    {
        adc_code = 0x20000000;
    }

    adc_code -= 0x20000000;             //! 1) Converts offset binary to binary
    value=(float) adc_code;
    value = value / 536870912.0;    //! 2) This calculates the input as a fraction of the reference voltage (dimensionless)
    value = value * 5;           //! 3) Multiply fraction by Vref to get the actual voltage at the input (in volts)
    return(value);



}

int txrxspi(uint8_t *tx, uint8_t *rx,uint8_t len)
{
    int ret;
    struct spi_ioc_transfer tr;

    tr.rx_buf = (unsigned long)rx;
    tr.tx_buf = (unsigned long)tx;
    tr.len = len;
    tr.delay_usecs = 0;
    tr.speed_hz = speed_adc;
    tr.bits_per_word = bits_adc;

    qDebug() << "Writting SPI\n\r";

    ret = ioctl(fadc,SPI_IOC_MESSAGE(1), &tr);
    if(ret == 1)
    {
        qDebug()<<"SPI write failed";
        return -1;
    }

    //print read message
    for(int tp=0;tp<len;tp++)
    {
        qDebug()<<"Read Value: " <<rx[tp];
    }
    return 1;
}

int spiadcinit(void)
{
    int ret;
    qDebug() << "Nimish Debug Opening file: " << device_adc;
    fadc = open(device_adc, O_RDWR);
    if (fadc < 0)
    {
        qDebug() << "can't open device";
        return 0;
    }

    ret = ioctl(fadc, SPI_IOC_WR_MODE, &mode_adc);
    if (ret == -1)
    {
        qDebug() << "can't set spi mode";
        return -1;
    }

    ret = ioctl(fadc, SPI_IOC_RD_MODE, &mode_adc);
    if (ret == -1)
    {
        qDebug() << "can't get spi mode";
        return -1;
    }


    ret = ioctl(fadc, SPI_IOC_WR_BITS_PER_WORD, &bits_adc);
    if (ret == -1)
    {
        qDebug() << "can't set bits per word";
        return -1;
    }

    ret = ioctl(fadc, SPI_IOC_RD_BITS_PER_WORD, &bits_adc);
    if (ret == -1)
    {
        qDebug() << "can't get bits per word";
        return -1;
    }

    ret = ioctl(fadc, SPI_IOC_WR_MAX_SPEED_HZ, &speed_adc);
    if (ret == -1)
    {
        qDebug() << "Can't set max speed hz";
        return -1;
    }

    ret = ioctl(fadc, SPI_IOC_RD_MAX_SPEED_HZ, &speed_adc);
    if (ret == -1)
    {
        qDebug() << "can't get max speed hz";
        return -1;
    }

    qDebug() << "Speed = "  << speed_adc;
    qDebug() << "bis = "  << bits_adc;
    return 1;

}
