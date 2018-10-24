#ifndef HANDLER_H
#define HANDLER_H

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include "response.h"

class Handler
{
public:
    Handler(const QString &path, const QString& request);

    QString* responce();

private:
    QDir dir;
    QString req;
    QString file;
    QString* data;

    QString getFileName();
    QFile* find(const QString& need_file);
    QString* read();
};

#endif // HANDLER_H
