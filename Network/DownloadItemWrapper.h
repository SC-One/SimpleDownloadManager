#ifndef DOWNLOADITEMWRAPPER_H
#define DOWNLOADITEMWRAPPER_H

#include "FileDownloader.h"
#include <QObject>
#include <QSharedPointer>

///
/// \brief The DownloadItemWrapper class
///
/// the view of downloader that is on progressing.(just for show detailes of downloader.
class DownloadItemWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString fileAddress READ fileAddress NOTIFY fileAddressChanged)
    Q_PROPERTY(qreal progressbar READ progressPercentage NOTIFY downloadProgressChanged)

public:
    bool operator==(const QUuid& uid) const;
    explicit DownloadItemWrapper(QObject* parent = nullptr);
    ~DownloadItemWrapper();
    explicit DownloadItemWrapper(const QSharedPointer<FileDownloader>& fileDownloader,
                                 QObject* parent = nullptr);

    //
    //For QVariant: @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    DownloadItemWrapper(const DownloadItemWrapper& that);
    DownloadItemWrapper& operator=(const DownloadItemWrapper& that);
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    const QString& url() const;
    void setUrl(const QString& newUrl);

    const QString& fileAddress() const;
    void setFileAddress(const QString& newFileAddress);

    qreal progressPercentage() const;
    void setProgressPercentage(qreal newProgressPercentage);

    QSharedPointer<FileDownloader> fileDownloaderCore() const;
    void setFileDownloaderCore(QSharedPointer<FileDownloader> newFileDownloaderCore);

    const QString& lastError() const;
    void setLastError(const QString& newLastError);

signals:
    void urlChanged();
    void fileAddressChanged();
    void downloadProgressChanged();
    void coreDownloaderChanged();
    void errorOccured();

private:
    void initDefaultConnections();
    void setDefaultValues(const QWeakPointer<FileDownloader>& fileDownloader);

private:
    QSharedPointer<FileDownloader> _fileDownloaderCore;
    QString _url;
    QString _fileAddress;
    qreal _progressPercentage;
    QString _lastError;
};
Q_DECLARE_METATYPE(DownloadItemWrapper)

#endif // DOWNLOADITEMWRAPPER_H
