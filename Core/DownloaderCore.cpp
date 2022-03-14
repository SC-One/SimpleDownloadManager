#include "DownloaderCore.h"
//#define TEST_USE_CASE
DownloaderCore::DownloaderCore(QObject* parent)
    : QObject{parent}
    , _model(new FileDownloaderModel())
{
    qDebug() << QStringLiteral("DownloaderCore has threadpool with %1").arg(_pool.stackSize());
    connect(this,
            &DownloaderCore::newFileDownloaderAdded,
            _model.get(),
            &FileDownloaderModel::addFileDownloader,
            Qt::QueuedConnection);
}

void DownloaderCore::startDownloadNewURL(const QString& url, const QString& fileAddressComplete)
{
    _pool.start([=]() {
        QSharedPointer<FileDownloader> newFIleDownloader(new FileDownloader());
        newFIleDownloader->setUrl(url);
        newFIleDownloader->setFileCompleteAddress(fileAddressComplete);
        insertNewModel(newFIleDownloader);
        newFIleDownloader->start();
    });
}

QWeakPointer<FileDownloaderModel> DownloaderCore::model() const
{
    return _model;
}

void DownloaderCore::insertNewModel(const QSharedPointer<FileDownloader>& newFIleDownloader)
{

    _workers.insert(newFIleDownloader->id(), newFIleDownloader);
    emit newFileDownloaderAdded(newFIleDownloader);
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
