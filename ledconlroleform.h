#ifndef LEDCONLROLEFORM_H
#define LEDCONLROLEFORM_H

#include <QWidget>

namespace Ui {
class ledConlroleForm;
}

class ledConlroleForm : public QWidget
{
    Q_OBJECT

public:
    explicit ledConlroleForm(QWidget *parent = 0);
    ~ledConlroleForm();

    void ledoutinit();

private slots:


    void on_ledbackButton_clicked();

    void on_led1Button_clicked();

    void on_led2Button_clicked();

    void on_led3Button_clicked();

    void on_led4Button_clicked();

private:
    Ui::ledConlroleForm *ui;

signals:

    void showMain();

};

#endif // LEDCONLROLEFORM_H
