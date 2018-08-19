#include "rectifierform.h"
#include "ui_rectifierform.h"

#include <QMessageBox>
#include "rectifierhelper.h"

rectifierForm::rectifierForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rectifierForm)
{
    ui->setupUi(this);
    spidev_initialize();

}

rectifierForm::~rectifierForm()
{
    delete ui;
}

void rectifierForm::on_rectifierbackButton_clicked()
{
    emit showMain();

    this->close();
}

void rectifierForm::on_selectButton_clicked()
{
    if(ui->selectButton->isChecked()){

        ui->selectButton->setText("VOLT");
        ui->volt_LineEdit->setFocus();

    }else{

        ui->selectButton->setText("CRNT");
        ui->current_LineEdit->setFocus();
    }

}

void rectifierForm::setText(QString str)
{
    QString readString;

    if(ui->selectButton->isChecked()){

        readString = ui->volt_LineEdit->text();
        readString = readString +str;
        ui->volt_LineEdit->setText(readString);

    }else{

        readString = ui->current_LineEdit->text();
        readString = readString +str;
        ui->current_LineEdit->setText(readString);
    }
}

void rectifierForm::on_oneButton_clicked()
{
    setText("1");

}

void rectifierForm::on_twoButton_clicked()
{
     setText("2");
}

void rectifierForm::on_threeButton_clicked()
{
    setText("3");
}

void rectifierForm::on_fourButton_clicked()
{
    setText("4");
}

void rectifierForm::on_fiveButton_clicked()
{
    setText("5");
}

void rectifierForm::on_sixButton_clicked()
{
    setText("6");
}

void rectifierForm::on_sevenButton_clicked()
{
    setText("7");
}

void rectifierForm::on_eightButton_clicked()
{
    setText("8");
}

void rectifierForm::on_nineButton_clicked()
{
    setText("9");
}

void rectifierForm::on_zeroButton_clicked()
{
    setText("0");
}

void rectifierForm::on_resetButton_clicked()
{
    ui->volt_LineEdit->setText("");
    ui->current_LineEdit->setText("");

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::white);
    palette->setColor(QPalette::Text,Qt::black);
    ui->volt_LineEdit->setPalette(*palette);
    ui->current_LineEdit->setPalette(*palette);
}

void rectifierForm::on_rectifierSettingButton_clicked()
{
    QString stringTemp=ui->volt_LineEdit->text();

    int voltage=stringTemp.toInt();

    stringTemp=ui->current_LineEdit->text();

    int current=stringTemp.toInt();

    if((voltage<0)||(voltage>110)||(ui->volt_LineEdit->text().isEmpty()))
    {
        QMessageBox::warning(this,"Rectifier Voltage", "Volatge should be between 0V and 110V");
        ui->volt_LineEdit->setText("");
    }

    if((current<0)||(current>210)||(ui->volt_LineEdit->text().isEmpty()))
    {
        QMessageBox::warning(this,"Rectifier Current", "Current should be between 0A and 200 A");
        ui->current_LineEdit->setText("");
    }

    rect_volt_selected=0;
    rect_cur_selected=0;
    rect_volt_select_complete=1;
    rect_cur_select_complete=1;

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::gray);
    palette->setColor(QPalette::Text,Qt::darkGray);
    ui->volt_LineEdit->setPalette(*palette);
    ui->current_LineEdit->setPalette(*palette);

    int volt_16bit=voltage*100;
    int cur_16bit=current*10;

    unsigned char hexaDeciNum[100];
    unsigned char volt_hex[100];

    char volt_hexval[5];
    sprintf(volt_hexval,"0x%x",volt_16bit);

    uint16_t result;

    result = strtol(volt_hexval,NULL,16);

    uint8_t  volt_bytes[2];

    volt_bytes[0] = result >> 8;     // high byte (0x12)
    volt_bytes[1] = result & 0x00FF;

    int volt_higher=(int)volt_bytes[0];
    int volt_lower=(int)volt_bytes[1];

    char cur_hexval[5];
    sprintf(cur_hexval,"0x%x",cur_16bit);

    result = strtol(cur_hexval,NULL,16);

    uint8_t  cur_bytes[2];

    cur_bytes[0] = result >> 8;     // high byte (0x12)
    cur_bytes[1] = result & 0x00FF;

    int cur_higher=cur_bytes[0];
    int cur_lower=cur_bytes[1];

    tx[2]=volt_lower;
    tx[3]=volt_higher;
    tx[4]=cur_lower;
    tx[5]=cur_higher;

//    for(int i = 0 ; i <4;i++){

//        transfer(fd_rect);
//    }

    backTimethead = new QThread();
    backTimer = new QTimer();
    workerTime = new rectifierWorker();


    connect(backTimer, SIGNAL(timeout()),workerTime, SLOT(refereshVoltageCurrent()));


    /////////////////////////////////////////////////////////////////////
    //connect(workerTime, SIGNAL(finished()),backTimer ,SLOT(stop()));
    connect(workerTime,SIGNAL(finished()),backTimethead,SLOT(quit()));
    connect(workerTime,SIGNAL(finished()),backTimer, SLOT(deleteLater()));
    connect(workerTime,SIGNAL(finished()),workerTime,SLOT(deleteLater()));
    connect(backTimethead, SIGNAL(finished()), backTimethead, SLOT(deleteLater()));

    /////////////////////////////////////////////////////////////////
    backTimer->start(1000);

    workerTime->moveToThread(backTimethead);

    // This ensures that timeout is called from worker thread
   // backTimer->moveToThread(backTimethead); // this must be called after timer is started

    backTimethead->start();

}
