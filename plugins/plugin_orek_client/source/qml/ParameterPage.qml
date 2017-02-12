import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import "orek.js" as Orek

Rectangle {
    color: "transparent"
    anchors.fill: parent

    function loadParameters() {
        Orek.getAllParameters( function(jsonContent) {
            parameterModel.json = jsonContent.toString()
        }, function(errorContent) {
            console.log(errorContent)
        });
    }

    JSONListModel {
        id: parameterModel
    }
    TableView {
        id: parameterTable
        model: parameterModel.model
        anchors.fill: parent
        Component.onCompleted: loadParameters()
        onVisibleChanged: loadParameters()
        TableViewColumn {
            role: "parameterID"
            title: "Parameter ID"
            width: 100
        }
        TableViewColumn {
            role: "parameterName"
            title: "Parameter Name"
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
