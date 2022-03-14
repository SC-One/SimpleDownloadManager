import QtQuick 2.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Dialog {
    id:rootDialog
    title: "Add new download Item"
    property alias url: linkText.text
    property alias fileAddress: fileLocation.text
    function resetInternalAddresses(){
        url="https://camo.githubusercontent.com/7659176ba6d3ca1d608f17d5"+
                "f88cbcd6ab31e960cb03369a46e2ac8dcb164aff/68747470733a2f2f73362e"+
                "7575706c6f61642e69722f66696c65732f726573706f6e736976655f616e616"+
                "c6f675f636c6f636b5f716d6c5f386731312e676966";
        fileAddress = "";
    }

    onVisibleChanged:
    {
        if(visible){
            resetInternalAddresses();
        }
    }
    function isValidURL(str) {
        var regexpHttp = /(ftp|http|https):\/\/(\w+:{0,1}\w*@)?(\S+)(:[0-9]+)?(\/|\/([\w#!:.?+=&%@!\-\/]))?/i
        var regexpWWW = /(www|www|www).(\w+:{0,1}\w*@)?(\S+)(:[0-9]+)?(\/|\/([\w#!:.?+=&%@!\-\/]))?/i
        return regexpHttp.test(str) || regexpWWW.test(str);
    }
    FileDialog{
        id:saveFile
        onAccepted: fileLocation.text = fileUrl;
    }

    contentItem: Rectangle {
        color: "#bab3ff"
        ColumnLayout{
            width:parent.width*0.77
            height:parent.height*0.77
            anchors.centerIn: parent
            GridLayout{
                Layout.maximumHeight: childrenRect.height
                columns:2
                Text {
                    text: "Url Link: "
                    color: "navy"
                }
                TextField {
                    id:linkText
                    Layout.fillWidth: true
                    Layout.minimumHeight: 50
                    background:Rectangle {
                        border.color: "gray"
                        border.width: 1
                        radius:2;
                    }
                }
                Text {
                    text: "File location to save: "
                    color: "navy"
                }
                TextField{
                    id:fileLocation
                    Layout.fillWidth: true
                    Layout.minimumHeight: 50
                    onFocusChanged: {
                        if(focus)
                        {
                            saveFile.open();
                        }
                    }
                }
            }
            Item{Layout.fillHeight: true;}
            RowLayout{
                Item {Layout.fillWidth: true}
                Button{
                    width:parent.width*0.4
                    height:70
                    text:"Download"
                    enabled: rootDialog.isValidURL(rootDialog.url)
                             && inputNewUrl.url != ""
                             && inputNewUrl.fileAddress != "";
                    onClicked: {
                        rootDialog.accept();
                    }
                }
                Button{
                    text:"close"
                    onClicked: rootDialog.close();
                }
                Item {Layout.fillWidth: true}
            }
        }

    }
}
