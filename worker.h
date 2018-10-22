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
#include <QByteArray>
#include <QDataStream>

#include "handler.h"
#include "response.h"

class Worker : public QObject, public QRunnable {
    Q_OBJECT

public:
    explicit Worker(qintptr socketDescriptor_);
    explicit Worker(QString from_);

    ~Worker();

    void setDir(QString dir);

    void run() override;

    void work1();
    void work2();

signals:
    void workDone(QByteArray resp);

private slots:
    void readData();
    void handle(QString& resp);
    void handle2(QString& resp);
    void onDisconnected();

private:
    QTcpSocket* socket;
    QEventLoop *loop;
    qintptr socketDescriptor;
    QString dir;
    QString from;
};

#endif // WORKER_H
