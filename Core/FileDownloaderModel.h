#ifndef FILEDOWNLOADERMODEL_H
#define FILEDOWNLOADERMODEL_H
//#include "Network/FileDownloader.h"
//#include <QAbstractListModel>
//#include <QObject>
//#include <QQmlEngine>
//class FileDownloaderModel : public QAbstractListModel
//{
//    Q_OBJECT
//public:
//    FileDownloaderModel(QObject* parent = nullptr);

//    enum FileDownloaderRoles
//    {
//        WorkerInfo = Qt::UserRole + 1
//    };
//    Q_ENUM(FileDownloaderRoles)
//public:
//    ///////////////////@@ QAbstractListModel interface @@///////////////////
//    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
//    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
//    QVariant
//    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    QHash<int, QByteArray> roleNames() const override;
//    ///////////////////////////////////////////////////////////////////

//public:
//    Q_INVOKABLE bool addFileDownloader(const QWeakPointer<FileDownloader>& data);
//    Q_INVOKABLE void generateHeader();
//    Q_INVOKABLE bool contains(const QUuid& workerUuid);
//    Q_INVOKABLE QWeakPointer<FileDownloader> getFileDownloader(const QUuid& workerUuid) const
//    {
//        for(auto const& item : _workers)
//        {
//            auto sharedWorker = item.lock();
//            if(!sharedWorker.isNull())
//            {
//                if(sharedWorker->operator==(workerUuid))
//                    return sharedWorker;
//                ;
//            }
//        }
//        return {};
//    }

//public:
//    static inline void RegisterToQML()
//    {
//        qmlRegisterType<FileDownloader>("ir.hcoding.models", 1, 0, "FileDownloader");
//        qmlRegisterType<FileDownloaderModel>("ir.hcoding.models", 1, 0, "FileDownloaderModel");
//    }

//private:
//    QHash<int, QByteArray> _roles;
//    QVector<QWeakPointer<FileDownloader>> _workers;
//};

//Q_DECLARE_METATYPE(FileDownloader);
#endif // FILEDOWNLOADERMODEL_H
