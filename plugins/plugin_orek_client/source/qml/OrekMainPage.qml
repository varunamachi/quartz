import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

Item {
    anchors.fill: parent
    ListModel {
        id: menuModel
        ListElement {
            name: "User"
            idx: 0
        }
        ListElement {
            name: "Group"
            idx: 1
        }
        ListElement {
            name: "Endpoints"
            idx: 2
        }
        ListElement {
            name: "Variables"
            idx: 3
        }
        ListElement {
            name: "Parameters"
            idx: 4
        }
    }
    Component {
        id: menuDelegate
        Rectangle {
            id: wrapper
            width: parent.width
            height: menuItem.height
            color: ListView.isCurrentItem ? "#FFA858" : "transparent"
            Text {
                id: menuItem
                text: name
                font.pointSize: 14
                //                color: ListView.isCurrentItem ? "black" : "white"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    menuView.currentIndex = index
                    stackView.currentIndex = idx
                }
            }
        }
    }
    RowLayout {
        id: layout
        anchors.fill: parent
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 80
            Layout.maximumWidth: 120
            Layout.preferredHeight: parent.height
            ListView {
                id: menuView
                width: parent.width
                height: parent.height
                model: menuModel
                delegate:  menuDelegate
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: parent.height
            StackLayout {
                id: stackView
                currentIndex: 0
                width: parent.width
                height: parent.height
                UserPage {
                    id: userPage
                    width: parent.width
                    height: parent.height
                }
                GroupPage {
                    id: groupPage
                    width: parent.width
                    height: parent.height
                }
                EndpointPage {
                    id: endpointPage
                    width: parent.width
                    height: parent.height
                }
                VariablePage {
                    id: variablePage
                    width: parent.width
                    height: parent.height
                }
                ParameterPage {
                    id: parameterPage
                    width: parent.width
                    height: parent.height
                }
            }
        }
    }

}
