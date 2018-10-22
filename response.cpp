#include "response.h"

QString Response::OK::info(
                   "HTTP/1.0 200 OK\r\n"
                   "Content-length: %1\r\n"
                   "Connection: close\r\n"
                   "Content-Type: text/html\r\n"
                   "\r\n"
                   "%2"
                 );

QString Response::NOT_FOUND::info(
                    "HTTP/1.0 404 Not Found\r\n"
                    "Content-length: %1\r\n"
                    "Connection: close\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "%2"
                 );

Response::OK::OK(QString* content_, int content_len_) :
    content(content_),
    content_len(content_len_)
{

}

QString* Response::OK::toString()
{
    QString* ans = new QString(info);
    QString* resp = new QString(std::move(ans->arg(QString::number(content_len), *content)));
    return resp;
}

QString* Response::NOT_FOUND::toString()
{
    QString* ans = new QString(info);
    QString content = "<html><h2><center>404 Not Found</center></h2></html>\r\n\n";
    QString* resp = new QString(std::move(ans->arg(QString::number(content.length()), content)));
//    QString* resp = new QString(std::move(ans->arg(0, "")));
    return resp;
}
