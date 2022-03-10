import QtQuick 2.0
import QtQuick.Layouts 1.3
import ir.hcoding.models 1.1 as HCoding
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.1
Rectangle {
    id:simpleDownloadManager
    radius: 6;
    color:"gray"
//    gradient:  Gradient {
//        GradientStop {
//            position: 0.0
//            SequentialAnimation on color {
//                loops: Animation.Infinite
//                ColorAnimation { from: "#14148c"; to: "#0E1533"; duration: 5000 }
//                ColorAnimation { from: "#0E1533"; to: "#14148c"; duration: 5000 }
//            }
//        }
//        GradientStop {
//            position: 1.0
//            SequentialAnimation on color {
//                loops: Animation.Infinite
//                ColorAnimation { from: "#14aaff"; to: "#437284"; duration: 5000 }
//                ColorAnimation { from: "#437284"; to: "#14aaff"; duration: 5000 }
//            }
//        }
//    }
    Item {
        id: props
        HCoding.DownloaderCore{
            id:downloadManagerCore
//            onSizeOfModelChanged:
//                simpleDownloadManager.list = downloadManagerCore.model();
        }
        FileDialog{
            id:saveFile
            onAccepted: fileAddress.text = fileUrl;
        }

    }

    Action{
        onTriggered: saveFile.open();
    }

    ColumnLayout
    {
        anchors.fill:parent
        RowLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
            TextInput{
                id:url
                Layout.fillWidth: true
                text:"http://www.iran.ir/"
            }
            TextInput{
                id:fileAddress
                Layout.maximumWidth: 100
                text:"file:///home/sc/prj/Qt/SimpleDownloadManager/build-SimpleDownloadManager-Desktop_Qt_5_15_2_GCC_64bit-Debug/MyFile"
                Layout.fillWidth: true
                onFocusChanged: {
                    if(focus)
                    {
                        saveFile.open();
                    }
                }
            }
            Button{
                text:"Download"
                onClicked: downloadManagerCore.startDownloadNewURL(url.text , fileAddress.text);
            }
        }

        GridLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
            columns: 1
            Repeater
            {
                id:fileDownloaderRepeater
                model:downloadManagerCore.model
                delegate: Rectangle{
                    id:rootDownloadItemWrapper
                    property var viewDownloaderCore: WorkerInfo
                    Layout.minimumHeight: 70
                    Layout.minimumWidth: childrenRect.width
                    color:"white"
                    RowLayout{
                        anchors.fill: parent
                        Text{
                            id:urlText
                            text: rootDownloadItemWrapper.viewDownloaderCore.url
                        }
                        ProgressBar {
                            width: 140
                            height:20
                            Layout.fillWidth: true;
                            value: rootDownloadItemWrapper.viewDownloaderCore.progressbar;
                            from : 0
                            to : 100
                        }
                        Text{
                            id:nameText
                            text: rootDownloadItemWrapper.viewDownloaderCore.fileAddress
                        }
                    }
                }
            }
        }
    }
}
