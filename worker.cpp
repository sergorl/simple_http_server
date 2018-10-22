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
    QTextStream os(socket);
    QString resp = os.readAll();
    handle(resp);

//    int m_nNextBlockSize = 0;

//    QDataStream in(socket);

//    QString req = "";

//    qDebug() << "Start to read";

//    for (;;) {
//        if (!m_nNextBlockSize) {
//            if (socket->bytesAvailable() < sizeof(quint16)) {
//                break;
//            }
//            in >> m_nNextBlockSize;
//        }

//        if (socket->bytesAvailable() < m_nNextBlockSize) {
//            break;
//        }

//        QString data;
//        in >> data;

//        qDebug() << "Read:\n" << data;

//        req += data;

//        m_nNextBlockSize = 0;
//    }

//    qDebug() << "=========== all:\n" << req;

//    handle(req);
}

void Worker::handle(QString& resp)
{
    Handler h(dir, resp);
    QByteArray responce = h.responce()->toLocal8Bit();
//    socket->write(responce);

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
//    out << quint16(0) << responce;
    out << responce;
//    out.device()->seek(0);
//    out << quint16(arrBlock->size() - sizeof(quint16));
    socket->write(arrBlock);
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
