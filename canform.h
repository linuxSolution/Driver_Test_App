#ifndef CANFORM_H
#define CANFORM_H

#include <QWidget>

#include <linux/can.h>
#include <linux/can/raw.h>

namespace Ui {
class canForm;
}

class canForm : public QWidget
{
    Q_OBJECT

public:
    explicit canForm(QWidget *parent = 0);
    ~canForm();

private slots:
    void on_canbackButton_clicked();

    void on_readCanNowButton_clicked();

    void on_sendCanNowButton_clicked();

private:
    Ui::canForm *ui;
    struct can_frame CanFrameForSending;
    struct can_frame CanFrameReceived;

signals:

    void showMain();

};

#endif // CANFORM_H
