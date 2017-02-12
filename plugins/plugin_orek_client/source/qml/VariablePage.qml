import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import "orek.js" as Orek

Rectangle {
    color: "transparent"
    anchors.fill: parent

    function loadVariables() {
        Orek.getAllVariables( function(jsonContent) {
            variableModel.json = jsonContent.toString()
        }, function(errorContent) {
            console.log(errorContent)
        });
    }

    JSONListModel {
        id: variableModel
    }
    TableView {
        id: variableTable
        model: variableModel.model
        anchors.fill: parent
        Component.onCompleted: loadVariables()
        onVisibleChanged: loadVariables()
        TableViewColumn {
            role: "variableID"
            title: "Variable ID"
            width: 100
        }
        TableViewColumn {
            role: "variableName"
            title: "Variable Name"
        }
        TableViewColumn {
            role: "endpointID"
            title: "Endpoint"
        }
        TableViewColumn {
            role: "description"
            title: "Description"
        }
        TableViewColumn {
            role: "unit"
            title: "Unit"
        }
        TableViewColumn {
            role: "type"
            title: "Type"
        }
        TableViewColumn {
            role: "permission"
            title: "Permission"
        }
    }
}
