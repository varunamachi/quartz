import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

import "orek.js" as Orek

Rectangle {
    color: orekActive.alternateBase
    anchors.fill: parent

    function loadGroups() {
        Orek.getAllGroups( function(jsonContent) {
            groupModel.json = jsonContent.toString()
        }, function(errorContent) {
            console.log(errorContent)
        });
    }


    JSONListModel {
        id: groupModel
    }
    ColumnLayout {
        id: groupMainLayout
        anchors.fill: parent
        spacing: 0
        anchors.margins: 0

        RowLayout {
            id: groupOperations
            anchors.margins: 0
            Layout.minimumHeight: 30
            Layout.preferredHeight: 30
            Layout.maximumHeight: 30
            Layout.fillHeight: true
            Layout.fillWidth: true
            width: groupMainLayout.width
            Button {
                height: Layout.height
                id: selectAllGroups
                text: qsTr("Select All")
                onClicked: {
                    groupTable.selection.selectAll()
                }
            }
            Button {
                height: Layout.height
                id: deselectAllGroups
                text: qsTr("Deslect All")
                onClicked: {
                    groupTable.selection.deselect(0, groupTable.rowCount - 1)
                }
            }
            Button {
                height: Layout.height
                id: createGroupBtn
                text: qsTr("Create Group")
                onClicked: console.log("Create group...")
            }
            Button {
                height: Layout.height
                id: editGroupBtn
                text: qsTr("Edit Group")
                onClicked: console.log("Edit group...")
            }
            Button {
                height: Layout.height
                id: deleteGroupBtn
                text: qsTr("Delete Group")
                onClicked: console.log("Delete Group...")
            }
        }
        TableView {
            id: groupTable
            model: groupModel.model
            Component.onCompleted: loadGroups()
            onVisibleChanged: loadGroups()
            selectionMode: SelectionMode.NoSelection
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 600
            Layout.preferredHeight: parent.height
            TableViewColumn {
                id: checkedCol
                role:  "checked"
                title: ""
                width: 20
                delegate: CheckboxDelegate {
                    table: groupTable
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
