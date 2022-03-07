#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H
#include <QObject>

#include <QByteArray>
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
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString filefileCompleteAddress READ filefileCompleteAddress WRITE
                   setFilefileCompleteAddress NOTIFY filefileCompleteAddressChanged)
    Q_PROPERTY(qreal progressbar READ progressbar NOTIFY downloadProgressChanged)
    Q_PROPERTY(QString fileAddress READ fileCompleteAddress /*WRITE setFileCompleteAddress*/ NOTIFY
                   fileAddressChanged)
    Q_PROPERTY(QString url READ url /*WRITE setUrl*/ NOTIFY urlChanged)
public:
    inline bool operator==(const QUuid& uid) const
    {
        return id() == uid;
    }
    enum DownloadStatus
    {
        Started,
        Requested,
        Downloading,
        Completed
    };
    explicit FileDownloader(QObject* parent = nullptr);
    const QString& url() const;
    void setUrl(const QString& newUrl);

    const QString& fileCompleteAddress() const;
    void setFileCompleteAddress(const QString& newFileCompleteAddress);

    qreal progressbar() const;

    inline void stop()
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

    ///
    /// \brief start always before run this method set url and file address by methods :
    /// setUrl , setFileCompleteAddress
    ///
    /// and always run this method concurrent because
    ///
    inline void start()
    {
        if(_replay->isRunning())
        {
            _replay->close();
        }
        startDownload();
    }
    const QUuid& id() const;

signals:
    void downloaded();
    void downloadProgressChanged();
    void fileAddressChanged();
    void urlChanged();
    void idChanged();

private:
    void setId(const QUuid& newId);
    void setProgressbar(qreal newProgressbar);
    const QString& lastError() const;
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
