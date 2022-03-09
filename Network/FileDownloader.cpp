#include "FileDownloader.h"
#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QNetworkReply>
bool FileDownloader::operator==(const QUuid& uid)
{
    return id() == uid;
}

FileDownloader::FileDownloader(QObject* parent)
    : QObject{parent}
{
    connect(_webCtrl.get(), &QNetworkAccessManager::finished, this, [this]() {
        _replay->deleteLater();
        emit downloaded();
    });
    setId(QUuid::createUuid());
}

QString FileDownloader::url() const
{
    return _url;
}

void FileDownloader::setUrl(const QString& newUrl)
{
    {
        QMutexLocker locker(&_urlLocker);
        _url = newUrl;
    }
    emit urlChanged();
}

QString FileDownloader::fileCompleteAddress() const
{
    QMutexLocker locker(&_fileAddressMutex);
    return _fileCompleteAddress;
}

void FileDownloader::setFileCompleteAddress(const QString& newFileCompleteAddress)
{
    {
        QMutexLocker locker(&_fileAddressMutex);
        _fileCompleteAddress = newFileCompleteAddress;
    }
    emit fileAddressChanged();
}

void FileDownloader::startDownload()
{
    if(QUrl(url()).isValid() && QUrl(fileCompleteAddress()).isLocalFile() && openFile())
    {
        QNetworkRequest request(url());
        _replay = _webCtrl->get(request);
        connect(_replay, &QNetworkReply::readyRead, this, [this]() {
            QByteArray data = _replay->readAll();
            qDebug() << "received data of size: " << data.size() << url();
            _downloadedFile.write(data);
        });
        connect(_replay, &QNetworkReply::downloadProgress, this, &FileDownloader::downloadProgress);
        connect(_replay,
                &QNetworkReply::errorOccurred,
                this,
                QOverload<QNetworkReply::NetworkError>::of(&FileDownloader::setLastError));
    }
}

void FileDownloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    setProgressbar(qreal(bytesReceived) / bytesTotal);
}

bool FileDownloader::openFile()
try
{
    if(!_downloadedFile.isOpen())
    {
        _downloadedFile.open(QIODevice::WriteOnly | QIODevice::Append);
        return clearFile();
    }
    else
    {
        closeFile();
        openFile();
    }
    return false;
}
catch(...)
{
    return false;
}

void FileDownloader::closeFile()
{
    if(_downloadedFile.isOpen())
    {
        _downloadedFile.close();
    }
}

bool FileDownloader::clearFile()
try
{
    return _downloadedFile.resize(0); //if failed clearing file.
}
catch(...)
{
    return false;
}

void FileDownloader::setId(const QUuid& newId)
{
    {
        QMutexLocker locker(&_idLocker);
        _id = newId;
    }
    emit idChanged();
}

QUuid FileDownloader::id() const
{
    QMutexLocker locker(&_idLocker);
    return _id;
}

qreal FileDownloader::progressbar()
{
    QMutexLocker locker(&_progressBarMutex);
    return _progressbar;
}

void FileDownloader::stop()
try
{
    if(_replay->isRunning())
    {
        _replay->abort();
        _replay->close();
    }
}
catch(...)
{
    // still nothing
}

void FileDownloader::start()
{
    if(_replay != nullptr)
    {
        //        if(_replay->isRunning())
        //        {
        //            _replay->close();
        //        }
        startDownload();
    }
}

void FileDownloader::setProgressbar(qreal newProgressbar)
{
    {
        QMutexLocker locker(&_progressBarMutex);
        _progressbar = newProgressbar;
    }
    emit downloadProgressChanged();
}

QString FileDownloader::lastError() const
{
    return _lastError;
}

void FileDownloader::setLastError(QNetworkReply::NetworkError newLastError)
{
    setLastError(_replay->errorString());
}
void FileDownloader::setLastError(const QString& newLastError)
{
    _lastError = newLastError;
    _replay->deleteLater();
}
