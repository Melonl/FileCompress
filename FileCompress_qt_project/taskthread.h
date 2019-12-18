#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include <QThread>
#include <QString>
#include "Compressor.h"

class TaskThread : public QThread
{
    Q_OBJECT

    QString srcPath;
    QString outPath;
    bool isCompress;

public:
    TaskThread(QObject* parent = 0);
    void setTask(QString src,QString out,bool isCompress);

    signals:
    void done(double costTime);
    void updateMsg(QString msg);

protected:
    void run();
};

#endif // TASKTHREAD_H
