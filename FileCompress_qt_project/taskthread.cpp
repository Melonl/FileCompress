#include "taskthread.h"

TaskThread::TaskThread(QObject* parent):QThread(parent){}

void TaskThread::run(){
    Compressor cpr;
    if(isCompress)
        cpr.compress(srcPath.toStdString(),outPath.toStdString());
    else
        cpr.decompress(srcPath.toStdString(),outPath.toStdString());
    emit done(cpr.costTime);

}

void TaskThread::setTask(QString src,QString out,bool issCompress){
    srcPath = src;
    outPath = out;
    this->isCompress = issCompress;
}
