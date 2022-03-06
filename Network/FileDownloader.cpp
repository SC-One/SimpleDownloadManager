#include "FileDownloader.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
FileDownloader::FileDownloader(QObject* parent)
    : QObject{parent}
{
    connect(_webCtrl.get(), &QNetworkAccessManager::finished, this, [this]() {
        _replay->deleteLater();
        emit downloaded();
    });
}

const QString& FileDownloader::url() const
{
    return _url;
}

void FileDownloader::setUrl(const QString& newUrl)
{
    _url = newUrl;
}

const QString& FileDownloader::fileCompleteAddress() const
{
    return _fileCompleteAddress;
}

void FileDownloader::setFileCompleteAddress(const QString& newFileCompleteAddress)
{
    _fileCompleteAddress = newFileCompleteAddress;
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
    emit downloadProgressChanged(double(bytesReceived) / bytesTotal);
}

bool FileDownloader::openFile()
try
{
    if(!_downloadedFile.isOpen())
    {
        _downloadedFile.open(QIODevice::WriteOnly | QIODevice::Append);
        return clearFile();
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

const QString& FileDownloader::lastError() const
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

//const QString& FileDownloader::tempFileCompleteAddress() const
//{
//    return _tempFileCompleteAddress;
//}

//void FileDownloader::setTempFileCompleteAddress(const QString& newTempFileCompleteAddress)
//{
//    _tempFileCompleteAddress = newTempFileCompleteAddress;
//}
