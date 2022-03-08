#include "DownloaderCore.h"

DownloaderCore::DownloaderCore(QObject* parent)
    : QObject{parent}
{
    qDebug() << QStringLiteral("DownloaderCore has threadpool with %1").arg(_pool.stackSize());
}

void DownloaderCore::startDownloadNewURL(const QString& url, const QString& fileAddressComplete)
{
    QSharedPointer<FileDownloader> newFIleDownloader(new FileDownloader());
    newFIleDownloader->setUrl(url);
    newFIleDownloader->setFileCompleteAddress(fileAddressComplete);
    _workers.insert(newFIleDownloader->id(), newFIleDownloader);
    _model.addFileDownloader(newFIleDownloader);
    _pool.start([this, newFIleDownloader]() { newFIleDownloader->start(); });
}
