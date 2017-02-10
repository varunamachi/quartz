import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    visible: true
    width: 640
    height: 480
    SwipeView {
        id: mainSwipe
        anchors.fill: parent
        width: 640
        height: 480
        GridLayout {
            id: mainGrid
            rows: 2
            columns: 2
            property string color: "red"

            Button {
                text: "One"
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: rec.color = "blue"
            }
            Button {
                text: "two"
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: rec.color = "green"
            }
            Button {
                text: "three"
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: rec.color = "yellow"
            }
            Button {
                text: "four"
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: rec.color = "white"
            }
        }
        Rectangle {
            id: rec
        }
    }
}
