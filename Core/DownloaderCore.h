#ifndef DOWNLOADERCORE_H
#define DOWNLOADERCORE_H
#include "FileDownloaderModel.h"
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
    Q_PROPERTY(QAbstractListModel* model READ rawModel NOTIFY modelUpdated)
public:
    explicit DownloaderCore(QObject* parent = nullptr);
    Q_INVOKABLE void startDownloadNewURL(const QString& url, const QString& fileAddressComplete);
    static inline void registerToQML()
    {
        FileDownloaderModel::RegisterToQML();
        qmlRegisterType<DownloaderCore>("ir.hcoding.models", 1, 1, "DownloaderCore");
    }

    QWeakPointer<FileDownloaderModel> model() const;

private:
    void setModel(QSharedPointer<FileDownloaderModel> newModel);
    QAbstractListModel* rawModel() const;

signals:
    void modelUpdated();

private:
    QThreadPool _pool;
    QSharedPointer<FileDownloaderModel> _model;
    QMap<QUuid, QSharedPointer<FileDownloader>> _workers;
};
#endif // DOWNLOADERCORE_H
