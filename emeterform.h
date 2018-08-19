#ifndef EMETERFORM_H
#define EMETERFORM_H

#include <QWidget>

namespace Ui {
class emeterForm;
}

class emeterForm : public QWidget
{
    Q_OBJECT

public:
    explicit emeterForm(QWidget *parent = 0);
    ~emeterForm();

private:
    Ui::emeterForm *ui;

signals:

    void showMain();
private slots:
    void on_emeterbackButton_clicked();
    void on_readButton_clicked();
};

#endif // EMETERFORM_H
