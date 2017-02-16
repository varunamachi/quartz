import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

import "orek.js" as Orek

Rectangle {
    color: "transparent"
    anchors.fill: parent

    function load() {
        Orek.getAllVariables( function(jsonContent) {
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
                onClicked: console.log("Create...")
            }
            Button {
                height: Layout.height
                id: editSelected
                text: qsTr("Edit")
                onClicked: console.log("Edit...")
            }
            Button {
                id: deleteSelected
                height: Layout.height
                text: qsTr("Delete")
                onClicked: console.log("Delete...")
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
}
