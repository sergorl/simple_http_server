#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "httpserver.h"
#include "response.h"
#include "handler.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Args arg;
    HttpServer server(arg);
    server.start();

    return a.exec();

}
