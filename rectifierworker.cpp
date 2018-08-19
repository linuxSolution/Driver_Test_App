#include "rectifierworker.h"

#include "rectifierhelper.h"

#include <QThread>

rectifierWorker::rectifierWorker()
{

}

rectifierWorker::~rectifierWorker()
{
    //
}


void rectifierWorker:: refereshVoltageCurrent(){

    transfer(fd_rect);

    //QThread::sleep(2);
}
