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
    property var list: [];
    Item {
        id: props
        HCoding.DownloaderCore{
            id:downloadManagerCore
            onSizeOfModelChanged:
                simpleDownloadManager.list = downloadManagerCore.model();
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
            TextInput{
                id:url
                Layout.fillWidth: true
                text:"http://dl.golsarmusic.ir/GolsarMusic-Root/99/07%20Mehr/15/cuban%20pete.mp3"
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
            Layout.fillHeight: true
            Repeater
            {
                id:fileDownloaderRepeater
                model:downloadManagerCore.sizeOfModel
                delegate: Rectangle{
                    Layout.minimumHeight: 50
                    Layout.minimumWidth: 170
                    color:"white"
                    RowLayout{
                        anchors.fill: parent
                        Text{
                            id:nameText
                            text: simpleDownloadManager.list[fileDownloaderRepeater.count].fileAddress
                        }
                        ProgressBar {
                            Layout.fillWidth: true
                            value: simpleDownloadManager.list[fileDownloaderRepeater.count].progressbar;
                            from : 0
                            to : 100
                        }
                        Text{
                            id:urlText
                            text: simpleDownloadManager.list[fileDownloaderRepeater.count].url
                        }
                    }
                }
            }
        }
    }
}
