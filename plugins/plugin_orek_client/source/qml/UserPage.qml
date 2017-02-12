import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4

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
    TableView {
        id: userTable
        model: userModel.model
        anchors.fill: parent
        Component.onCompleted: load()
        onVisibleChanged: load()
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
