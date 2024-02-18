import QtQuick 2.15
//import ops.camera.viewport 1.0
Item {
    id: root
    anchors.fill: parent
    anchors.centerIn: parent
    width: 700
    height: 700
    signal mouseMoveSignal(obj: Item)

    Rectangle {
        id: rect
        anchors.centerIn: parent
        width: 500
        height: 500
        border.width: 3
        radius: 3;
        clip: true




        Image {
            id: frameview
            width: parent.width
            height: parent.height
            source: "image://provider/default"
            // sourceSize.width: 900 //TODO From original Pixmap
            // sourceSize.height: 900
            visible: true

            MouseArea {
                id: frameMouseArea
                hoverEnabled: true
                anchors.fill: parent

                Item {
                    id: mousePos
                }

                onPositionChanged: (mouse) => {
                    mousePos.x = frameview.sourceSize.width * mouse.x / frameview.width
                    mousePos.y = frameview.sourceSize.height * mouse.y / frameview.height
                    root.mouseMoveSignal(mousePos)
                }

                onWheel: (wheel) => {

                    if (wheel.modifiers & Qt.ShiftModifier) {
                        frameview.width = frameview.width + wheel.angleDelta.y
                    } else if (wheel.modifiers & Qt.ControlModifier) {
                        frameview.height = frameview.height + wheel.angleDelta.y
                    } else {
                        frameview.width = frameview.width + wheel.angleDelta.y;
                        frameview.height = frameview.height + wheel.angleDelta.y
                    }
                    frameview.width = frameview.width < rect.width ? rect.width : frameview.width
                    frameview.height = frameview.height < rect.height ? rect.height : frameview.height
                    frameview.x = frameview.x > 0 ? frameview.x = 0 : frameview.x
                    frameview.x = frameview.x < -frameview.width + rect.width ? -frameview.width + rect.width : frameview.x
                    frameview.y = frameview.y > 0 ? frameview.y = 0 : frameview.y
                    frameview.y = frameview.y < -frameview.height + rect.height ? -frameview.height + rect.height : frameview.y
                }
            }
            Timer {
                id: frameRefresher
                interval: 25
                repeat: true
                running: true
                onTriggered: () => {
                    frameview.source = ""
                    frameview.source = "image://provider/LiveFrame"
                    text.text = frameview.sourceSize.toString()
                    frameview.width = frameview.width > rect.width ? frameview.width : rect.width
                    frameview.height = frameview.height > rect.height ? frameview.height : rect.height

                }
            }
        }

        MouseArea {
            id: rectMouseArea
            anchors.fill: parent
            drag.target: frameview
            drag.filterChildren: true
            drag.minimumX: -frameview.width + rect.width
            drag.maximumX: 0
            drag.minimumY: -frameview.height + rect.height
            drag.maximumY: 0
            onDoubleClicked: () => {
                frameview.x = 0
                frameview.y = 0
                frameview.width = parent.width
                frameview.height = parent.height
            };
        }
        Text {
            id: text
            text: "Hello World!"
            // font.family: "Helvetica"
            font.pointSize: 24
            color: "black"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
        }
    }
}