#ifndef ETHERNETFORM_H
#define ETHERNETFORM_H

#include <QWidget>

namespace Ui {
class ethernetForm;
}

class ethernetForm : public QWidget
{
    Q_OBJECT

public:
    explicit ethernetForm(QWidget *parent = 0);
    ~ethernetForm();

private slots:
    void on_etherbackButton_clicked();

    void on_ethernetButton_clicked();

private:
    Ui::ethernetForm *ui;

signals:
    void showMain();
};

#endif // ETHERNETFORM_H
