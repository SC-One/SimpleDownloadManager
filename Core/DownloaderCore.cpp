#include "DownloaderCore.h"
//#define TEST_USE_CASE
DownloaderCore::DownloaderCore(QObject* parent)
    : QObject{parent}
    , _model(new FileDownloaderModel())
{
    qDebug() << QStringLiteral("DownloaderCore has threadpool with %1").arg(_pool.stackSize());
}

void DownloaderCore::startDownloadNewURL(const QString& url, const QString& fileAddressComplete)
{
    QSharedPointer<FileDownloader> newFIleDownloader(new FileDownloader());
    newFIleDownloader->setUrl(url);
    newFIleDownloader->setFileCompleteAddress(fileAddressComplete);
    _workers.insert(newFIleDownloader->id(), newFIleDownloader);
    _model->addFileDownloader(newFIleDownloader);
    _pool.start([this, newFIleDownloader]() { newFIleDownloader->start(); });
}

QWeakPointer<FileDownloaderModel> DownloaderCore::model() const
{
    return _model;
}

void DownloaderCore::setModel(QSharedPointer<FileDownloaderModel> newModel)
{
    _model = newModel;
    emit modelUpdated();
}

QAbstractListModel* DownloaderCore::rawModel() const
{
    return _model.get();
}
