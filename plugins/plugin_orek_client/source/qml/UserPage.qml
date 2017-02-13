import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

import "orek.js" as Orek



Rectangle {
    color: "transparent"
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
        anchors.fill: parent
        RowLayout {
            id: userOperations
        }
        TableView {
            id: userTable
            model: userModel.model
            anchors.fill: parent
            Component.onCompleted: load()
            onVisibleChanged: load()
            TableViewColumn {
                id: checkedCol
                role:  "checked"
                title: ""
                width: 20
                delegate: CheckBox {
                    checked: styleData.value
                    enabled: true
                    anchors.left: parent != null ? parent.left : checkedCol.left
                    anchors.leftMargin: parent != null ? parent.width/2 - 6
                                                       : checkedCol.width
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
