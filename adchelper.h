#ifndef ADCHELPER_H
#define ADCHELPER_H


extern int ret_adc;
extern int fd_adc;

extern float voltage0;
extern float voltage1;
extern float voltage2;
extern float voltage3;

int adc_spi_initialize();
float calculate_channel_voltage0(int fd,uint8_t *tx);
void close_spi_adc();
void pabort_adc(const char *s);

////////////

float get_scale_value();

int ADC_Channnel_Volatge_Read(int channel_no);

#endif // ADCHELPER_H
