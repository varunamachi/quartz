import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

import "orek.js" as Orek
import "common.js" as Utils

Rectangle {
    color: orekActive.alternateBase
    anchors.fill: parent

    function load() {
        Orek.getAllParameters( function(jsonContent) {
            model.json = jsonContent.toString()
        }, function(errorContent) {
            Utils.showError(errorContent)
        });
    }


    function getParameterProperty(propName) {
        if(createDialog.isEdit && createDialog.parameter) {
            return createDialog.parameter[propName]
        }
        return ""
    }

    function removeSelected() {
        for(var i = 0; i < model.count; i++) {
            var parameter = model.model.get(i)
            var msg = qsTr("Do you really want to delete selected parameters?")
            if(parameter.selected === true) {
                if(Utils.confirm(qsTr("Remove Parameter"), msg)) {
                    var suc = function(msg) {
                        Utils.showResult(msg)
                        load()
                    }
                    var fail = function(msg) {
                        Utils.showResult(msg)
                        load()
                    }
                    Orek.deleteParameter(parameter.parameterID, suc, fail);
                    break
                }
            }
        }
    }

    Dialog {
//        parameterID
//        parameterName
//        endpointID
//        description
//        unit
//        type
        property bool isEdit: false
        property var parameter
        id: createDialog
        width: 400
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            var parameter = {}
            parameter[ "parameterID"  ] = parameterID.text
            parameter[ "parameterName"] = parameterName.text
            parameter[ "endpointID" ] = endpointID.text
            parameter[ "description" ] = description.text
            parameter[ "unit" ] = unit.text
            parameter[ "type" ] = type.text

            var func = isEdit ? Orek.updateParameter : Orek.createParameter
            func( parameter,
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
                text: qsTr("Parameter ID")
            }
            TextField {
                //Should be generated
                id: parameterID
                placeholderText: qsTr("Enter parameter identifier")
                text: getParameterProperty("parameterID")
                Layout.fillWidth:  true
                enabled: !createDialog.isEdit
            }

            Label {
                text: qsTr("Parameter Name")
            }
            TextField {
                id: parameterName
                placeholderText: qsTr("Enter parameter name")
                text: getParameterProperty("parameterName")
                Layout.fillWidth:  true
            }

            Label {
                text: qsTr("Endpoint ID")
            }
            TextField {
                //May be pull the user list and show it in a combobox
                id: endpointID
                placeholderText: qsTr("Enter endpoint ID")
                text: getParameterProperty("endpointID")
                Layout.fillWidth:  true
            }
            Label {
                text: qsTr("Description")
            }
            TextField {
                id: description
                placeholderText: qsTr("Enter description of parameter")
                text: getParameterProperty("description")
                Layout.fillWidth:  true
            }
            Label {
                text: qsTr("Unit")
            }
            TextField {
                id: unit
                placeholderText: qsTr("Enter the unit of parameter")
                text: getParameterProperty("unit")
                Layout.fillWidth:  true
            }
            Label {
                text: qsTr("Type")
            }
            TextField {
                id: type
                placeholderText: qsTr("Enter the type")
                text: getParameterProperty("type")
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
                        var parameter = model.model.get(i)
                        if(parameter.selected === true) {
                            createDialog.parameter = parameter
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
}
