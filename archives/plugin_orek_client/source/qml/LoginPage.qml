import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

import "orek.js" as Orek

Rectangle {
    id: lp
    signal logInError(string error)
    signal loggedIn
    color: orekActive.base
    anchors.fill: parent
    GridLayout {
        anchors.fill: parent
        id: loginGrid
        columns: 2
        rowSpacing: 5
        columnSpacing: 5
        anchors.margins: 10
        Label {
            id: addrLabel
            text: qsTr("Server Address")
            color: orekActive.windowText
        }
        TextField {
            id: orekServer
            text: qsTr("http://localhost:8000")
            Layout.fillWidth: true
            color: orekActive.windowText
        }

        Label {
            id: nameLabel
            text: qsTr("User Name")
            color: orekActive.windowText
        }
        TextField {
            id: userName
            Layout.fillWidth: true
            placeholderText: qsTr("Enter the user name")
            color: orekActive.windowText
            text: "one"
        }

        Label {
            text: "Password"
            color: orekActive.windowText
        }
        TextField {
            id: password
            echoMode: "Password"
            Layout.fillWidth: true
            placeholderText: qsTr("Enter your password")
            color: orekActive.windowText
            text: "password"
        }
        Label {
            text: ""
            color: orekActive.windowText
        }
        Button {
            id: loginBtn
            text: "Login"
            onReleased: {
                Orek.address = orekServer.text
                Orek.login(
                    userName.text,
                    password.text,
                    function() {
                        lp.loggedIn()
                    },
                    function(err) {
                        lp.logInError(err)
                    })
            }
        }

        Label{
            text: ""
            Layout.fillHeight: true
        }
    }

}
