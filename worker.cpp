#include "worker.h"

Worker::Worker(qintptr socketDescriptor_) : socketDescriptor(socketDescriptor_) {}

Worker::Worker(QString from_) : from(from_) {}

Worker::~Worker() {
    if (socket != nullptr) socket->close();
    socket = nullptr;
}

void Worker::setDir(QString dir)
{
    this->dir = dir;
}

void Worker::run() {

    work1();
//    work2();
}

void Worker::work1()
{
    loop = new QEventLoop;

    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead())   , this, SLOT(readData()),       Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection );

    loop->exec();
}

void Worker::work2()
{
    loop = new QEventLoop;

    handle2(from);

    loop->exec();
}

void Worker::readData()
{
    QString resp = socket->readAll();
    handle(resp);
}

void Worker::handle(QString& resp)
{
    Handler h(dir, resp);
    QByteArray responce = h.responce()->toLocal8Bit();
    socket->write(responce);
    socket->close();
}

void Worker::handle2(QString &resp)
{
    Handler h(dir, resp);
    QByteArray responce = h.responce()->toLocal8Bit();

    emit workDone(responce);
}

void Worker::onDisconnected()
{
    socket->close();
    loop->quit();
}
