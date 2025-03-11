import QtQuick 2.15

Rectangle {
    id: root
    color: "#313244"
    radius: 8
    property int maxVisible: 15
    property real maxValue: 100
    // Chart content
    Item {
        id: chartContent
        anchors.fill: parent
        anchors.margins: 20
        clip: true
        // Grid lines
        Repeater {
            model: 5
            Rectangle {
                width: parent.width
                height: 1
                color: "#45475a"
                y: index * (parent.height / 4)
                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: -30
                    anchors.verticalCenter: parent.verticalCenter
                    text: Math.round(maxValue - (index * (maxValue / 4)))
                    color: "#cdd6f4"
                    font.pixelSize: 10
                }
            }
        }
        // Data lines container
        Item {
            id: linesContainer
            anchors.fill: parent
        }
    }

    // Connect to the data model
    Connections {
        target: dataModel
        function onNewDataPoint(value) {
            console.log("Received Data:", value);
            createNewLine(value);
        }
    }

    // Create a new line when data is received
    function createNewLine(value) {
        // Create the line component inline instead of loading from a file
        var line = Qt.createQmlObject(
            'import QtQuick 2.15; ' +
            'Item { ' +
                'parent: linesContainer; ' +
                'id: lineItem; ' +
                'property real value: ' + value + '; ' +
                'property real maxValue: ' + root.maxValue + '; ' +
                'width: parent.width; ' +
                'height: parent.height; ' +
                'Rectangle { ' +
                    'id: dataLine; ' +
                    'width: parent.width; ' +
                    'height: 2; ' +
                    'radius: 1; ' +
                    'y: (1 - (value / maxValue)) * parent.height -2; ' +
                    'color: { ' +
                        'var hue = (1 - (value / maxValue)) * 240; ' +
                        'return Qt.hsla(hue/360, 0.8, 0.6, 1); ' +
                    '}; ' +
                '}; ' +
                'Text { ' +
                    'anchors.right: parent.right; ' +
                    'anchors.rightMargin: 10; ' +
                    'anchors.verticalCenter: dataLine.verticalCenter; ' +
                    'text: Math.round(value); ' +
                    'color: "#cdd6f4"; ' +
                    'font.pixelSize: 10; ' +
                '}; ' +
                'NumberAnimation { ' +
                    'target: lineItem; ' +
                    'property: "y"; ' +
                    'from: 0; ' +
                    'to: parent.height; ' +
                    'duration: 8000; ' +
                    'easing.type: Easing.Linear; ' +
                    'running: true; ' +
                    'onStopped: { lineItem.destroy(); }; ' +
                '}; ' +
            '}',
            linesContainer,
            "dynamicLine"
        );
        // Remove oldest line if we have too many
        var children = linesContainer.children;
        if (children.length > maxVisible) {
            children[0].destroy();
        }
    }
}
