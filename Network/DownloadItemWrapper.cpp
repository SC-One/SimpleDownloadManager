#include "DownloadItemWrapper.h"

bool DownloadItemWrapper::operator==(const QUuid& uid) const
{
    return _fileDownloaderCore->id() == uid;
}

DownloadItemWrapper::DownloadItemWrapper(QObject* parent)
    : DownloadItemWrapper({nullptr}, parent)
{ }

DownloadItemWrapper::~DownloadItemWrapper()
{
    qDebug() << "Deleted DownloadItemWrapper" << fileDownloaderCore()->id();
}

DownloadItemWrapper::DownloadItemWrapper(const QSharedPointer<FileDownloader>& fileDownloader,
                                         QObject* parent)
    : QObject(parent)
{
    setFileDownloaderCore(fileDownloader);
    setDefaultValues(fileDownloader);
}

DownloadItemWrapper::DownloadItemWrapper(const DownloadItemWrapper& that)
{
    this->operator=(that);
}

DownloadItemWrapper& DownloadItemWrapper::operator=(const DownloadItemWrapper& that)
{
    setFileDownloaderCore(that.fileDownloaderCore());
    setDefaultValues(that.fileDownloaderCore());
    qDebug() << that.url() << that.fileAddress() << that._progressPercentage;
    return (*this);
}

const QString& DownloadItemWrapper::url() const
{
    return _url;
}

void DownloadItemWrapper::setUrl(const QString& newUrl)
{
    _url = newUrl;
    emit urlChanged();
}

const QString& DownloadItemWrapper::fileAddress() const
{
    return _fileAddress;
}

void DownloadItemWrapper::setFileAddress(const QString& newFileAddress)
{
    _fileAddress = newFileAddress;
    emit fileAddressChanged();
}

qreal DownloadItemWrapper::progressPercentage() const
{
    return _progressPercentage;
}

void DownloadItemWrapper::setProgressPercentage(qreal newProgressPercentage)
{
    _progressPercentage = newProgressPercentage;
    emit downloadProgressChanged();
}

void DownloadItemWrapper::initDefaultConnections()
{
    connect(
        _fileDownloaderCore.get(),
        &FileDownloader::downloadProgressChanged,
        this,
        [this]() { setProgressPercentage(_fileDownloaderCore->progressbar()); },
        Qt::QueuedConnection);
    connect(
        _fileDownloaderCore.get(),
        &FileDownloader::urlChanged,
        this,
        [this]() { setUrl(_fileDownloaderCore->url()); },
        Qt::QueuedConnection);
    connect(
        _fileDownloaderCore.get(),
        &FileDownloader::fileAddressChanged,
        this,
        [this]() { setFileAddress(_fileDownloaderCore->fileCompleteAddress()); },
        Qt::QueuedConnection);
    connect(_fileDownloaderCore.get(),
            &FileDownloader::errorOccured,
            this,
            &DownloadItemWrapper::setLastError,
            Qt::QueuedConnection);
}

void DownloadItemWrapper::setDefaultValues(const QWeakPointer<FileDownloader>& fileDownloader)
{
    auto const temp = fileDownloader.lock();
    if(!temp.isNull())
    {
        setUrl(temp->url());
        setFileAddress(temp->fileCompleteAddress());
        setProgressPercentage(0);
    }
}

const QString& DownloadItemWrapper::lastError() const
{
    return _lastError;
}

void DownloadItemWrapper::setLastError(const QString& newLastError)
{
    _lastError = newLastError;
    emit errorOccured();
}

void DownloadItemWrapper::setFileDownloaderCore(
    QSharedPointer<FileDownloader> newFileDownloaderCore)
{
    _fileDownloaderCore = newFileDownloaderCore;
    initDefaultConnections();
    emit coreDownloaderChanged();
}

QSharedPointer<FileDownloader> DownloadItemWrapper::fileDownloaderCore() const
{
    return _fileDownloaderCore;
}
