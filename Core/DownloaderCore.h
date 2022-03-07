#ifndef DOWNLOADERCORE_H
#define DOWNLOADERCORE_H
#include "Network/FileDownloader.h"
#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>
#include <QUuid>
#include <QVector>

namespace DownloadManager
{
class DownloaderCore : public QObject
{
    Q_OBJECT
public:
    explicit DownloaderCore(QObject* parent = nullptr);
    void startDownloadNewURL(const QString& url, const QString& fileAddressComplete);
    static inline void registerToQML() { }
signals:
    void workersChanged();

private:
    QThreadPool _pool;
    QMap<QUuid, QSharedPointer<FileDownloader>> _workers;
};
} // namespace DownloadManager

#endif // DOWNLOADERCORE_H
