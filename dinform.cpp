#include "dinform.h"
#include "ui_dinform.h"

#include "gpio.h"
#include "gpi.h"

#include <iostream>
using namespace std;
#include <qthread.h>

dinForm::dinForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dinForm)
{
    ui->setupUi(this);
    cout<<"Current Thread is "<<QThread::currentThread();
    dinInit();
}

dinForm::~dinForm()
{
    delete ui;
}

void dinForm::on_dibackButton_clicked()
{
    backTimer->stop();
    workerTime->stopWorker();

    emit showMain();

    this->close();

}

void dinForm::dinInit(){

    GPIOUnexport(127); //PD31
    GPIOUnexport(69);  //PC5
    GPIOUnexport(43);   //PB11
    GPIOUnexport(105);  // PD9
    GPIOUnexport(103);  //PD7
    GPIOUnexport(107);  //PD11
    GPIOUnexport(102);  //PD6
    GPIOUnexport(56);   //PB24

    GPIOExport(127); //PD31
    GPIOExport(69);  //PC5
    GPIOExport(43);   //PB11
    GPIOExport(105);  // PD9
    GPIOExport(103);  //PD7
    GPIOExport(107);  //PD11
    GPIOExport(102);  //PD6
    GPIOExport(56);   //PB24

    GPIODirection("PD31",IN);
    GPIODirection("PC5",IN);
    GPIODirection("PB11",IN);
    GPIODirection("PD9",IN);
    GPIODirection("PD7",IN);
    GPIODirection("PD11",IN);
    GPIODirection("PD6",IN);
    GPIODirection("PB24",IN);

    // New additions

     GPIOUnexport(72); //PC8
     GPIOExport(72);   //PC8
     GPIODirection("PC8",IN);

     GPIOUnexport(104); //PD8
     GPIOExport(104);   //PD8
     GPIODirection("PD8",IN);


}

void dinForm::dinReader(){

    int value;
    value=GPIORead("PD31"); //DI-1
    if(value==1)
        ui->lineEdit_emergency->setText("OFF");
    else
        ui->lineEdit_emergency->setText("ON");

    value=GPIORead("PC5"); //DI-2
    if(value==1)
        ui->lineEdit_on_off->setText("OFF");
    else
        ui->lineEdit_on_off->setText("ON");


    value=GPIORead("PB11"); //DI-3
    if(value==1)
        ui->lineEdit_nz1_lifted->setText("Lifted"); // Newly inverted Logic
    else
        ui->lineEdit_nz1_lifted->setText("Not Lifted");

    value=GPIORead("PD9"); //DI-5
    if(value==1)
        ui->lineEdit_spd_alarm->setText("No SPD");
    else
        ui->lineEdit_spd_alarm->setText("SPD Alarm");

    value=GPIORead("PD7"); //DI-6
    if(value==1)
        ui->lineEdit_smoke->setText("No Smoke");
    else
        ui->lineEdit_smoke->setText("Smoke");

    value=GPIORead("PD11"); //DI-7
    if(value==1)
        ui->lineEdit_nzl1_locking->setText("No lock");
    else
        ui->lineEdit_nzl1_locking->setText("locked");

    value=GPIORead("PD6");
    if(value==1)
        ui->lineEdit_insulation->setText("OFF");
    else
        ui->lineEdit_insulation->setText("ON");


    value=GPIORead("PB24");
    if(value==1)
        ui->lineEdit_leakage->setText("OFF");
    else
        ui->lineEdit_leakage->setText("ON");

    // New additions

    value=GPIORead("PC8");
    if(value==1)
        ui->lineEdit_evConnection->setText("Not Connected");
    else
        ui->lineEdit_evConnection->setText("Connected");

    value=GPIORead("PD8");
    if(value==1)
        ui->lineEdit_vld->setText("LOW");
    else
        ui->lineEdit_vld->setText("HIGH");


   cout<<"Current Thread is-> "<<QThread::currentThread();
}

void dinForm::on_readDinNowButton_clicked()
{
    dinReader();
}

void dinForm::on_startDinButton_clicked()
{
        backTimethead = new QThread();
        backTimer = new QTimer();
        workerTime = new worker();


        connect(backTimer, SIGNAL(timeout()),workerTime, SLOT(updateDins()));
        connect(workerTime, SIGNAL(updateDinUi_Signal(int*)),this, SLOT(updatedinUi(int*)));

        /////////////////////////////////////////////////////////////////////
        //connect(workerTime, SIGNAL(finished()),backTimer ,SLOT(stop()));
        connect(workerTime,SIGNAL(finished()),backTimethead,SLOT(quit()));
        connect(workerTime,SIGNAL(finished()),backTimer, SLOT(deleteLater()));
        connect(workerTime,SIGNAL(finished()),workerTime,SLOT(deleteLater()));
        connect(backTimethead, SIGNAL(finished()), backTimethead, SLOT(deleteLater()));
        connect(backTimethead, SIGNAL(finished()),this, SLOT(threadDone()));
        /////////////////////////////////////////////////////////////////
        backTimer->start(1000);

        workerTime->moveToThread(backTimethead);

        // This ensures that timeout is called from worker thread
       // backTimer->moveToThread(backTimethead); // this must be called after timer is started

        backTimethead->start();

}

void dinForm::on_stopDinButton_clicked()
{
    backTimer->stop();
    workerTime->stopWorker();
}

void dinForm::threadDone(){

     qDebug("Thread is done");
}

void dinForm::updatedinUi(int *dinValues){

    if(dinValues[0]==1)
        ui->lineEdit_emergency->setText("OFF");
    else
        ui->lineEdit_emergency->setText("ON");

    if(dinValues[1]==1)
        ui->lineEdit_on_off->setText("OFF");
    else
        ui->lineEdit_on_off->setText("ON");

    // Inverted Login new
    if(dinValues[2]==1)
        ui->lineEdit_nz1_lifted->setText("Lifted");
    else
        ui->lineEdit_nz1_lifted->setText("Not Lifted");

    if(dinValues[3]==1)
        ui->lineEdit_spd_alarm->setText("No SPD");
    else
        ui->lineEdit_spd_alarm->setText("SPD Alarm");

    if(dinValues[4]==1)
        ui->lineEdit_smoke->setText("No Smoke");
    else
        ui->lineEdit_smoke->setText("Smoke");

    if(dinValues[5]==1)
        ui->lineEdit_nzl1_locking->setText("No lock");
    else
        ui->lineEdit_nzl1_locking->setText("locked");

    if(dinValues[6]==1)
        ui->lineEdit_insulation->setText("OFF");
    else
        ui->lineEdit_insulation->setText("ON");

    if(dinValues[7]==1)
        ui->lineEdit_leakage->setText("OFF");
    else
        ui->lineEdit_leakage->setText("ON");

    // Newly added
    if(dinValues[8]==1)
        ui->lineEdit_evConnection->setText("Not Connected");
    else
        ui->lineEdit_evConnection->setText("Connected");

    if(dinValues[9]==1)
        ui->lineEdit_vld->setText("LOW");
    else
        ui->lineEdit_vld->setText("HIGH");
}
