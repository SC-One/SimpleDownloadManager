import QtQuick 2.15
import QtQuick.Window 2.15
import "View" as SimpleDownloadManagerView
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Simple DownloadManager")
    SimpleDownloadManagerView.SimpleDownloadManager{
        anchors.fill: parent
    }

//    SimpleDownloadManagerView.CircularProgressBar{
//        id:circle
//        anchors.centerIn: parent
//        width:parent.width*0.8
//        height:parent.height*0.8
//        onClicked: circle.value+=12.5;
//    }
}
