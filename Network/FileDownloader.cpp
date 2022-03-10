#include "FileDownloader.h"
#include <QDebug>
#include <QDir>
#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <iostream>
bool FileDownloader::operator==(const QUuid& uid) const
{
    return id() == uid;
}

FileDownloader::FileDownloader(QObject* parent)
    : QObject{parent}
{
    auto x = new QTimer();
    x->setInterval(1000);
    connect(x, &QTimer::timeout, this, [this]() {
        if(_replay != nullptr)
            std::cerr << _replay->isRunning() << _replay->errorString().toStdString()
                      << _replay->bytesToWrite() << _replay->bytesAvailable()
                      << _replay->waitForReadyRead(100) << isHttpRedirect();
    });
    x->start(1000);
    setId(QUuid::createUuid());
    connect(this, &FileDownloader::fileAddressChanged, this, [this]() {
        QUrl nativeAddress(fileCompleteAddress());
        _downloadedFile.setFileName(QDir::toNativeSeparators(nativeAddress.toLocalFile()));
    });
    connect(this, &FileDownloader::errorOccured, this, [this](const QString& error) {
        std::cerr << error.toStdString();
    });
}

FileDownloader::~FileDownloader()
{
    std::cerr << "Deleted FileDownloader" << id().toString().toStdString();
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
    auto const& urlValue = QUrl(url());
    if(urlValue.isValid() && QUrl(fileCompleteAddress()).isLocalFile() && openFile())
    {
        QNetworkRequest request(urlValue);
        request.setAttribute(QNetworkRequest::Http2DirectAttribute, 26);
        _webCtrl.reset(new QNetworkAccessManager());
        connect(_webCtrl.get(), &QNetworkAccessManager::finished, this, [this]() {
            _replay->deleteLater();
            emit downloaded();
        });
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
    else
    {
        qDebug() << urlValue.isValid() << QUrl(fileCompleteAddress()).isLocalFile() << openFile();

        qDebug() << __FILE__ << __LINE__ << _downloadedFile.errorString();
    }
}

void FileDownloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    setProgressbar(qreal(bytesReceived) / bytesTotal);
}

bool FileDownloader::openFile()
try
{
    clearFile();
    if(!_downloadedFile.isOpen())
    {
        return _downloadedFile.open(QIODevice::WriteOnly | QIODevice::Append);
    }
    else
    {
        closeFile();
        openFile();
        qDebug() << __FILE__ << __LINE__ << _downloadedFile.errorString();
    }
    return false;
}
catch(...)
{
    qDebug() << __FILE__ << __LINE__ << _downloadedFile.errorString();
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

bool FileDownloader::isHttpRedirect() const
{
    if(_replay)
    {
        int statusCode = _replay->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        return statusCode == 301 || statusCode == 302 || statusCode == 303 || statusCode == 305 ||
               statusCode == 307 || statusCode == 308;
    }
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
    emit errorOccured(newLastError);
}
