#include "httpserver.h"

HttpServer::HttpServer(Args& arg, QObject *parent) : QTcpServer(parent)
{
    pool = new QThreadPool(this);   
    pool->setMaxThreadCount(64);

//    qDebug() << "Max threads: " << pool->maxThreadCount();
//    qDebug() << "Max connections: " << maxPendingConnections();
//    setMaxPendingConnections(128);

    ip = arg.ip;
    port = arg.port;
    dir = arg.dir;
}

void HttpServer::start()
{
    if (listen(QHostAddress(ip), port.toInt())) {
        //qDebug() << QString("Server starts to listen at %1:%2").arg(ip, port);        
    } else {
        qDebug() << "Problem: " << errorString();
        close();
    }
}

void HttpServer::incomingConnection(qintptr socketDescriptor)
{
    Worker* w = new Worker(socketDescriptor);
    w->setDir(dir);

    pool->start(w);
}

