#ifndef DOUTFORM_H
#define DOUTFORM_H

#include <QWidget>

namespace Ui {
class doutForm;
}

class doutForm : public QWidget
{
    Q_OBJECT

public:
    explicit doutForm(QWidget *parent = 0);
    ~doutForm();

    void doutinit();

private slots:

    void on_dobackButton_clicked();

    void on_inputContactor_Button_clicked();

    void on_fanButton_clicked();

    void on_noselLockButton_clicked();

    void on_nozelUnlockButton_clicked();

    void on_lvd1Button_clicked();

    void on_lvd2Button_clicked();

private:
    Ui::doutForm *ui;

signals:

    void showMain();

};

#endif // DOUTFORM_H
