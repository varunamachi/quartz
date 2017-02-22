import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

import qz.app 1.0 as Qz
import "orek.js" as Orek

Rectangle {
    function getGroupProperty(propName) {
        if(createDialog.isEdit && createDialog.group) {
            return createDialog.group[propName]
        }
        return ""
    }
    Dialog {
        property bool isEdit: false
        property var group
        id: createDialog
        width: 400
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            var group = {}
            group["userGroupID"] = groupID.text
            group["userGroupName"] = groupName.text
            group["userGroupOwner"] = owner.text
            group["userGroupDesc"] = desc.text
            var func = isEdit ? Orek.updateGroup : Orek.createGroup
            func(group,
                 function(msg) {
                     Qz.Service.info( "Orek",
                                     qsTr("Group %1 create/edit successfull")
                                     .arg(groupName.text))
                     load()
                 },
                 function(msg) {
                     Qz.Service.info( "Orek",
                                     qsTr( "Group %1 create/edit failed" )
                                     .arg(groupName.text))
                     load()
                 }
            );
        }
        GridLayout {
            columns: 2
            anchors.fill: parent
            Label {
                text: qsTr("Group ID")
            }
            TextField {
                id: groupID
                placeholderText: qsTr("Enter Group ID")
                text: getUserProperty("userGroupID")
                Layout.fillWidth:  true
                enabled: !createDialog.isEdit
            }

            Label {
                text: qsTr("Group Name")
            }
            TextField {
                id: groupName
                placeholderText: qsTr("Enter Group Name")
                text: getUserProperty("userGroupName")
                Layout.fillWidth:  true
            }

            Label {
                text: qsTr("Owner")
            }
            TextField {
                id: owner
                placeholderText: qsTr("Enter Group Owner")
                text: getUserProperty("userGroupOwner")
                Layout.fillWidth:  true
            }

            Label {
                text: qsTr("Description")
            }
            TextField {
                id: desc
                placeholderText: qsTr("Enter Description")
                text: getUserProperty("userGroupDesc")
                Layout.fillWidth:  true
            }
        }
    }


    color: orekActive.alternateBase
    anchors.fill: parent

    function load() {
        Orek.getAllGroups( function(jsonContent) {
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
                        var group = model.model.get(i)
                        if(group.selected === true) {
                            createDialog.group = group
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
                        var group = model.model.get(i)
                        if(group.selected === true) {
                            Orek.deleteUser(group.userGroupID,
                                 function(msg) {
                                     load()
                                 },
                                 function(msg) {
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
//            Layout.minimumHeight: 600
            Layout.preferredHeight: parent.height

            itemDelegate: Text {
                text: styleData.value
                color: model.selected ? "#e67e00"
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
                role: "userGroupID"
                title: "Group ID"
                width: 100
            }
            TableViewColumn {
                role: "userGroupName"
                title: "Group Name"
                width: 200
            }
            TableViewColumn {
                role: "userGroupOwner"
                title: "Owner"
                width: 200
            }
            TableViewColumn {
                role: "userGroupDesc"
                title: "Description"
            }
        }
    }
}
