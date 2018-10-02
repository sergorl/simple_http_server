#include "httpserver.h"

HttpServer::HttpServer(Args& arg, QObject *parent) : QTcpServer(parent)
{
    pool = new QThreadPool(this);   
    pool->setMaxThreadCount(512);

    ip = arg.ip;
    port = arg.port;
    dir = arg.dir;
}

void HttpServer::start()
{
    if (listen(QHostAddress(ip), port.toInt()))
        qDebug() << QString("Server starts to listen at %1:%2").arg(ip, port);
    else
        qDebug() << "Problem: " << errorString();
}

void HttpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "New connection";
    Worker* w = new Worker(socketDescriptor);
    w->setDir(dir);
    pool->start(w);
}

Args::Args(QString ip_, QString port_, QString dir_) : ip(ip_), port(port_), dir(dir_)
{
}

Args::Args()
{
    QStringList arg = QCoreApplication::arguments();

    ip = arg.at(2);
    port = arg.at(4);
    dir = arg.at(6);
}

QString Args::toString()
{
    return QString("ip: %1 : %2; dir: %3").arg(ip, port, dir);
}
