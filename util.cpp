#include "util.h"

Args::Args(QString ip_, QString port_, QString dir_) : ip(ip_), port(port_), dir(dir_)
{}

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
