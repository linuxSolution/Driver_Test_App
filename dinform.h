#ifndef DINFORM_H
#define DINFORM_H

#include <QWidget>
#include <qtimer.h>
#include "worker.h"

namespace Ui {
class dinForm;
}

class dinForm : public QWidget
{
    Q_OBJECT

public:
    explicit dinForm(QWidget *parent = 0);
    ~dinForm();

    void dinInit();


private slots:
    void on_dibackButton_clicked();

    void on_readDinNowButton_clicked();

    void on_startDinButton_clicked();

    void dinReader();

    void on_stopDinButton_clicked();

    /**
     * @brief threadDone
     * it is called when thread is about to delete
     */

    void threadDone();

    void updatedinUi(int *dinValues);

private:

    Ui::dinForm *ui;

    QThread *backTimethead;
    QTimer *backTimer;
    worker *workerTime;

signals:

    void showMain();
};

#endif // DINFORM_H
