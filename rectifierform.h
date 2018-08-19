#ifndef RECTIFIERFORM_H
#define RECTIFIERFORM_H

#include <QWidget>
#include <QString>

#include <QThread>
#include <QTimer>
#include "rectifierworker.h"

namespace Ui {
class rectifierForm;
}

class rectifierForm : public QWidget
{
    Q_OBJECT

public:
    explicit rectifierForm(QWidget *parent = 0);
    ~rectifierForm();

    void setText(QString str);

private:
    Ui::rectifierForm *ui;

    unsigned char rect_volt_selected=1;
    unsigned char rect_cur_selected=0;
    unsigned char rect_volt_select_complete=0;
    unsigned char  rect_cur_select_complete=0;

    QThread *backTimethead;
    QTimer *backTimer;
    rectifierWorker *workerTime;

signals:
    void showMain();
private slots:
    void on_rectifierbackButton_clicked();
    void on_selectButton_clicked();
    void on_oneButton_clicked();
    void on_twoButton_clicked();
    void on_threeButton_clicked();
    void on_fourButton_clicked();
    void on_fiveButton_clicked();
    void on_sixButton_clicked();
    void on_sevenButton_clicked();
    void on_eightButton_clicked();
    void on_nineButton_clicked();
    void on_zeroButton_clicked();
    void on_resetButton_clicked();
    void on_rectifierSettingButton_clicked();
};

#endif // RECTIFIERFORM_H
