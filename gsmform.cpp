#include "gsmform.h"
#include "ui_gsmform.h"
#include "gsmhelper.h"

gsmForm::gsmForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gsmForm)
{
    ui->setupUi(this);
}

gsmForm::~gsmForm()
{
    delete ui;
}

void gsmForm::on_gsmbackButton_clicked()
{
    emit showMain();

    this->close();
}

void gsmForm::on_gsmButton_clicked()
{
    check_ppp_connection();

    if(ppp_status==1)
    {
        ui->gsmLineEdit->append("GSM PPP connection is OK and up");

        if (system("ping -c1 -s1 www.google.com"))
        {

            ui->gsmLineEdit->append("Unable to ping www.google.com -I ppp0");
        }

        else
        {
            ui->gsmLineEdit->append("ping www.google.com successful");
        }

    }

    if(ppp_status==0)
    {
        ui->gsmLineEdit->append("GSM PPP connection is down");
    }


    if(ppp_status==2)
    {
        ui->gsmLineEdit->append("GSM PPP is UP but Network is down");
    }

}
