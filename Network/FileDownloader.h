#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H
#include <QObject>

#include <QByteArray>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
class QNetworkAccessManager;
class QNetworkReply;
class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QObject* parent = nullptr);
    const QString& url() const;
    void setUrl(const QString& newUrl);

    const QString& fileCompleteAddress() const;
    void setFileCompleteAddress(const QString& newFileCompleteAddress);

    //    const QString& tempFileCompleteAddress() const;
    //    void setTempFileCompleteAddress(const QString& newTempFileCompleteAddress);

    QByteArray downloadedData();
    const QString& lastError() const;
    void setLastError([[maybe_unused]] QNetworkReply::NetworkError newLastError);
    void setLastError(const QString& newLastError);

signals:
    void downloaded();

    void downloadProgressChanged(int percent);

private:
    void startDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    bool openFile();
    void closeFile();
    bool clearFile();

private:
    QScopedPointer<QNetworkAccessManager> _webCtrl;
    QNetworkReply* _replay;
    QByteArray DownloadedData;

    QString _url;
    QString _lastError;
    QString _fileCompleteAddress; // TODO
    QFile _downloadedFile;
    //    QString _tempFileCompleteAddress; // TODO
};

#endif // FILEDOWNLOADER_H
