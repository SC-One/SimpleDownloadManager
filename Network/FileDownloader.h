#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H
#include <QObject>

#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QMutex>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QUuid>
class QNetworkAccessManager;
class QNetworkReply;
class FileDownloader : public QObject
{
    Q_OBJECT
public:
    bool operator==(const QUuid& uid) const;
    enum DownloadStatus
    {
        Started,
        Requested,
        Downloading,
        Completed
    };
    explicit FileDownloader(QObject* parent = nullptr);
    ~FileDownloader();
    QString url() const;
    void setUrl(const QString& newUrl);

    QString fileCompleteAddress() const;
    void setFileCompleteAddress(const QString& newFileCompleteAddress);

    qreal progressbar();

    void stop();

    ///
    /// \brief start always before run this method set url and file address by methods :
    /// setUrl , setFileCompleteAddress
    ///
    /// and always run this method concurrent because
    ///
    void start();
    QUuid id() const;

signals:
    void downloaded();
    void downloadProgressChanged();
    void fileAddressChanged();
    void urlChanged();
    void idChanged();

    void errorOccured(const QString& error);

private:
    void setId(const QUuid& newId);
    void setProgressbar(qreal newProgressbar);
    QString lastError() const;
    void setLastError([[maybe_unused]] QNetworkReply::NetworkError newLastError);
    void setLastError(const QString& newLastError);
    ///
    /// \brief startDownload
    ///
    void startDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    bool openFile();
    void closeFile();
    bool clearFile();

    bool isHttpRedirect() const;

private:
    QScopedPointer<QNetworkAccessManager> _webCtrl;
    QNetworkReply* _replay;

    mutable QMutex _progressBarMutex;
    mutable QMutex _fileAddressMutex;
    mutable QMutex _urlLocker;
    mutable QMutex _idLocker;
    qreal _progressbar;
    QString _url;
    QString _lastError;
    QString _fileCompleteAddress; // TODO
    QFile _downloadedFile;
    QUuid _id;
};
#endif // FILEDOWNLOADER_H
