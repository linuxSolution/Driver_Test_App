#ifndef RECTIFIERWORKER_H
#define RECTIFIERWORKER_H

#include <QObject>

class rectifierWorker : public QObject
{
    Q_OBJECT
public:
    rectifierWorker();
    ~rectifierWorker();

signals:
   void finished(); // This is a custom signal

public slots:

   void refereshVoltageCurrent();
};

#endif // RECTIFIERWORKER_H
