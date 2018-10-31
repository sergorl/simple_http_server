#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtDebug>
#include <QTcpSocket>
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
    explicit Worker(QTcpSocket* socket, QString req);

    void setDir(QString dir);

    void run() override;

    void work();

signals:
    void workDone(QTcpSocket* socket, QByteArray resp);

private slots:
    void handle(QString req);

private:
    QString dir;
    QString from;
    QTcpSocket* pClientSocket;
};

#endif // WORKER_H
