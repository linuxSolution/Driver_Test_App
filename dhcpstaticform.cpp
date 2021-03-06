#include "dhcpstaticform.h"
#include "ui_dhcpstaticform.h"

#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

dhcpstaticForm::dhcpstaticForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dhcpstaticForm)
{
    ui->setupUi(this);
}

dhcpstaticForm::~dhcpstaticForm()
{
    delete ui;
}

void dhcpstaticForm::on_dhcpbackButton_clicked()
{
    emit showMain();

    this->close();
}

void dhcpstaticForm::on_staticButton_clicked()
{
    QString filename = "/home/delta/QtProjects/Revised_Qt_App_rectifierGui_7/interfaces";
    QFile networkFile(filename);

    if(!networkFile.open(QFile::WriteOnly |QFile::Text)){
        qDebug()<<"Could not open file";
        return;
    }

    QTextStream out(&networkFile);

    QString toWrite= "# interface file auto-generated by buildroot\n\n" \
                     "auto lo\n"\
                     "iface lo inet loopback\n\n";

    QString staticIP = ui->staticLineEdit->text();
    QString subnetMask = ui->subnetLineEdit->text();
    QString gateway = ui->gatewayLineEdit->text();

    QString fin ="auto eth0\n" \
    "iface eth0 inet static\n" \
    "address" + staticIP+"\n" \
    "gateway" + gateway+"\n" \
    "netmask" + subnetMask+"\n" \
    "dns-nameservers 8.8.8.8 8.8.4.4";

    QString final = toWrite + fin;

    out<<final;
    networkFile.flush();
    networkFile.close();
}

void dhcpstaticForm::on_dhcpButton_clicked()
{
    QString filename = "/home/delta/QtProjects/Revised_Qt_App_rectifierGui_7/interfaces";
    QFile networkFile(filename);

    if(!networkFile.open(QFile::WriteOnly |QFile::Text)){
        qDebug()<<"Could not open file";
        return;
    }

    QTextStream out(&networkFile);

    QString toWrite= "# interface file auto-generated by buildroot\n\n" \
                     "auto lo\n"\
                     "iface lo inet loopback\n\n"\
                    "auto eth0\n"\
                    "iface eth0 inet dhcp\n";

    out<<toWrite;

    networkFile.flush();
    networkFile.close();
}
