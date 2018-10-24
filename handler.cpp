#include "handler.h"

Handler::Handler(const QString &path, const QString& request)
{
    req = QString(request);
    dir = QDir(path);
    file = getFileName();
    data = read();
}

QString* Handler::responce()
{
    if (data != nullptr)
        return OK(data).toString();

    return NOT_FOUND().toString();
}

QString Handler::getFileName()
{
    QStringList items = req.split(" ");
    QString path = items[1];

    QString str = path.section("/", -1, QString::SectionSkipEmpty);
    QStringList parts = str.split("\?");

    QString file = parts.at(0);

    return file;
}

QString* Handler::read()
{
    QFile* pFile = nullptr;
    QString* data = nullptr;

    if (file != "" && (pFile = find(file)) != nullptr) {

        if (!pFile->open(QIODevice::ReadOnly)) {
            qDebug() << "File can't open!";
            return data;
        }

        QByteArray bytes = pFile->readAll();

        QString chars = QString::fromLocal8Bit(bytes.data());
        data = new QString(std::move(chars));
    }

    return data;
}

QFile* Handler::find(const QString &need_file)
{
    QFile* file = nullptr;

    for(auto& file_info : dir.entryInfoList(QDir::Files)) {

        if (file_info.canonicalFilePath().contains(need_file)) {
            file = new QFile(file_info.filePath());
            break;
        }
    }

    return file;
}
