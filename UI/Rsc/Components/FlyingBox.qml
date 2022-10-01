import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: flyingBox
    property string hiddenText: ""
    property string filePath: ""
    property string backgroundColor: "#fefefe"

    function updateHiddenText(text) {
        hiddenText = text
    }

    Rectangle {
        id: wrapper
        width: parent.width
        height: parent.height
        color: flyingBox.backgroundColor

        Text {
            id: text
            anchors.fill: parent
            text: flyingBox.hiddenText
            font.pixelSize: 10
            font.weight: Font.Thin
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            opacity: 0
            wrapMode: Text.WordWrap
        }

        Image {
            id:image
            source: flyingBox.filePath
            width: sourceSize.width < parent.width ? sourceSize.width : parent.width
            height: sourceSize.height < parent.height ? sourceSize.height : parent.height
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 1
        }

        states: State {
            name: "shown"
            PropertyChanges {
                target: text
                opacity: 1
                font.pixelSize: 30
            }
            PropertyChanges {
                target: image
                opacity: 0.2
                width: sourceSize.width * 1.2
                height: sourceSize.height * 1.2
            }
        }

        transitions: Transition {
            NumberAnimation {
                properties: "opacity, font.pixelSize"
                target: text
            }

            NumberAnimation {
                properties: "width, height, opacity"
                target: image
            }
        }


        MouseArea {
            width: parent.width
            height: parent.height
            hoverEnabled: true

            onEntered: {
                wrapper.state = wrapper.state == "shown" ?
                            wrapper.state = "" : wrapper.state = "shown";
            }

            onExited: {
                wrapper.state = wrapper.state == "shown" ?
                            wrapper.state = "" : wrapper.state = "shown";
            }
        }
    }
}
