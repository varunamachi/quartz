import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import "orek.js" as Orek

Rectangle {
    color: "transparent"
    anchors.fill: parent

    function loadEndpoints() {
        Orek.getAllEndpoints( function(jsonContent) {
            endpointModel.json = jsonContent.toString()
        }, function(errorContent) {
            console.log(errorContent)
        });
    }

    JSONListModel {
        id: endpointModel
    }
    TableView {
        id: endpointTable
        model: endpointModel.model
        anchors.fill: parent
        Component.onCompleted: loadEndpoints()
        onVisibleChanged: loadEndpoints()
        selectionMode: SelectionMode.NoSelection
        TableViewColumn {
            id: checkedCol
            role:  "checked"
            title: ""
            width: 20
            delegate: CheckboxDelegate {
                table: endpointTable
            }
        }
        TableViewColumn {
            role: "endpointID"
            title: "Endpoint ID"
            width: 100
        }
        TableViewColumn {
            role: "endpointName"
            title: "Endpoint Name"
        }
        TableViewColumn {
            role: "owner"
            title: "Owner"
        }
        TableViewColumn {
            role: "group"
            title: "Owner Group"
        }
        TableViewColumn {
            role: "description"
            title: "Description"
        }
        TableViewColumn {
            role: "location"
            title: "Location"
        }
        TableViewColumn {
            role: "visibility"
            title: "Visiability"
        }
    }
}
