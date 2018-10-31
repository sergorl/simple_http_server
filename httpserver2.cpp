#include "httpserver2.h"

HttpServer2::HttpServer2(Args& arg, QObject *parent) : QTcpServer(parent)
{
    pool = new QThreadPool(this);
//    pool->setMaxThreadCount(2);
//    setMaxPendingConnections(128);

    ip = arg.ip;
    port = arg.port;
    dir = arg.dir;
}

void HttpServer2::start()
{
    if (listen(QHostAddress(ip), port.toInt())) {
//        qDebug() << QString("Server starts to listen at %1:%2").arg(ip, port);
    }
    else {
        qDebug() << "Problem: " << errorString();
        close();
    }
}

void HttpServer2::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead()),
            this,   SLOT(readData()),
            Qt::DirectConnection);

//    qDebug() << "New connection";
}

void HttpServer2::readData()
{
//    qDebug() << "Read Begin";

    pClientSocket = (QTcpSocket*) sender();
    QString from = pClientSocket->readAll();

    Worker* w = new Worker(from);
    w->setDir(dir);        
    w->setAutoDelete(true);

//    qDebug() << "Worker is created";

    pool->start(w);
    connect(w, &Worker::workDone, this, &HttpServer2::sendData, Qt::QueuedConnection);

//    qDebug() << "Read End";
}

void HttpServer2::sendData(QByteArray to)
{    
//    qDebug() << "Write";

    pClientSocket->write(to);
    pClientSocket->close();

//    qDebug() << "Send";

}
