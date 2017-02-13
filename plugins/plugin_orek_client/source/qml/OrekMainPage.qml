import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

Rectangle {
    id: main
    anchors.fill: parent
    color: orekActive.alternateBase
    SystemPalette {
        id: orekActive
        colorGroup: SystemPalette.Active
    }


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
//            color: ListView.isCurrentItem ? "#FFA858" : "red"
            color: orekActive.alternateBase
            Text {
                id: menuItem
                text: name
                font.pointSize: 14
                color: orekActive.windowText
            }
            states: State {
                name: "Current"
                when: wrapper.ListView.isCurrentItem
                PropertyChanges { target: wrapper; color: "#FFA858" }
            }
            transitions: Transition {
                ColorAnimation { properties: "color"; duration: 150 }
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
    StackLayout {
        id: stack
        anchors.fill: parent
        LoginPage {
            id: loginPage
            visible: true
            anchors.fill: parent
            onLoggedIn: {
                stack.currentIndex = 1
            }
            onLogInError: {
                console.log("Login Error: " + error)
            }
        }
        RowLayout {
            id: mainLayout
            visible: false
            spacing: 2
            anchors.fill: parent
            Rectangle {
                Layout.fillWidth: true
                Layout.minimumWidth: 50
                Layout.preferredWidth: 80
                Layout.maximumWidth: 120
                Layout.preferredHeight: parent.height
                color: orekActive.alternateBase
                ListView {
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
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
}
