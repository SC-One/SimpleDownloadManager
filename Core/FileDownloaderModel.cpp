#include "FileDownloaderModel.h"

FileDownloaderModel::FileDownloaderModel(QObject* parent)
    : QAbstractListModel{parent}
{
    _roles = QHash<int, QByteArray>{
        {FileDownloaderModel::FileDownloaderRoles::ID, "ID"},
        {FileDownloaderModel::FileDownloaderRoles::FileNameAddress, "FileNameAddress"},
        {FileDownloaderModel::FileDownloaderRoles::URL, "URL"},
        {FileDownloaderModel::FileDownloaderRoles::ProgressPercent, "ProgressPercent"}};
}

int FileDownloaderModel::rowCount(const QModelIndex& parent) const
{
    return _workers.size();
}

int FileDownloaderModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant FileDownloaderModel::data(const QModelIndex& index, int role) const
{
    auto const row = index.row();
    if(row > _workers.size())
        return {};
    auto& res = _workers[row];
    switch(role)
    {
    case FileDownloaderModel::ID:
        return res.lock()->id();
    case FileDownloaderModel::FileNameAddress:
        return res.lock()->fileCompleteAddress();
    case FileDownloaderModel::URL:
        return res.lock()->url();
    case FileDownloaderModel::ProgressPercent:
        return res.lock()->progressbar();
    default:
        return "";
    }
}

QVariant FileDownloaderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return _roles[role];
}

QHash<int, QByteArray> FileDownloaderModel::roleNames() const
{
    return _roles;
}

bool FileDownloaderModel::addFileDownloader(const QWeakPointer<FileDownloader>& data)
{
    if(contains(data.lock()->id()))
    {
        return false;
    }
    beginInsertRows(QModelIndex(), _workers.size(), _workers.size());
    _workers.push_back(data);
    endInsertRows();
    return true;
}

void FileDownloaderModel::generateHeader()
{
    for(int i = FileDownloaderModel::ID; i <= FileDownloaderModel::ProgressPercent; ++i)
    {
        setHeaderData(0, Qt::Horizontal, _roles[i], i);
    }
}

bool FileDownloaderModel::contains(const QUuid& workerUuid)
{
    for(auto const& item : _workers)
    {
        auto sharedWorker = item.lock();
        if(!sharedWorker.isNull())
        {
            if(sharedWorker->operator==(workerUuid))
                return true;
            ;
        }
    }
    return false;
}
