#include "emeterform.h"
#include "ui_emeterform.h"
#include "mbushelper.h"

#include <QString>

emeterForm::emeterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::emeterForm)
{
    ui->setupUi(this);
    initialize_modbus();
}

emeterForm::~emeterForm()
{
    delete ui;
}

void emeterForm::on_emeterbackButton_clicked()
{
    emit showMain();
    this->close();
}

void emeterForm::on_readButton_clicked()
{
    modbus_meter_reading();

    int x=rvolt;
    int y=bvolt;
    int z=yvolt;

    ui->lineEdit_RVoltage->setText(QString::number(x));

    ui->lineEdit_BVoltage->setText(QString::number(y));

    ui->lineEdit_YVoltage->setText(QString::number(z));

    ui->lineEdit_Frequency->setText(QString::number(freq));

    ui->lineEdit_KWH->setText(QString::number(kwh));
}
