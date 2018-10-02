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
    Handler(const QString &path, const QString& responce);

    QString* responce();
    QString handle();
    QString* readAll();

private:
    QDir* dir;
    QString* resp;
    QString need_file;

    QFile* find(const QString& need_file);
};

#endif // HANDLER_H
