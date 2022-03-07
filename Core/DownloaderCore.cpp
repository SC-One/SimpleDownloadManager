#include "DownloaderCore.h"

namespace DownloadManager
{
DownloaderCore::DownloaderCore(QObject* parent)
    : QObject{parent}
{
    qDebug() << QStringLiteral("DownloaderCore has threadpool with %1").arg(_pool.stackSize());
}

void DownloaderCore::startDownloadNewURL(const QString& url, const QString& fileAddressComplete)
{
    auto newFIleDownloader = QSharedPointer<FileDownloader>::create();
    newFIleDownloader->setUrl(url);
    newFIleDownloader->setFileCompleteAddress(fileAddressComplete);
    _workers.insert(newFIleDownloader->id(), newFIleDownloader);
    emit workersChanged();
    _pool.start([this, newFIleDownloader]() { newFIleDownloader->start(); });
}
} // namespace DownloadManager
