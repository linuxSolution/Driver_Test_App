#include "adcext.h"
#include "ui_adcext.h"
#include "adchelper.h"

#include <unistd.h>
#include "adccalibration.h"
#include "ExternalAdc/extadc.h"

#include <QDebug>
#include "SqlDatabase/db_manager.h"

adcExt::adcExt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adcExt)
{
    ui->setupUi(this);
    //adc_spi_initialize();
    spiadcinit();
    readAdcSql();
}

adcExt::~adcExt()
{
    delete ui;
}

void adcExt::on_adcExtbackButton_clicked()
{
    close_spi_adc();
    emit showMain();
    this->close();
}

void adcExt::on_readAdcButton_clicked()
{
    float an1,an2,an3,an4;

    int x,y,z,a;

    scale=get_scale_value();

    float voltage,v,v1;
    float resistance,Temperature,resistance1,Temperature1;

    int i;
    float sum_voltage=0,sum_voltage2=0,sum_tempearature1=0,sum_tempearature2=0;

    for(i=0;i<100;i++)
    {

        x=ADC_Channnel_Volatge_Read(4);

        voltage=x*scale/20;

        sum_voltage+=voltage;

        a=ADC_Channnel_Volatge_Read(5);

        voltage2=a*scale/20;

        sum_voltage2+=voltage2;

        y=ADC_Channnel_Volatge_Read(10);

        v=y*scale/2000;

        resistance= (3600*v)/(5-v);

        Temperature =(resistance-1000)/3.85;

        sum_tempearature1+=Temperature;

        z=ADC_Channnel_Volatge_Read(11);

        v1=z*scale/2000;

        resistance1= (3600*v1)/(5-v1);

        Temperature1 =(resistance1-1000)/3.85;

        sum_tempearature2+=Temperature1;

    }

    uint8_t tx0[] = {
         0xB0, 0x08, 0x00, 0x00,0x00,0x00,0x00,0x00
    };

    uint8_t tx1[] = {
        0xB8, 0x08, 0x00, 0x00,
    };

    uint8_t tx2[] = {
        0xB1, 0x08, 0x00, 0x00,
    };

    uint8_t tx3[] = {
        0xB9, 0x08, 0x00, 0x00,
    };


   // float volt=calculate_channel_voltage0(fd_adc,tx0);

    float volt = adc1valueget();
    sleep(1);

    //volt=calculate_channel_voltage0(fd_adc,tx0);
    volt = adc1valueget();

    sleep(1);

   // volt=calculate_channel_voltage0(fd_adc,tx0);
    volt = adc1valueget();

    float cabinet_temp=volt*1000/20;


    printf("\n Cabinet Temperature is %f: ", cabinet_temp);

    sleep(1);

    //volt=calculate_channel_voltage0(fd_adc,tx1);
    volt = adc2valueget();
    sleep(1);


    //volt=calculate_channel_voltage0(fd_adc,tx1);
       volt = adc2valueget();
    sleep(1);

    //volt=calculate_channel_voltage0(fd_adc,tx1);
       volt = adc2valueget();

    float CC2=volt;

    printf("\n voltage2 is %f: ", CC2);

    sleep(1);


    //volt=calculate_channel_voltage0(fd_adc,tx2);
       volt = adc3valueget();
    sleep(1);


    //volt=calculate_channel_voltage0(fd_adc,tx2);
    volt = adc3valueget();
    sleep(1);

    //volt=calculate_channel_voltage0(fd_adc,tx2);
    volt = adc3valueget();

    float shunt_current_2=volt*150;

    //volt=calculate_channel_voltage0(fd_adc,tx3);
    volt = adc4valueget();

    sleep(1);


    //volt=calculate_channel_voltage0(fd_adc,tx3);
    volt = adc4valueget();
    sleep(1);

   // volt=calculate_channel_voltage0(fd_adc,tx3);
    volt = adc4valueget();

    //float shunt_current=volt*150;

    float shunt_current=volt*125;

    if(cabinet_temp>0)
    {
        //ui->lineEdit_an1->setText(QString::number((cabinet_temp*an1_gain)-an1_offset));
        ui->lineEdit_an1->setText(QString::number((cabinet_temp-an1_offset)*an1_gain));
    }

    if(CC2>0)
    {
         //ui->lineEdit_an2->setText(QString::number((CC2*an2_gain)-an2_offset));
        ui->lineEdit_an2->setText(QString::number((CC2-an2_offset)*an2_gain));
    }

    if(shunt_current_2>0)
    {
        //ui->lineEdit_an3->setText(QString::number((shunt_current_2*an3_gain)-an3_offset));
         ui->lineEdit_an3->setText(QString::number((shunt_current_2-an3_offset)*an3_gain));
    }

    if(shunt_current>0)
    {
        //ui->lineEdit_an4->setText(QString::number((shunt_current*an4_gain)-an4_offset));
        ui->lineEdit_an4->setText(QString::number((shunt_current-an4_offset)*an4_gain));
    }

    ui->lineEdit_an5->setText(QString::number((((sum_voltage/100)*an5_gain)-0.65)));

    ui->lineEdit_an6->setText(QString::number((((sum_voltage2/100)*an6_gain)-0.65)));

    ui->lineEdit_an7->setText(QString::number((((sum_tempearature1/100)*an7_gain)-an7_offset)));

    ui->lineEdit_an8->setText(QString::number(((sum_tempearature2/100)*an8_gain)-an8_offset));

}

void adcExt::readAdcSql(){

   qDebug()<<"start";
   Db_Manager::add_database("/home/launchApps/Apps/ChargerApps/sqlite/charger.db");

   //Reading a key
    QString qs = Db_Manager::getKey("adc4gain");

     if(qs.isNull() == false)
    {
        qDebug()<<"Before Database"<<an4_gain;
        an4_gain = qs.toFloat();
        qDebug()<<"After Database"<<an4_gain;
    }
    else {

        qDebug()<<"Charger Disc: DB ReadError \r";
    }

     //Reading a key
      qs = Db_Manager::getKey("adc4offset");

       if(qs.isNull() == false)
      {
          qDebug()<<"Before Database"<<an4_offset;
          an4_offset = qs.toFloat();
          qDebug()<<"After Database"<<an4_offset;
      }
      else {

          qDebug()<<"Charger Disc: DB ReadError \r";
      }

      qDebug()<<"end";
}
