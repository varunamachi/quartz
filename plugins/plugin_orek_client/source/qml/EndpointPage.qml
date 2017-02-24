import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

import "common.js" as Utils
import "orek.js" as Orek

Rectangle {
    color: orekActive.alternateBase
    anchors.fill: parent

    function load() {
        Orek.getAllEndpoints( function(jsonContent) {
            model.json = jsonContent.toString()
        }, function(errorContent) {
            console.log(errorContent)
        });
    }


    function getEndpointProperty(propName) {
        if(createDialog.isEdit && createDialog.endpoint) {
            return createDialog.endpoint[propName]
        }
        return ""
    }

    function removeSelected() {
        for(var i = 0; i < model.count; i++) {
            var ep = model.model.get(i)
            var msg = qsTr("Do you really want to delete selected endpoints?")
            if(ep.selected === true) {
                if(Utils.confirm(qsTr("Remove Endpoint"), msg)) {
                    var suc = function(msg) {
                        Utils.showResult(msg)
                        load()
                    }
                    var fail = function(msg) {
                        Utils.showResult(msg)
                        load()
                    }
                    Orek.deleteEndpoint(ep.endpointID, suc, fail);
                    break
                }
            }
        }
    }
    Dialog {
        property bool isEdit: false
        property var endpoint
        id: createDialog
        width: 400
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            var endpoint = {}
            endpoint[ "endpointID"  ] = endpointID.text
            endpoint[ "endpointName"] = name.text
            endpoint[ "owner"       ] = owner.text
            endpoint[ "group"       ] = group.text
            endpoint[ "description" ] = description.text
            endpoint[ "location"    ] = location.text

            var func = isEdit ? Orek.updateEndpoint : Orek.createEndpoint
            func( endpoint,
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
                text: qsTr("Endpoint ID")
            }
            TextField {
                //Should be generated
                id: endpointID
                placeholderText: qsTr("Enter endpoint identifier")
                text: getEndpointProperty("endpointID")
                Layout.fillWidth:  true
                enabled: !createDialog.isEdit
            }

            Label {
                text: qsTr("Endpoint Name")
            }
            TextField {
                id: name
                placeholderText: qsTr("Enter endpoint name")
                text: getEndpointProperty("endpointName")
                Layout.fillWidth:  true
            }

            Label {
                text: qsTr("Owner")
            }
            TextField {
                //May be pull the user list and show it in a combobox
                id: owner
                placeholderText: qsTr("Enter user name of the owner")
                text: getEndpointProperty("owner")
                Layout.fillWidth:  true
            }
            Label {
                text: qsTr("Group")
            }
            TextField {
                id: group
                placeholderText: qsTr("Enter the owning group")
                text: getEndpointProperty("group")
                Layout.fillWidth:  true
            }
            Label {
                text: qsTr("Description")
            }
            TextField {
                id: description
                placeholderText: qsTr("Enter the description")
                text: getEndpointProperty("description")
                Layout.fillWidth:  true
            }
            Label {
                text: qsTr("Location")
            }
            TextField {
                id: location
                placeholderText: qsTr("Enter the location")
                text: getEndpointProperty("location")
                Layout.fillWidth:  true
            }
        }
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
                        var ep = model.model.get(i)
                        if(ep.selected === true) {
                            createDialog.endpoint = ep
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
}
