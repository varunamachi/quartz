import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

import "common.js" as Utils
import "orek.js" as Orek

Rectangle {
    function load() {
        Orek.getAllUsers( function(jsonContent) {
            model.json = jsonContent.toString()
        }, function(errorContent) {
            Utils.showError(errorContent)
        });
    }

    function getUserProperty(propName) {
        if(createDialog.isEdit && createDialog.user) {
            return createDialog.user[propName]
        }
        return ""
    }

    function removeSelected() {
        for(var i = 0; i < model.count; i++) {
            var user = model.model.get(i)
            var msg = qsTr("Do you really want to delete selected users?")
            if(user.selected === true) {
                if(Utils.confirm(qsTr("Remove Users"), msg)) {
                    var suc = function(msg) {
                        Utils.showResult(msg)
                        load()
                    }
                    var fail = function(msg) {
                        Utils.showResult(msg)
                        load()
                    }
                    Orek.deleteUser(user.name, suc, fail);
                    break
                }
            }
        }
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
                     Utils.showResult(msg)
                     load()
                 },
                 function(msg) {
                     Utils.showResult(msg)
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
    color: orekActive.alternateBase
    anchors.fill: parent

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
                id: remove
                height: Layout.height
                text: qsTr("Delete")
                onClicked: {
                    removeSelected()
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

