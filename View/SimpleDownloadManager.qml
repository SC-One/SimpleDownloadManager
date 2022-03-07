import QtQuick 2.0
import QtQuick.Layouts 1.3
Rectangle {
    radius: 6;
    gradient: Gradient.NighFade

    GridLayout
    {
        anchors.fill:parent
        Repeater
        {
            id:fileDownloaderRepeater
        }
    }
}
