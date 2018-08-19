#ifndef DHCPSTATICFORM_H
#define DHCPSTATICFORM_H

#include <QWidget>

namespace Ui {
class dhcpstaticForm;
}

class dhcpstaticForm : public QWidget
{
    Q_OBJECT

public:
    explicit dhcpstaticForm(QWidget *parent = 0);
    ~dhcpstaticForm();

private:
    Ui::dhcpstaticForm *ui;

signals:
    void showMain();
private slots:
    void on_dhcpbackButton_clicked();
    void on_staticButton_clicked();
    void on_dhcpButton_clicked();
};

#endif // DHCPSTATICFORM_H
