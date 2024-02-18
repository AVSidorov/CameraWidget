import QtQuick 2.15
//import ops.camera.viewport 1.0
Item {
    id: root
    anchors.fill: parent
    anchors.centerIn: parent

    signal mouseMoveSignal(obj: Item)

    Rectangle {
        id: rect
        anchors.centerIn: parent
        width: 100
        height: 100
        anchors.margins: 33
        border.width: 10
        radius: border.width;
        clip: true

        Image {
            id: frameview
            // anchors.fill blocks zooming
            width: parent.width
            height: parent.height
            source: "image://provider/default"

            MouseArea {
                id: frameMouseArea
                hoverEnabled: true
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
                    frameview.width = rect.width
                    frameview.height = rect.height
                };

                Item {
                    id: mousePos
                }

                onPositionChanged: (mouse) => {
                    mousePos.x = frameview.sourceSize.width * mouse.x / frameview.width
                    mousePos.y = frameview.sourceSize.height * mouse.y / frameview.height
                    root.mouseMoveSignal(mousePos)
                }

                onWheel: (wheel) => {
                    var r = frameview.width/frameview.height

                    if (wheel.modifiers & Qt.ShiftModifier) {
                        frameview.width = frameview.width + wheel.angleDelta.y
                    } else if (wheel.modifiers & Qt.ControlModifier) {
                        frameview.height = frameview.height + wheel.angleDelta.y
                    } else {
                        frameview.width = frameview.width + wheel.angleDelta.y
                        frameview.height = frameview.width/r
                    }
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


                    // adjust rect
                    var r = frameview.sourceSize.width/frameview.sourceSize.height
                    rect.width = root.height  * r;
                    rect.height = rect.width / r;
                    if (rect.width > root.width | rect.height>root.height){
                        rect.height = root.width / r
                        rect.width = rect.height * r
                    }

                    // adjust frame to rect
                    frameview.width = frameview.width < rect.width ? rect.width : frameview.width
                    frameview.height = frameview.height < rect.height ? rect.height : frameview.height
                    frameview.x = frameview.x > 0 ?  0 : frameview.x
                    frameview.x = frameview.x < -frameview.width + rect.width ? -frameview.width + rect.width : frameview.x
                    frameview.y = frameview.y > 0 ?  0 : frameview.y
                    frameview.y = frameview.y < -frameview.height + rect.height ? -frameview.height + rect.height : frameview.y

                }
            }
        }
    }
}