#ifndef DOWNLOADERCORE_H
#define DOWNLOADERCORE_H
#include "Network/FileDownloader.h"
#include <QObject>
#include <QQmlEngine>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>
#include <QUuid>
#include <QVector>
class DownloaderCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int sizeOfModel READ getSizeOfModel WRITE setSizeOfModel NOTIFY modelUpdated)
public:
    explicit DownloaderCore(QObject* parent = nullptr);
    Q_INVOKABLE void startDownloadNewURL(const QString& url, const QString& fileAddressComplete);
    static inline void registerToQML()
    {
        qmlRegisterType<FileDownloader>("ir.hcoding.models", 1, 1, "FileDownloader");
        qmlRegisterType<DownloaderCore>("ir.hcoding.models", 1, 1, "DownloaderCore");
    }

    Q_INVOKABLE QVariantList model();
    int getSizeOfModel() const;
    void setSizeOfModel(int newSizeOfModel);

signals:
    void modelUpdated();

private:
    int sizeOfModel;
    QThreadPool _pool;
    QMap<QUuid, QSharedPointer<FileDownloader>> _workers;
};
#endif // DOWNLOADERCORE_H
