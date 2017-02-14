import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3


import "orek.js" as Orek



Rectangle {
    color: orekActive.alternateBase
    anchors.fill: parent

    function load() {
        Orek.getAllUsers( function(jsonContent) {
            userModel.json = jsonContent.toString()
        }, function(errorContent) {
            console.log(errorContent)
        });
    }
    JSONListModel {
        id: userModel
    }
    ColumnLayout {
        id: colmn
        anchors.fill: parent
        spacing: 0
        anchors.margins: 0

        RowLayout {
            id: userOperations
            anchors.margins: 0
            Layout.minimumHeight: 30
            Layout.preferredHeight: 30
            Layout.maximumHeight: 30
            Layout.fillHeight: true
            Layout.fillWidth: true
            width: colmn.width
            Button {
                height: Layout.height
                id: selectAll
                text: qsTr("Select All")
                onClicked: {
                    userTable.selection.selectAll()
                }
            }
            Button {
                height: Layout.height
                id: deselectAll
                text: qsTr("DeslectAll")
                onClicked: {
                    userTable.selection.deselect(0, userTable.rowCount - 1)
                }
            }
            Button {
                height: Layout.height
                id: createUserBtn
                text: qsTr("Create User")
                onClicked: console.log("Create user...")
            }
            Button {
                height: Layout.height
                id: editUser
                text: qsTr("Edit User")
                onClicked: console.log("Edit user...")
            }
            Button {
                height: Layout.height
                id: deleteUser
                text: qsTr("Delete User")
                onClicked: console.log("Delete user...")
            }
        }
        TableView {
            id: userTable
            model: userModel.model
            height: parent.height - userOperations.height
            Component.onCompleted: load()
            onVisibleChanged: load()
            selectionMode: SelectionMode.NoSelection
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 600
            Layout.preferredHeight: parent.height
            onSelectionChanged: {

            }

            TableViewColumn {
                id: checkedCol
                role:  "checked"
                title: ""
                width: 20
                delegate: CheckboxDelegate {
                    table: userTable
                }
            }
            TableViewColumn {
                role: "name"
                title: "User Name"
                width: 100
            }
            TableViewColumn {
                role: "email"
                title: "Email"
                width: 200
            }
            TableViewColumn {
                role: "firstName"
                title: "First Name"
                width: 200
            }
            TableViewColumn {
                role: "secondName"
                title: "Second Name"
            }
        }
    }
}

