#include "worker.h"

Worker::Worker(QTcpSocket* socket, QString req) : from(req),
                                                  pClientSocket(socket)
{}

void Worker::setDir(QString dir)
{
    this->dir = dir;
}

void Worker::run()
{
    handle(from);
}

void Worker::handle(QString req)
{
    Handler h(dir, req);
    QByteArray responce = h.responce()->toLocal8Bit();

    emit workDone(pClientSocket, responce);
}

