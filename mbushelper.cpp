
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
//#include "modbus/modbus.h"
//#include "modbus/modbus-rtu.h"

//#include <modbus/modbus-rtu.h>
//#include <modbus/modbus.h>
#include "mbushelper.h"

int rc;

float rvolt,yvolt,bvolt,freq,kwh;

int initialize_modbus()
{
    uint32_t sec_to = 5;
    uint32_t usec_to = 0;

        ctx = modbus_new_rtu(UART_PORT, BAUD_RATE, PARITY, BYTESIZE, STOPBITS);
        if (ctx == NULL)
        {
            fprintf(stderr, "Unable to allocate libmodbus context\n");
            return -1;
        }
        modbus_rtu_set_rts_delay(ctx,50000);

        modbus_set_debug(ctx, TRUE);
        //modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL);
        modbus_set_slave(ctx, SERVER_ID);
        modbus_get_response_timeout(ctx, &sec_to, &usec_to);
        modbus_enable_rpi(ctx,TRUE);
        modbus_configure_rpi_bcm_pin(ctx,BCM_PIN_NO);
        modbus_rpi_pin_export_direction(ctx);

        if (modbus_connect(ctx) == -1)
        {
            fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
            modbus_free(ctx);
            return -1;
        }
}



void modbus_meter_reading()
{
          uint16_t *tab_rp_registers=NULL;

          int nb_points = 20;

           tab_rp_registers = (uint16_t *) malloc(nb_points * sizeof(uint16_t));
           memset(tab_rp_registers, 0, nb_points * sizeof(uint16_t));

            rc = modbus_read_registers(ctx,99,10,tab_rp_registers);

            printf("\n modbus read registers:%d \n",rc);

            if(rc==-1)

            {
                printf("\n read registers failed :%s\n",modbus_strerror(errno));

            }

           for(int i=0;i<rc;i++)

            {
                printf("\n reg[%d]=%d (0x%X)\n",i,tab_rp_registers[i],tab_rp_registers[i]);

            }

            rvolt=modbus_get_float(&tab_rp_registers[0]);
            printf("\n R Voltage: %f",rvolt);

            yvolt=modbus_get_float(&tab_rp_registers[2]);
            printf("\n y Voltage: %f",yvolt);


            bvolt=modbus_get_float(&tab_rp_registers[4]);
            printf("\n B Voltage: %f",bvolt);

             memset(tab_rp_registers, 0, nb_points * sizeof(uint16_t));

            rc = modbus_read_registers(ctx,171,2,tab_rp_registers);

            printf("\n modbus read registers:%d \n",rc);

            if(rc==-1)

            {
                printf("\n read registers failed :%s\n",modbus_strerror(errno));

            }

            for(int i=0;i<rc;i++)

           {
               printf("\n reg[%d]=%d (0x%X)\n",i,tab_rp_registers[i],tab_rp_registers[i]);
           }

           freq=modbus_get_float(&tab_rp_registers[0]);
           printf("\n Frequency: %f",freq);


            memset(tab_rp_registers, 0, nb_points * sizeof(uint16_t));

            rc = modbus_read_registers(ctx,223,2,tab_rp_registers);

            printf("\n modbus read registers:%d \n",rc);

            if(rc==-1)

            {
                printf("\n read registers failed :%s\n",modbus_strerror(errno));
            }

            for(int i=0;i<rc;i++)

           {
               printf("\n reg[%d]=%d (0x%X)\n",i,tab_rp_registers[i],tab_rp_registers[i]);
           }

           kwh=modbus_get_float(&tab_rp_registers[0]);
           printf("\n KWH: %f",kwh);
}


void close_modbus()
{
        modbus_rpi_pin_unexport_direction(ctx);
        modbus_close(ctx);
        modbus_free(ctx);
}
