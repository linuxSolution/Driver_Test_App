#include "doutform.h"
#include "ui_doutform.h"

#include "gpio.h"
#include "gpo.h"

doutForm::doutForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doutForm)
{
    ui->setupUi(this);
    doutinit();
}

doutForm::~doutForm()
{
    delete ui;
}

void doutForm::on_dobackButton_clicked()
{
    emit showMain();
    this->close();
}

void doutForm::on_inputContactor_Button_clicked()
{
    if(ui->inputContactor_Button->isChecked()){

        ui->inputContactor_Button->setText("ON");

        GPIOWrite("PB4",HIGH);

    }else{
        ui->inputContactor_Button->setText("OFF");
        GPIOWrite("PB4",LOW);
    }

}

void doutForm::on_fanButton_clicked()
{
    if(ui->fanButton->isChecked()){

        ui->fanButton->setText("ON");
        GPIOWrite("PB9",HIGH);

    }else{
        ui->fanButton->setText("OFF");
        GPIOWrite("PB9",LOW);
    }
}

void doutForm::on_noselLockButton_clicked()
{
    if(ui->noselLockButton->isChecked()){

        ui->noselLockButton->setText("ON");
        GPIOWrite("PA24",HIGH);

    }else{
        ui->noselLockButton->setText("OFF");
        GPIOWrite("PA24",LOW);
    }
}

void doutForm::on_nozelUnlockButton_clicked()
{
    if(ui->nozelUnlockButton->isChecked()){

        ui->nozelUnlockButton->setText("ON");
        GPIOWrite("PA25",HIGH);

    }else{
        ui->nozelUnlockButton->setText("OFF");
         GPIOWrite("PA25",LOW);
    }
}

void doutForm::on_lvd1Button_clicked()
{
    if(ui->lvd1Button->isChecked()){

        ui->lvd1Button->setText("ON");
        GPIOWrite("PD2",HIGH);
    }else{
        ui->lvd1Button->setText("OFF");
        GPIOWrite("PD2",LOW);
    }
}

void doutForm::on_lvd2Button_clicked()
{
    if(ui->lvd2Button->isChecked()){

        ui->lvd2Button->setText("ON");
        GPIOWrite("PD3",HIGH);

    }else{
        ui->lvd2Button->setText("OFF");
         GPIOWrite("PD3",LOW);
    }
}

void doutForm::doutinit(){

    GPIOUnexport(36); //PB4
    GPIOUnexport(41); //PB9
    GPIOUnexport(24); //PA24
    GPIOUnexport(25); //PA25
    GPIOUnexport(98); //PD2
    GPIOUnexport(99); //PD3

    GPIOExport(36); //PB4
    GPIOExport(41); //PB9
    GPIOExport(24); //PA24
    GPIOExport(25); //PA25
    GPIOExport(98); //PD2
    GPIOExport(99); //PD3

    GPIODirection("PB4",OUT);
    GPIODirection("PB9",OUT);
    GPIODirection("PA24",OUT);
    GPIODirection("PA25",OUT);
    GPIODirection("PD2",OUT);
    GPIODirection("PD3",OUT);

}
