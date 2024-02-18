import QtQuick 2.15
import QtQuick.Controls 2.15


Item{
    id: root
    anchors.fill: parent
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


        Image{
            id: frameview
            width: 900
            height: 900
            // source: "images/pr.png"
            source: "image://colors/red"
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
            Timer{
                id: frameRefresher
                interval: 25
                repeat: true
                onTriggered: ()=> {
                    frameview.source = ""
                    frameview.source = "image://colors/LiveFrame"
                    frameview.width = frameview.width > rect.width ? frameview.width : rect.width
                    frameview.height = frameview.height > rect.height ? frameview.height : rect.height
                }
            }
        }

        MouseArea {
            id: rectMouseArea
            anchors.fill: parent
            // hoverEnabled: true

            drag.target: frameview
            drag.filterChildren: true
            drag.minimumX: -frameview.width+rect.width
            drag.maximumX: 0
            drag.minimumY: -frameview.height + rect.height
            drag.maximumY: 0
            onClicked: ()=>{
                root.qmlSignal(frameview)
                frameRefresher.start()
                // root.msgSignal("Hello from QML")
            }
            onDoubleClicked: ()=>{
                frameview.x = 0
                frameview.y = 0
                frameview.width = parent.width
                frameview.height = parent.height
                // root.msgSignal("Hello from QML")
            };

            onWheel: (wheel)=> {

                if(wheel.modifiers & Qt.ShiftModifier){
                    frameview.width = frameview.width + wheel.angleDelta.y
                }
                else if(wheel.modifiers & Qt.ControlModifier){
                    frameview.height = frameview.height + wheel.angleDelta.y
                }
                else {
                    frameview.width =  frameview.width + wheel.angleDelta.y;
                    frameview.height = frameview.height + wheel.angleDelta.y
                }
                frameview.width = frameview.width < rect.width ? rect.width : frameview.width
                frameview.height = frameview.height < rect.height ? rect.height : frameview.height
                frameview.x = frameview.x > 0 ? frameview.x = 0 : frameview.x
                frameview.x = frameview.x < -frameview.width + rect.width ? -frameview.width + rect.width: frameview.x
                frameview.y = frameview.y > 0 ? frameview.y = 0 : frameview.y
                frameview.y = frameview.y < -frameview.height + rect.height ? -frameview.height + rect.height: frameview.y
            }

        }



        MouseArea{
            id: mouseAreaLeft
            anchors.left: parent.left
            anchors.top: parent.top
            width: 33
            height: parent.height
            hoverEnabled: true;
        }
        Rectangle{
            id: leftInfo
            color: "gray"
            opacity:0.3
            visible: mouseAreaLeft.containsMouse | mouseAreaLeftInfo.containsMouse
            width: parent.width/5
            height: parent.height
            MouseArea{
                id: mouseAreaLeftInfo
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }

 }

