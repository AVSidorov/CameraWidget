import QtQuick 2.15
import QtQuick.Controls 2.15


Item{
    id: root
    width: 500
    height: 500

    signal qmlSignal(anObject: Item)
    signal msgSignal(msg: string)
    signal mouseMoveSignal(obj: Item)

    Rectangle{
        id: rect
        anchors.centerIn: parent
        // anchors.fill: parent
        width: parent.width>910 ? 900 : parent.width-10
        height: parent.height>910 ? 900 : parent.height-10
        border.width: 1
        clip: true



        Image {
            id: frameview
            width: 900
            height: 900
            source: "images/pr.png"
            sourceSize.width: 900
            sourceSize.height: 900
            visible: true
            MouseArea{
                id: frameMouseArea
                hoverEnabled: true
                anchors.fill: parent
                Item{
                    id: mousePos
                }
                onPositionChanged: (mouse) =>{
                    mousePos.x = frameview.sourceSize.width * mouse.x / frameview.width
                    mousePos.y = frameview.sourceSize.height * mouse.y / frameview.height
                    root.mouseMoveSignal(mousePos)
                }
            }
        }

        MouseArea {
            id: rectMouseArea
            anchors.fill: parent
            // hoverEnabled: true

            drag.target: frameview
            drag.filterChildren: true
            drag.minimumX: -frameview.width+10
            drag.maximumX: rect.width-10
            drag.minimumY: -frameview.height + 10
            drag.maximumY: rect.height - 10
            // onClicked: frameview.visible = frameview.visible ^ true;
            onClicked: ()=>{
                root.qmlSignal(frameview)
                // root.msgSignal("Hello from QML")
            }
            onDoubleClicked: ()=>{
                frameview.x = 0
                frameview.y = 0
                frameview.width = parent.width
                frameview.height = parent.height
            };

            onWheel: (wheel)=> {

                if(wheel.modifiers & Qt.ShiftModifier){
                    frameview.width = frameview.width + wheel.angleDelta.y
                }
                else if(wheel.modifiers & Qt.ControlModifier){
                    frameview.height = frameview.height + wheel.angleDelta.y
                }
                else {
                    frameview.width = frameview.width + wheel.angleDelta.y
                    frameview.height = frameview.height + wheel.angleDelta.y
                }
            }

        }

    }


 }

