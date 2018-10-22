#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QStringList>
#include <QCoreApplication>

struct Args {

    Args(QString ip_, QString port_, QString dir_);

    Args();

    QString ip;
    QString port;
    QString dir;

    QString toString();
};

#endif // UTIL_H
