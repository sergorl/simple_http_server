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
    explicit Worker(QString from_);

    void setDir(QString dir);

    void run() override;

    void work();

signals:
    void workDone(QByteArray resp);

private slots:
    void handle(QString& resp);

private:
    QString dir;
    QString from;
};

#endif // WORKER_H
