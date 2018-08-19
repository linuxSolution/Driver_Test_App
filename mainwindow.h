#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "doutform.h"
#include "ledconlroleform.h"
#include "dinform.h"
#include "canform.h"
#include "ethernetform.h"
#include "gsmform.h"
#include "rectifierform.h"
#include "dhcpstaticform.h"
#include "cmsconfigform.h"
#include "emeterform.h"
#include "adcext.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_doutButton_clicked();

    void on_mainexitButton_clicked();

    void on_ledButton_clicked();

    void showMain();

    void on_dinButton_clicked();

    void on_canButton_clicked();

    void on_ethernetButton_clicked();

    void on_gsmButton_clicked();

    void on_rectifierButton_clicked();

    void on_dhcpButton_clicked();

    void on_cmsconfigButton_clicked();

    void on_emeterButton_clicked();

    void on_adcExtButton_clicked();


private:
    Ui::MainWindow *ui;
    doutForm *dform;
    ledConlroleForm *ledform;
    dinForm *dinform;
    canForm *canform;
    ethernetForm *ethernetform;
    gsmForm *gsmform;
    rectifierForm *rectifierform;
    dhcpstaticForm *dhcpstaticform;
    cmsConfigform *cmsConfigForm;
    emeterForm *emeterform;
    adcExt *adcExtform;

    void readAdcSql();
};

#endif // MAINWINDOW_H
