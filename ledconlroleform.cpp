#include "ledconlroleform.h"
#include "ui_ledconlroleform.h"
#include "gpio.h"
#include "gpo.h"

ledConlroleForm::ledConlroleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ledConlroleForm)
{
    ui->setupUi(this);
    ledoutinit();
}

ledConlroleForm::~ledConlroleForm()
{
    delete ui;
}


void ledConlroleForm::on_ledbackButton_clicked()
{
    emit showMain();
    this->close();
}

void ledConlroleForm::on_led1Button_clicked()
{
    if(ui->led1Button->isChecked()){

        ui->led1Button->setText("ON");
        GPIOWrite("PD14",HIGH);
    }else{
        ui->led1Button->setText("OFF");
        GPIOWrite("PD14",LOW);
    }
}

void ledConlroleForm::on_led2Button_clicked()
{
    if(ui->led2Button->isChecked()){

        ui->led2Button->setText("ON");
        GPIOWrite("PD15",HIGH);
    }else{
        ui->led2Button->setText("OFF");
        GPIOWrite("PD15",LOW);
    }
}

void ledConlroleForm::on_led3Button_clicked()
{
    if(ui->led3Button->isChecked()){

        ui->led3Button->setText("ON");
        GPIOWrite("PD16",HIGH);
    }else{
        ui->led3Button->setText("OFF");
        GPIOWrite("PD16",LOW);
    }
}

void ledConlroleForm::on_led4Button_clicked()
{
    if(ui->led4Button->isChecked()){

        ui->led4Button->setText("ON");
        GPIOWrite("PD17",HIGH);
    }else{
        ui->led4Button->setText("OFF");
        GPIOWrite("PD17",LOW);
    }
}

void ledConlroleForm::ledoutinit(){

    GPIOUnexport(110); //PD14
    GPIOUnexport(111); //PD15
    GPIOUnexport(112); //PD16
    GPIOUnexport(113); //PD17

    GPIOExport(110); //PD14
    GPIOExport(111); //PD15
    GPIOExport(112); //PD16
    GPIOExport(113); //PD17

    GPIODirection("PD14",OUT);
    GPIODirection("PD15",OUT);
    GPIODirection("PD16",OUT);
    GPIODirection("PD17",OUT);

}
