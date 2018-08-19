#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_doutButton_clicked()
{
    dform = new doutForm();

    connect(dform,SIGNAL(showMain()),this,SLOT(showMain()));
    dform->show();
    this->hide();
}

void MainWindow::on_mainexitButton_clicked()
{
    this->close();
}


void MainWindow::on_ledButton_clicked()
{
    //qDebug("hello");
    ledform = new ledConlroleForm();
    connect(ledform,SIGNAL(showMain()),this,SLOT(showMain()));
    ledform->setMinimumSize(800,480);
    ledform->show();
    this->hide();
}

 void MainWindow::showMain()
 {
    this->show();
 }

void MainWindow::on_dinButton_clicked()
{
    dinform = new dinForm();
    connect(dinform,SIGNAL(showMain()),this,SLOT(showMain()));
    dinform->setMinimumSize(800,480);
    dinform->show();
    this->hide();
}

void MainWindow::on_canButton_clicked()
{
    canform = new canForm();
    connect(canform,SIGNAL(showMain()),this,SLOT(showMain()));
    canform->setMinimumSize(800,480);
    canform->show();
    this->hide();
}

void MainWindow::on_ethernetButton_clicked()
{
    this->ethernetform = new ethernetForm();
    connect(ethernetform,SIGNAL(showMain()),this,SLOT(showMain()));
    ethernetform->setMinimumSize(800,480);
    ethernetform->show();
    this->hide();

}

void MainWindow::on_gsmButton_clicked()
{
    this->gsmform = new gsmForm();
    connect(gsmform,SIGNAL(showMain()),this,SLOT(showMain()));
    gsmform->setMinimumSize(800,480);
    gsmform->show();
    this->hide();
}

void MainWindow::on_rectifierButton_clicked()
{
    this->rectifierform = new rectifierForm();
    connect(rectifierform,SIGNAL(showMain()),this,SLOT(showMain()));
    rectifierform->setMinimumSize(800,480);
    rectifierform->show();
    this->hide();
}

void MainWindow::on_dhcpButton_clicked()
{
    this->dhcpstaticform = new dhcpstaticForm();
    connect(dhcpstaticform,SIGNAL(showMain()),this,SLOT(showMain()));
    dhcpstaticform->show();
    this->hide();
}

void MainWindow::on_cmsconfigButton_clicked()
{
     this->cmsConfigForm = new cmsConfigform();
     connect(cmsConfigForm,SIGNAL(showMain()),this,SLOT(showMain()));
     cmsConfigForm->show();
     this->hide();
}

void MainWindow::on_emeterButton_clicked()
{
    this->emeterform = new emeterForm();
    connect(emeterform,SIGNAL(showMain()),this,SLOT(showMain()));
    emeterform->setMinimumSize(800,480);
    emeterform->show();
    this->hide();
}

void MainWindow::on_adcExtButton_clicked()
{
    this->adcExtform = new adcExt();
    connect(adcExtform,SIGNAL(showMain()),this,SLOT(showMain()));
    adcExtform->setMinimumSize(800,480);
    adcExtform->show();
    this->hide();
}

