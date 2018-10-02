#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtDebug>
#include <QRunnable>
#include <QThread>
#include <QTextStream>
#include <QEventLoop>
#include <QString>

#include "handler.h"
#include "response.h"

class Worker : public QObject, public QRunnable {
    Q_OBJECT

public:
    explicit Worker(qintptr socketDescriptor_);
    ~Worker();

    void setDir(QString dir);

    void run();

private slots:
    void readData();
    void handle(QString& resp);
    void onDisconnected();

private:
    QTcpSocket* socket;
    QEventLoop *loop;
    qintptr socketDescriptor;
    QString dir;
};

#endif // WORKER_H
