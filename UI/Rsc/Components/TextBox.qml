import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: textBox
    signal textEntered(string query)
    property int fontSize: 55
    property string backgroundColor: "#fefefe"

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: textBox.backgroundColor

        StackView {
            id: stackView
            anchors.fill: parent
            initialItem: mouseArea

            TextInput {
                id: textInput
                width: parent.width
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: "Your City"
                font.pixelSize: textBox.fontSize
                font.weight: Font.Thin
                selectByMouse: true
                selectedTextColor: "black"
                selectionColor: "gray"

                onAccepted: {
                    stackView.replace(mouseArea)
                    textEntered(textInput.text)
                }
            }

            MouseArea {
                id: mouseArea
                width: parent.width
                height: parent.height
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    stackView.replace(textInput)
                }
               Text {
                   horizontalAlignment: Text.AlignHCenter
                   verticalAlignment: Text.AlignVCenter
                   id: textField
                   width: parent.width
                   height: parent.height
                   text: textInput.text
                   font.pixelSize: textBox.fontSize
                   font.weight: Font.Thin
               }
            }
        }
    }
}
