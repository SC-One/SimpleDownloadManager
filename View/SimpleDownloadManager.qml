import QtQuick 2.0
import QtQuick.Layouts 1.3
import ir.hcoding.models 1.0 as HCoding
import QtQuick.Controls 2.15
Rectangle {
    radius: 6;
    gradient: Gradient.NighFade
    Item {
        id: props
        HCoding.DownloaderCore{
            id:downloadManagerCore
        }
    }
    GridLayout
    {
        anchors.fill:parent
        Repeater
        {
            id:fileDownloaderRepeater
            model:downloadManagerCore.workerSize
            delegate: ProgressBar {
                value: 0.5
                indeterminate: true
            }
        }
    }
}
