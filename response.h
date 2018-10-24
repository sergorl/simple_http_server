#ifndef RESPONSE_H
#define RESPONSE_H

#include <QString>

class Response {
    public:

        Response() = default;

        static QString info;
};

class OK : Response {
    public:
        OK(QString* content_);
        QString* toString();

    private:
        QString* content;
};

class NOT_FOUND : Response {
    public:
        NOT_FOUND() = default;
        QString* toString();

    private:
};

#endif // RESPONSE_H
