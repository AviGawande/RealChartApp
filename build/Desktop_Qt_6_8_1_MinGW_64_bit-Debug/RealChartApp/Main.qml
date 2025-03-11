import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Real-Time Chart App"
    color: "#1a1a1a"  // Dark theme background

    header: ToolBar {
        background: Rectangle {
            color: "#2a2a2a"
        }
        RowLayout {
            anchors.fill: parent
            spacing: 10
            Button {
                text: "Start UDP"
                onClicked: dataModel.startUdpReceiver()
            }
            Button {
                text: "Stop UDP"
                onClicked: dataModel.stopUdpReceiver()
            }
            Label {
                Layout.fillWidth: true
                text: "Real-Time Chart App"
                horizontalAlignment: Text.AlignHCenter
                color: "white"
                font.pixelSize: 16
            }
        }
    }
    // Your existing WaterfallChart component
    WaterfallChart {
        anchors.fill: parent
    }
}
