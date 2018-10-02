#include "handler.h"

Handler::Handler(const QString &path, const QString& responce)
{
    resp = new QString(responce);
    dir = new QDir(path);
    need_file = handle();
}

QString* Handler::responce()
{
    QString* data = readAll();

    if (data != nullptr)
        return Response::OK(data, data->length()).toString();

    return Response::NOT_FOUND().toString();
}

QString Handler::handle()
{
    QStringList items = resp->split(" ");
    QString path = items[1];

    QString str = path.section("/", -1, QString::SectionSkipEmpty);
    QStringList parts = str.split("\?");

    QString file = parts.at(0);

    return file;
}

QString* Handler::readAll()
{
    QFile* file = nullptr;
    QString* data = nullptr;

    if (need_file != "" && (file = find(need_file)) != nullptr) {

        if (!file->open(QIODevice::ReadOnly)) {
            qDebug() << "File can't open!";
            return data;
        }

        QByteArray bytes = file->readAll();

        QString chars = QString::fromLocal8Bit(bytes.data());
        data = new QString(std::move(chars));
    }

    return data;
}

QFile* Handler::find(const QString &need_file)
{
    QFile* file = nullptr;

    for(auto& file_info : dir->entryInfoList(QDir::Files)) {

        if (file_info.canonicalFilePath().contains(need_file)) {
            file = new QFile(file_info.filePath());
            break;
        }
    }

    return file;
}
