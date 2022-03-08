#include "DownloaderWrapper.h"
//#include "Network/FileDownloader.h"
//DownloaderWrapper::DownloaderWrapper(QObject* parent)
//    : QObject{parent}
//{
//    connect(this, &DownloaderWrapper::fileDownloaderChanged, this, [this]() {
//        auto fileDownloader = _fileDownloader.lock();
//        if(!fileDownloader.isNull())
//            connect(fileDownloader.get(),
//                    &FileDownloader::downloadProgressChanged,
//                    this,
//                    &DownloaderWrapper::downloadProgressChanged);
//    });
//}

//QWeakPointer<FileDownloader> DownloaderWrapper::fileDownloader() const
//{
//    return _fileDownloader;
//}

//void DownloaderWrapper::setFileDownloader(QWeakPointer<FileDownloader> newFileDownloader)
//{
//    if(_fileDownloader == newFileDownloader)
//        return;
//    _fileDownloader = newFileDownloader;
//    emit fileDownloaderChanged();
//}

//void DownloaderWrapper::setFileDownloader(QSharedPointer<FileDownloader> newFileDownloader)
//{
//    setFileDownloader(newFileDownloader);
//}
