#include "ethernetform.h"
#include "ui_ethernetform.h"
#include "ethernethelper.h"

ethernetForm::ethernetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ethernetForm)
{
    ui->setupUi(this);
}

ethernetForm::~ethernetForm()
{
    delete ui;
}

void ethernetForm::on_etherbackButton_clicked()
{
    emit showMain();

    this->close();
}

void ethernetForm::on_ethernetButton_clicked()
{
    check_ethernet_connection();

    if(ethernet_status==1)
    {
        ui->ethernetLineEdit->append("Ethernet connection is OK and up");

        if (system("ping -c1 -s1 www.google.com -I eth0"))
        {
            ui->ethernetLineEdit->append("Unable to ping www.google.com");
        }

        else
        {
            ui->ethernetLineEdit->append("ping www.google.com successful");
        }
    }

    if(ethernet_status==0)
    {
        ui->ethernetLineEdit->append("Ethernet connection is down");
    }

}
