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
                    "HTTP/1.0 404 Not Found"
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
    return new QString(info);
}
