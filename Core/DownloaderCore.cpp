#include "DownloaderCore.h"
//#define TEST_USE_CASE
DownloaderCore::DownloaderCore(QObject* parent)
    : QObject{parent}
    , sizeOfModel(0)
{
    qDebug() << QStringLiteral("DownloaderCore has threadpool with %1").arg(_pool.stackSize());
}

void DownloaderCore::startDownloadNewURL(const QString& url, const QString& fileAddressComplete)
{
    QSharedPointer<FileDownloader> newFIleDownloader(new FileDownloader());
    newFIleDownloader->setUrl(url);
    newFIleDownloader->setFileCompleteAddress(fileAddressComplete);
    _workers.insert(newFIleDownloader->id(), newFIleDownloader);
    setSizeOfModel(getSizeOfModel() + 1);
    _pool.start([this, newFIleDownloader]() { newFIleDownloader->start(); });
}

QVariantList DownloaderCore::model()
{
    /*QList<FileDownloader*> */ QVariantList result;
    auto const model = _workers.values();
    for(auto const& item : model)
    {
        result.append(item.get());
    }
    return result;
}

int DownloaderCore::getSizeOfModel() const
{
    return sizeOfModel;
}

void DownloaderCore::setSizeOfModel(int newSizeOfModel)
{
    sizeOfModel = newSizeOfModel;
    emit modelUpdated();
}

//#ifdef TEST_USE_CASE
//void addTestParams()
//{

//}
//#endif
