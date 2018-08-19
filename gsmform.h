#ifndef GSMFORM_H
#define GSMFORM_H

#include <QWidget>

namespace Ui {
class gsmForm;
}

class gsmForm : public QWidget
{
    Q_OBJECT

public:
    explicit gsmForm(QWidget *parent = 0);
    ~gsmForm();

private slots:
    void on_gsmbackButton_clicked();

    void on_gsmButton_clicked();

private:
    Ui::gsmForm *ui;

signals:
    void showMain();
};

#endif // GSMFORM_H
