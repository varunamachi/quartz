import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

CheckBox {
    property TableView table
//    property alias marked: checked
//    checked: styleData.selected
    enabled: true
    anchors.left: parent != null ? parent.left : checkedCol.left
    anchors.leftMargin: parent != null ? parent.width/2 - 6
                                       : checkedCol.width
    style: CheckBoxStyle {
        indicator: Rectangle {
            implicitWidth: 10
            implicitHeight: 10
            radius: 3
            border.color: control.activeFocus
                          ? "darkblue"
                          : "gray"
            border.width: 1
            Rectangle {
                visible: control.checked
                color: "#555"
                border.color: "#333"
                radius: 2
                anchors.margins: 2
                anchors.fill: parent
            }
        }
    }
    onCheckedChanged: {
        table.focus = true
        table.selection.clear()
        table.selection.select(styleData.row, styleData.row)
        table.model.setProperty(styleData.row, "selected", checked )
    }
}
