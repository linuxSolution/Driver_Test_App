#include "worker.h"

#include "gpi.h"

worker::worker()
{

}

worker::~worker()
{
    // do nothing
    qDebug("Destroying Worker");
}

void worker::stopWorker(){

    emit finished();
}

void worker::updateDins(){

    int value[8 + 2];                             // added 2 more
    value[0]=GPIORead("PD31"); //DI-1
    value[1]=GPIORead("PC5"); //DI-2
    value[2]=GPIORead("PB11"); //DI-3
    value[3]=GPIORead("PD9"); //DI-5
    value[4]=GPIORead("PD7"); //DI-6
    value[5]=GPIORead("PD11"); //DI-7
    value[6]=GPIORead("PD6");
    value[7]=GPIORead("PB24");

    // newly added

    value[8] = GPIORead("PC8");
    value[9] = GPIORead("PD8");

    emit updateDinUi_Signal(value);
}

