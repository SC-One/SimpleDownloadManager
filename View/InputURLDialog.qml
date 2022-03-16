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
        url="http://0.0.0.0:8080/file20.txt";
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
