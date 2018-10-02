#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QThreadPool>

#include "worker.h"

struct Args {

    Args(QString ip_, QString port_, QString dir_);

    Args();

    QString ip;
    QString port;
    QString dir;

    QString toString();
};

class HttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpServer(Args& arg, QObject *parent = nullptr);
    void start();

private:
    QThreadPool* pool;
    QString ip;
    QString port;
    QString dir;

    void incomingConnection(qintptr socketDescriptor);
};

#endif // HTTPSERVER_H
