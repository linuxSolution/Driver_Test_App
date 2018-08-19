#ifndef WORKER_H
#define WORKER_H

#include <QtCore>
#include <QTimer>
#include <QString>
#include <stdint.h>

class worker : public QObject
{
    Q_OBJECT
public:
   worker();
    ~worker();
   void stopWorker();

signals:
   void finished(); // This is a custom signal
   void updateDinUi_Signal(int *dins);

public slots:

   void updateDins();

};
#endif // WORKER_H
