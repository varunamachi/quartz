import QtQuick 2.0


Rectangle {
    width: 180; height: 200

    Component {
        id: contactsDelegate
        Rectangle {
            id: wrapper
            width: 180
            height: contactInfo.height
            color: ListView.isCurrentItem ? "black" : "red"
            Text {
                id: contactInfo
                text: name + ": " + number
                color: wrapper.ListView.isCurrentItem ? "red" : "black"
            }
            MouseArea {
                 anchors.fill: parent
                 onClicked: view.currentIndex = index
             }
        }
    }

    ListView {
        id: view
        anchors.fill: parent
        model: ListModel {
            id: list
            ListElement {
                name: "Bill Smith"
                number: "555 3264"
            }
            ListElement {
                name: "John Brown"
                number: "555 8426"
            }
            ListElement {
                name: "Sam Wise"
                number: "555 0473"
            }
        }
        delegate: contactsDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }
}

