import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id:root
    property color bgColor: "#e8dbb7"
    property color usageColor: "#16821c"
    property real from: 0
    property real to: 100
    property real value: 0
    property color titleColor : "#3b0069"
    property string title: value.toFixed(2) + "%"
    property string toolTipText: ""
    signal clicked()
    onClicked: console.log("clicked")
    onValueChanged: {
        if(value>to)
            value = to;
        usageCanvas.requestPaint();
    }
    Behavior on value {
        NumberAnimation{
            duration: 16     // 60 hertz
        }
    }


    property real lineWidth: props.defaultWidth/10

    Item {
        id: props
        property real defaultWidth: Math.min(root.width,root.height)
        property real defaultHeight: props.defaultWidth
        readonly property real totalAngle: 2*Math.PI
        function clearCtx(context){
            context.reset();
        }
    }
    Text{
        id: title
        text:root.title
        color:root.titleColor
        font.pixelSize: props.defaultWidth/10
        font.bold: true
        anchors.centerIn: parent
    }
    ToolTip{
        id:tltip
        text: root.toolTipText
    }

    Canvas{
        id:bgCanvas
        anchors.centerIn: parent
        width: props.defaultWidth
        height: props.defaultHeight
        onPaint: {
            var ctx = bgCanvas.getContext("2d");
            props.clearCtx(ctx);        //FIXME on Test
            // init style before start
            ctx.strokeStyle = root.bgColor;
            ctx.lineWidth = root.lineWidth;
            ctx.lineCap = "round";
            ctx.beginPath();
            var startAngle = -Math.PI;
            var stopAngle = -3*Math.PI;
            ctx.arc(props.defaultWidth/2 , props.defaultHeight/2 , props.defaultWidth/2-root.lineWidth , startAngle , stopAngle,false);
            ctx.stroke();
        }
    }
    Canvas{
        id:usageCanvas
        anchors.centerIn: parent
        width: bgCanvas.width
        height: bgCanvas.height
        onPaint: {
            var ctx = usageCanvas.getContext("2d");
            props.clearCtx(ctx);
            // init style before start
            ctx.strokeStyle = root.usageColor;
            ctx.lineWidth = root.lineWidth;
            ctx.lineCap = "round";
            ctx.beginPath();
            var startAngle = 0;
            var stopAngle = root.value * props.totalAngle / (root.to-root.from);
            ctx.arc(props.defaultWidth/2 , props.defaultHeight/2 , props.defaultWidth/2-root.lineWidth , startAngle , stopAngle , false);
            ctx.stroke();
        }
    }
    MouseArea{
        anchors.fill: parent;
        hoverEnabled: true
        onEntered:tltip.visible=true;
        onExited: tltip.visible=false;
        onClicked: {
            root.clicked();
        }
    }
}
