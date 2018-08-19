#include "cmsconfigform.h"
#include "ui_cmsconfigform.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QMessageBox>


cmsConfigform::cmsConfigform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cmsConfigform)
{
    ui->setupUi(this);
}

cmsConfigform::~cmsConfigform()
{
    delete ui;
}

void cmsConfigform::on_cmsbackButton_clicked()
{
    emit showMain();
    this->close();
}

void cmsConfigform::on_saveButton_clicked()
{
    QString filename = "/home/delta/QtProjects/Revised_Qt_App_rectifierGui_7/cmsConfig";
    QFile cmsConfig(filename);

    if(!cmsConfig.open(QFile::WriteOnly |QFile::Text)){

        QMessageBox::about(this,"Error","Could not open the file");
        return;
    }

    QTextStream out(&cmsConfig);

    QString serverIP = ui->lineEdit_server_ip->text();
    QString serverPort = ui->lineEdit_server_port->text();
    QString serverPath = ui->lineEdit_server_path->text();
    QString chargeBoxSerial = ui->lineEdit_cb_ser_num->text();
    QString chagePointSerial = ui->lineEdit_cp_ser_no->text();
    QString chagePointModel = ui->lineEdit_cp_model_no->text();
    QString changePoinVendor = ui->lineEdit_cp_vendor_id->text();
    QString firmwareVer = ui->lineEdit_firmware->text();
    QString iccid = ui->lineEdit_iccid->text();
    QString imsi = ui->lineEdit_imsi->text();
    QString meterSno = ui->lineEdit_mtr_ser_num->text();
    QString meterType = ui->comboBox_mtr_type->currentText();
    QString inMinvolt = ui->lineEdit_input_min_volt->text();
    QString inMaxvolt = ui->lineEdit_input_max_volt->text();
    QString nozMaxtemp = ui->lineEdit_nozzle_max_temp->text();

    QString fin =  \
            "ocpp_server_ip="+serverIP+"\n" \
            "ocpp_server_port="+serverPort+"\n" \
            "ocpp_server_path="+serverPath+"\n" \
            "cbox_ser_no="+chargeBoxSerial+"\n" \
            "cpoint_ser_no="+chagePointSerial+"\n" \
            "cpoint_vendor_id=" +changePoinVendor+"\n" \
            "iccid=" +iccid +"\n"\
            "imsi=" +imsi+"\n"\
            "meter_ser_no=" +meterSno+"\n"\
            "input_min_voltage=" +inMinvolt+"\n"\
            "input_max_voltage=" +inMaxvolt+"\n"\
            "cpoint_model_no=" + chagePointModel+"\n"\
            "nozzle_max_temp=" +nozMaxtemp+"\n"\
            "firmware_ver="+ firmwareVer+"\n"\
            "meter_type="+meterType+"\n";

    out<<fin;
    cmsConfig.flush();
    cmsConfig.close();

    QMessageBox::about(this,"Sucess","Connfiguration saved");

}
