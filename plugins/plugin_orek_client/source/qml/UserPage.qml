import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

import "orek.js" as Orek
import "common.js" as Utils

Rectangle {
    function getUserProperty(propName) {
        if(createDialog.isEdit && createDialog.user) {
            return createDialog.user[propName]
        }
        return ""
    }
    MessageDialog {
        id: resultDialog
    }

    Dialog {
        property bool isEdit: false
        property var user
        id: createDialog
        width: 400
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            var user = {}
            user["name"] = userName.text
            user["email"] = userEmail.text
            user["firstName"] = userFirstName.text
            user["secondName"] = userSecondName.text
            var func = isEdit ? Orek.updateUser : Orek.createUser
            func(user,
                 function(msg) {
                     Utils.showResult(resultDialog, msg)
                     load()
                 },
                 function(msg) {
                     Utils.showResult(resultDialog, msg)
                     load()
                 }
            );
        }

        GridLayout {
            columns: 2
            anchors.fill: parent
            Label {
                text: qsTr("User Name")
            }
            TextField {
                id: userName
                placeholderText: qsTr("Enter user name")
                text: getUserProperty("name")
                Layout.fillWidth:  true
                enabled: !createDialog.isEdit
            }

            Label {
                text: qsTr("Email")
            }
            TextField {
                id: userEmail
                placeholderText: qsTr("Enter the user email")
                text: getUserProperty("email")
                Layout.fillWidth:  true
            }

            Label {
                text: qsTr("First Name")
            }
            TextField {
                id: userFirstName
                placeholderText: qsTr("First name of the user")
                text: getUserProperty("firstName")
                Layout.fillWidth:  true
            }

            Label {
                text: qsTr("Second Name")
            }
            TextField {
                id: userSecondName
                placeholderText: qsTr("Second name of the user")
                text: getUserProperty("secondName")
                Layout.fillWidth:  true
            }
        }
    }
    MessageDialog {
        id: confirmDialog
        title: qsTr("Delete User")
        text: qsTr("Do really want to delete the user(s)")
    }

    color: orekActive.alternateBase
    anchors.fill: parent

    function load() {
        Orek.getAllUsers( function(jsonContent) {
            model.json = jsonContent.toString()
        }, function(errorContent) {
            console.log(errorContent)
        });
    }
    JSONListModel {
        id: model
    }
    ColumnLayout {
        id: colmn
        anchors.fill: parent
        spacing: 0
        anchors.margins: 0

        RowLayout {
            id: operations
            anchors.margins: 0
            Layout.minimumHeight: 30
            Layout.preferredHeight: 30
            Layout.maximumHeight: 30
            Layout.fillHeight: true
            Layout.fillWidth: true
            width: colmn.width
            Button {
                height: Layout.height
                id: create
                text: qsTr("Create")
                onClicked: {
                    createDialog.isEdit = false
                    createDialog.open()
                }
            }
            Button {
                height: Layout.height
                id: editSelected
                text: qsTr("Edit")
                onClicked: {
                    createDialog.isEdit = true
                    for(var i = 0; i < model.count; i++) {
                        var user = model.model.get(i)
                        if(user.selected === true) {
                            createDialog.user = user
                            createDialog.open()
                            break
                        }
                    }
                }
            }
            Button {
                id: deleteSelected
                height: Layout.height
                text: qsTr("Delete")
                onClicked: {
                    for(var i = 0; i < model.count; i++) {
                        var user = model.model.get(i)
                        if(user.selected === true) {
                            Orek.deleteUser(user.name,
                                 function(msg) {
                                     Utils.showResult(resultDialog, msg)
                                     load()
                                 },
                                 function(msg) {
                                     Utils.showResult(resultDialog, msg)
                                     load()
                                 }
                            );
                            break
                        }
                    }

                }
            }
        }
        TableView {
            id: theTable
            model: model.model
            height: parent.height - operations.height
            Component.onCompleted: load()
            onVisibleChanged: load()
            selectionMode: SelectionMode.SingleSelection
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 600
            Layout.preferredHeight: parent.height

            itemDelegate: Text {
                text: styleData.value
                color: model && model.selected ? "#e67e00"
                                               : orekActive.text
            }
            TableViewColumn {
                id: checkedCol
                role:  "selected"
                title: ""
                width: 20
                delegate: CheckboxDelegate {
                    table: theTable
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

