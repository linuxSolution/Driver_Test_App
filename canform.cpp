#include "canform.h"
#include "ui_canform.h"
#include "canhelper.h"

canForm::canForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::canForm)
{
    system("ip link set can0 up type can bitrate 250000");
    open_port("can0");
    ui->setupUi(this);
}

canForm::~canForm()
{
    delete ui;
}

void canForm::on_canbackButton_clicked()
{
    emit showMain();

    this->close();
}

void canForm::on_readCanNowButton_clicked()
{
    CanFrameReceived=read_port();

     for(int i=0;i<CanFrameReceived.can_dlc;i++)
      {
          ui->canoutTextEdit->appendPlainText(QString::number(CanFrameReceived.data[i]));
      }
}

void canForm::on_sendCanNowButton_clicked()
{
    CanFrameForSending.can_dlc=8;
    CanFrameForSending.can_id=456;
    CanFrameForSending.data[0]=45;
    CanFrameForSending.data[1]=55;
    CanFrameForSending.data[2]=65;
    CanFrameForSending.data[3]=75;
    CanFrameForSending.data[4]=85;
    CanFrameForSending.data[5]=95;
    CanFrameForSending.data[6]=25;
    CanFrameForSending.data[7]=35;

    send_port(&CanFrameForSending);
}
