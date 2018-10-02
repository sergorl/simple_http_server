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

    if (data != nullptr) {

//        qDebug() << "OK FIND" << Response::NOT_FOUND().toString();
        return Response::OK(data, data->length()).toString();
    }

//    qDebug() << "NOT FOUND" << Response::NOT_FOUND().toString();

    return Response::NOT_FOUND().toString();
}

QString Handler::handle()
{
    QStringList items = resp->split(" ");
    QString path = items[1];

    QString file = path.section("/", -1, QString::SectionSkipEmpty);

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
            qDebug() << "File is found: " << file->fileName();
            break;
        }
    }

    return file;
}
