#include "httpserver2.h"

HttpServer2::HttpServer2(Args& arg, QObject *parent) : QTcpServer(parent)
{
    pool = new QThreadPool(this);

    ip = arg.ip;
    port = arg.port;
    dir = arg.dir;
}

void HttpServer2::start()
{
    if (listen(QHostAddress(ip), port.toInt())) {
        qDebug() << QString("Server starts to listen at %1:%2").arg(ip, port);
    }
    else {
        qDebug() << "Problem: " << errorString();
        close();
    }
}

void HttpServer2::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead()),
            this,   SLOT(readData()),
            Qt::DirectConnection);

//    connect(socket, SIGNAL(disconnected()),
//            this, SLOT(onDisconnected()),
//            Qt::DirectConnection );

}

void HttpServer2::readData()
{
//    QTextStream os(socket);
//    QString from = os.readAll();
    auto from = socket->readAll();

    qDebug() << "From 2:" << from;

//    Worker* w = new Worker(from);
//    w->setDir(dir);

//    connect(w, &Worker::workDone, this, &HttpServer2::sendData, Qt::QueuedConnection);

//    pool->start(w);
}

void HttpServer2::sendData(QByteArray to)
{
    socket->write(to);
    socket->disconnectFromHost();
}
