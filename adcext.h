#ifndef ADCEXT_H
#define ADCEXT_H

#include <QWidget>

namespace Ui {
class adcExt;
}

class adcExt : public QWidget
{
    Q_OBJECT

public:
    explicit adcExt(QWidget *parent = 0);
    ~adcExt();

private slots:
    void on_adcExtbackButton_clicked();

    void on_readAdcButton_clicked();

    void readAdcSql();

private:
    Ui::adcExt *ui;
    float scale;

signals:
    void showMain();
};

#endif // ADCEXT_H
