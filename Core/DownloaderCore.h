#ifndef DOWNLOADERCORE_H
#define DOWNLOADERCORE_H
#include "FileDownloaderModel.h"
#include <QObject>
#include <QQmlEngine>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>
#include <QUuid>
#include <QVector>
class DownloaderCore : public QObject
{
    Q_OBJECT
public:
    explicit DownloaderCore(QObject* parent = nullptr);
    void startDownloadNewURL(const QString& url, const QString& fileAddressComplete);
    static inline void registerToQML()
    {
        FileDownloaderModel::RegisterToQML();
        qmlRegisterType<DownloaderCore>("ir.hcoding.models", 1, 0, "DownloaderCore");
    }

private:
    QThreadPool _pool;

    FileDownloaderModel _model;
    QMap<QUuid, QSharedPointer<FileDownloader>> _workers;
};
#endif // DOWNLOADERCORE_H
