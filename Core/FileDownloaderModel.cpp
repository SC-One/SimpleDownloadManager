#include "FileDownloaderModel.h"

//FileDownloaderModel::FileDownloaderModel(QObject* parent)
//    : QAbstractListModel{parent}
//{
//    _roles = QHash<int, QByteArray>{
//        {FileDownloaderModel::FileDownloaderRoles::WorkerInfo, "WorkerInfo"}};
//}

//int FileDownloaderModel::rowCount(const QModelIndex& parent) const
//{
//    return _workers.size();
//}

//int FileDownloaderModel::columnCount(const QModelIndex& parent) const
//{
//    return 1;
//}

//QVariant FileDownloaderModel::data(const QModelIndex& index, int role) const
//{
//    auto const row = index.row();
//    if(row > _workers.size())
//        return {};
//    auto res = _workers[row];
//    return *(res.lock().get());
//}

//QVariant FileDownloaderModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    return _roles[role];
//}

//QHash<int, QByteArray> FileDownloaderModel::roleNames() const
//{
//    return _roles;
//}

//bool FileDownloaderModel::addFileDownloader(const QWeakPointer<FileDownloader>& data)
//{
//    if(contains(data.lock()->id()))
//    {
//        return false;
//    }
//    beginInsertRows(QModelIndex(), _workers.size(), _workers.size());
//    _workers.push_back(data);
//    endInsertRows();
//    return true;
//}

//void FileDownloaderModel::generateHeader()
//{
//    for(int i = FileDownloaderModel::WorkerInfo; i <= FileDownloaderModel::WorkerInfo; ++i)
//    {
//        setHeaderData(0, Qt::Horizontal, _roles[i], i);
//    }
//}

//bool FileDownloaderModel::contains(const QUuid& workerUuid)
//{
//    for(auto const& item : _workers)
//    {
//        auto sharedWorker = item.lock();
//        if(!sharedWorker.isNull())
//        {
//            if(sharedWorker->operator==(workerUuid))
//                return true;
//            ;
//        }
//    }
//    return false;
//}
