#include "response.h"

QString Response::info(
                    "HTTP/1.0 %1\r\n"
                    "Content-length: %2\r\n"
                    "Connection: close\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "%3"
                 );

OK::OK(QString* content_) : content(content_)
{}

QString* OK::toString()
{
    QString* ans = new QString(info);
    QString* resp = new QString(std::move(ans->arg("200 OK", QString::number(content->length()), *content)));
    return resp;
}

QString* NOT_FOUND::toString()
{
    QString* ans = new QString(info);
//    QString content = "<html><h2><center>404 Not Found</center></h2></html>";
    QString content = "<b>404 Not Found</b>";
    QString* resp = new QString(std::move(ans->arg("404 NOT FOUND", QString::number(content.length()), content)));
    return resp;
}
