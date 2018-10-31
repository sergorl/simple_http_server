#include "worker.h"

Worker::Worker(QString from_) : from(from_) {}

void Worker::setDir(QString dir)
{
    this->dir = dir;
}

void Worker::run() {

//    qDebug() << "Work";
    handle(from);
}

void Worker::handle(QString &req)
{
//    qDebug() << "Handle start";

    Handler h(dir, req);
    QByteArray responce = h.responce()->toLocal8Bit();

//    qDebug() << "Handle end";

    emit workDone(responce);
}

