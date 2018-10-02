#ifndef RESPONSE_H
#define RESPONSE_H

#include <QString>

class Response
{
public:

    Response() = default;

    class OK {
    public:
        OK(QString* content_, int content_len_);
        QString* toString();

    private:
        static QString info;
        QString* content;
        int content_len;
    };

    class NOT_FOUND {
    public:
        NOT_FOUND() = default;
        QString* toString();

    private:
        static QString info;
    };
};

#endif // RESPONSE_H
