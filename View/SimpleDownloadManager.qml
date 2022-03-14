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
        ColumnLayout
        {
            Layout.fillWidth: true
//            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
            TextInput{
                id:url
//                Layout.fillHeight: true
                text:"https://camo.githubusercontent.com/52fa9afe98c94dc246c5d9db604e9f214cff1994a2b4974d96ee1f3dd5f0da80/68747470733a2f2f73362e7575706c6f61642e69722f66696c65732f64726f705f646f776e5f696e7075745f746578745f696e5f716d6c5f7461392e676966"
            }
            TextInput{
                id:fileAddress
                Layout.minimumHeight: 70
                Layout.maximumHeight: 100
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

        ColumnLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
//            columns: 1
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
                    ColumnLayout{
                        anchors.fill: parent
                        Text{
                            id:urlText
                            Layout.minimumHeight: 77;
                            Layout.fillWidth: true;
                            text: rootDownloadItemWrapper.viewDownloaderCore.url
                        }
                        ProgressBar {
                            width: 140
                            height:100
                            Layout.fillWidth: true;
                            Layout.minimumHeight: 100;
                            Layout.maximumHeight: 200;
                            Layout.minimumWidth: 140;
                            ToolTip{
                                id:tltip
                                text: "Value: 0";
                            }

                            MouseArea{
                                anchors.fill: parent
                                hoverEnabled: true
                                onExited: tltip.visible=false;
                                onEntered: tltip.visible=true;
                            }
                            property int  index: 0
                            value: rootDownloadItemWrapper.viewDownloaderCore.progressbar;
                            onValueChanged:{
                                tltip.text = "Value: "+value;
                                index++;
                                console.log("index",index);
                        }
                            from : 0
                            to : 100
                        }
                        Text{
                            id:nameText
                            Layout.fillWidth: true;
                            Layout.minimumHeight: 77;
                            text: rootDownloadItemWrapper.viewDownloaderCore.fileAddress
                        }
                    }
                }
            }
        }
    }
}
