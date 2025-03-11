import QtQuick 2.15

Item {
    id: lineItem
    property real value: 0
    property real maxValue: 100
    width: parent.width
    height: parent.height

    signal animationFinished()

    Rectangle {
        width: parent.width
        height: 2
        color: "blue"
        y: (1 - (value / maxValue)) * parent.height

        Text {
            text: Math.round(value)
            color: "black"
            anchors.right: parent.right
        }

        NumberAnimation on y {
            to: parent.height
            duration: 3000
            easing.type: Easing.Linear
            onStopped: animationFinished()
        }
    }
}
