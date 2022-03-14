#include "FileDownloader.h"
#include <QDebug>
#include <QDir>
#include <QMutexLocker>
#include <QTimer>
#include <QUrl>
bool FileDownloader::operator==(const QUuid& uid) const
{
    return id() == uid;
}

FileDownloader::FileDownloader(QObject* parent)
    : QObject{parent}
{
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
    stop();
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
    if(urlValue.isValid() && QUrl(fileCompleteAddress()).isLocalFile() /* && openFile()*/)
    {
        downloadFileFromBegining(_downloadedFile.fileName(), urlValue.toString());
    }
    else
    {
        qDebug() << __FILE__ << __LINE__ << _downloadedFile.errorString();
    }
}

void FileDownloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    setProgressbar(qreal(bytesReceived) / bytesTotal * 100);
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
    _streamDownloadedData.close();
}
catch(...)
{
    // still nothing
}

void FileDownloader::start()
{
    startDownload();
}

void FileDownloader::setProgressbar(qreal newProgressbar)
{
    {
        QMutexLocker locker(&_progressBarMutex);
        _progressbar = newProgressbar;
    }
    emit downloadProgressChanged(newProgressbar);
}

QString FileDownloader::lastError() const
{
    return _lastError;
}

void FileDownloader::setLastError(const QString& newLastError)
{
    _lastError = newLastError;
    emit errorOccured(newLastError);
}

void FileDownloader::setLastError(const std::string& newLastError)
{
    setLastError(QString::fromStdString(newLastError));
}

void FileDownloader::downloadFileFromBegining(const std::string& nameOfFile, const std::string& url)
try
{
    _streamDownloadedData.open(nameOfFile);
    _curlHandler.setOpt(new curlpp::options::NoProgress(false));
    _curlHandler.setOpt(
        new curlpp::options::ProgressFunction(curlpp::types::ProgressFunctionFunctor(
            [this](double dltotal, double dlnow, double ultotal, double ulnow) -> double {
                if(0 == dltotal)
                {
                    dltotal = 1;
                    dlnow = 0;
                }
                dltotal /= 1024 / 1024;
                dlnow /= 1024 / 1024;
                downloadProgress(dlnow, dltotal);
                return 0;
            })));
    _curlHandler.setOpt(new curlpp::options::WriteStream(&_streamDownloadedData));
    _curlHandler.setOpt(new curlpp::options::Url(url));
    _curlHandler.perform();
    _streamDownloadedData.close();
}
catch(curlpp::LogicError& e)
{
    std::cerr << e.what() << std::endl;
    setLastError(std::string("curlpp::LogicError -> ") + e.what());
    std::cerr << "error" << std::endl;
}
catch(curlpp::RuntimeError& e)
{
    std::cerr << e.what() << std::endl;
    setLastError(std::string("curlpp::RuntimeError -> ") + e.what());
    std::cerr << "error" << std::endl;
}

void FileDownloader::downloadFileFromBegining(const QString& nameOfFile, const QString& url)
{
    downloadFileFromBegining(nameOfFile.toStdString(), url.toStdString());
}
