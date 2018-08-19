#ifndef CMSCONFIGFORM_H
#define CMSCONFIGFORM_H

#include <QWidget>

namespace Ui {
class cmsConfigform;
}

class cmsConfigform : public QWidget
{
    Q_OBJECT

public:
    explicit cmsConfigform(QWidget *parent = 0);
    ~cmsConfigform();

private:
    Ui::cmsConfigform *ui;

signals:

    void showMain();
private slots:
    void on_cmsbackButton_clicked();
    void on_saveButton_clicked();
};

#endif // CMSCONFIGFORM_H
