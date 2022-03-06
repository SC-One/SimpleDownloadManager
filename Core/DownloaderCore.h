#ifndef DOWNLOADERCORE_H
#define DOWNLOADERCORE_H
#include <QObject>

namespace DownloadManager
{
class DownloaderCore : public QObject
{
    Q_OBJECT
public:
    explicit DownloaderCore(QObject* parent = nullptr);
signals:
};
} // namespace DownloadManager

#endif // DOWNLOADERCORE_H
