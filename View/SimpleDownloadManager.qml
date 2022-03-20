import QtQuick 2.0
import QtQuick.Layouts 1.3
import ir.hcoding.models 1.1 as HCoding
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.1
Rectangle {
    id:simpleDownloadManager
    radius: 6;
    color: "#ededed"
    Item {
        id: props
        HCoding.DownloaderCore{
            id:downloadManagerCore
        }
        InputURLDialog {
            id:inputNewUrl
            width:simpleDownloadManager.width*0.77
            height:simpleDownloadManager.height*0.77
            visible: false;
            onAccepted:{
                downloadManagerCore.startDownloadNewURL(inputNewUrl.url , inputNewUrl.fileAddress);
            }
        }
    }
    ColumnLayout
    {
        anchors.fill:parent
        Button{
            id: insertNewDownload
            text:"add new Download"
            onClicked: inputNewUrl.open();
            Layout.alignment: Qt.AlignHCenter
        }

        Flow{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
            spacing: 10
            Repeater
            {
                id:fileDownloaderRepeater
                model:downloadManagerCore.model
                delegate: Rectangle{
                    id:rootDownloadItemWrapper
                    property var viewDownloaderCore: WorkerInfo
                    Layout.minimumHeight: 150
                    Layout.minimumWidth: 150
                    width:parent.width*0.3
                    height:width
                    color:"transparent"
                    CircularProgressBar
                    {
                        anchors.fill: parent
                        toolTipText:rootDownloadItemWrapper.viewDownloaderCore.url
                        value: rootDownloadItemWrapper.viewDownloaderCore.progressbar;
                        from : 0
                        to : 100
                    }
                }
            }
        }
    }
}
