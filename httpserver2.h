#ifndef HTTPSERVER2_H
#define HTTPSERVER2_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QThreadPool>
#include <QTextStream>

#include "util.h"
#include "worker.h"

struct HttpServer2 : public QTcpServer {

    Q_OBJECT

public:
    HttpServer2(Args& arg, QObject* parent = nullptr);

    void start();

    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void readData();
    void sendData(QByteArray to);

private:
    QThreadPool* pool;
    QTcpSocket *socket;

    QString ip;
    QString port;
    QString dir;
};

#endif // HTTPSERVER2_H
