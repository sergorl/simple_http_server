#include "worker.h"

Worker::Worker(qintptr socketDescriptor_) : socketDescriptor(socketDescriptor_) {}

Worker::~Worker() {
    if (socket != nullptr) socket->close();
    socket = nullptr;
}

void Worker::setDir(QString dir)
{
    this->dir = dir;
}

void Worker::run() {

    loop = new QEventLoop;

    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead())   , this, SLOT(readData()),       Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection );

    loop->exec();
}

void Worker::readData()
{
    QTextStream os(socket);
    QString resp = os.readAll();

    QString id =  QString::number((long long) QThread::currentThreadId(), 16) ;
    QString received = QString("Received from thread #%1: %2").arg(id, resp);
    qDebug() << received;

    handle(resp);
}

void Worker::handle(QString& resp)
{
    Handler h(dir, resp);
    qDebug() << "REsponse: " << h.responce()->toLocal8Bit();
    socket->write(h.responce()->toLocal8Bit());
}

void Worker::onDisconnected()
{
    socket->close();
    loop->quit();
}
