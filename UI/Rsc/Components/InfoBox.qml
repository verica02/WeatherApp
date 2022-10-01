import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle {
    property string mainText: ""
    property string secondaryText: ""
    property string backgroundColor: "#fefefe"

    id: rect
    color: backgroundColor
    state: "initial"

    states: [
        State {
            name: "initial"
        },
        State {
            name: "greeting"
            PropertyChanges {
                target: image
                source: "qrc:/Icons/greetings_view_image"
            }
        },
        State {
            name: "validQuery"
        },
        State {
            name: "invalidQuery"
            PropertyChanges {
                target: image
                source: "qrc:/Icons/invalid_view_image"
            }
        }
    ]

    function onGreeting() {
        mainText = "Hello!"
        secondaryText = "Type your city above"
        rect.state = "greeting"
    }

    function onInvalidQuery(query) {
        mainText = query
        rect.state = "invalidQuery"
        secondaryText = "Resource is unreachable"
    }

    function onValidQuery(temperature, description, filepath) {
        mainText = temperature
        secondaryText = description
        rect.state = "validQuery"
        image.source = filepath
    }

    transitions: Transition {
        ParallelAnimation {
            id: infiniteAnimation
            SequentialAnimation {
                NumberAnimation {
                    target: image
                    properties: "opacity"
                    duration: 2500
                    from: image.opacity
                    to: 0.7
                }
                NumberAnimation {
                    target: image
                    from: 0.7
                    to: 1
                    properties: "opacity"
                    duration: 2500
                }
            }

            ParallelAnimation {
                SequentialAnimation {
                    NumberAnimation {
                        target: image
                        properties: "width"
                        from: image.imageWidth
                        to: image.imageWidth*0.8
                        duration: 3500
                    }
                    NumberAnimation {
                        target: image
                        properties: "width"
                        from: image.imageWidth*0.8
                        to: image.imageWidth
                        duration: 3500
                    }
                }
            }
            ParallelAnimation {
                SequentialAnimation{
                    NumberAnimation {
                        target:image
                        properties: "height"
                        from: image.imageHeight
                        to: image.imageHeight*0.8
                        duration: 3500
                    }
                    NumberAnimation {
                        target:image
                        properties: "height"
                        from: image.imageHeight*0.8
                        to: image.imageHeight
                        duration: 3500
                    }
                }
            }
            loops: Animation.Infinite
        }
    }

    Row {
        id: row
        height: parent.height
        width: parent.width

        Rectangle {
            id: imageWrapper
            width: parent.width/2
            height: parent.height
            color: rect.color

            Image {
                id: image
                property int imageHeight: sourceSize.height < parent.height ? sourceSize.height : parent.height
                property int imageWidth: sourceSize.width < parent.width ? sourceSize.width : parent.width
                source: "qrc:/Icons/greetings_view_image"
                width: imageWidth
                height: imageHeight
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Column {
            width: parent.width/2
            height: parent.height

            Text {
                id: mainText_

                text: rect.mainText
                width: parent.width
                height: parent.height/2
                font.pixelSize: 32
                font.weight: Font.Thin
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: secondaryText_

                text: rect.secondaryText
                width: parent.width
                height: parent.height/2
                font.pixelSize: 28
                font.weight: Font.Thin
                color: "gray"
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
