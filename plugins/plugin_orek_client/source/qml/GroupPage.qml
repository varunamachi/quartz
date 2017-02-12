import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import "orek.js" as Orek

Rectangle {
    color: "transparent"
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
    TableView {
        id: groupTable
        model: groupModel.model
        anchors.fill: parent
        Component.onCompleted: loadGroups()
        onVisibleChanged: loadGroups()
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
