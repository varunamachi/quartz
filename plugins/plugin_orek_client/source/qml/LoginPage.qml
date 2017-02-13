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
        columnSpacing: 2
        Label {
            id: addrLabel
            text: "Server Address"
            width: 100
            color: orekActive.windowText
        }
        TextField {
            id: orekServer
            text: "http://localhost:8000"
            Layout.fillWidth: true
            color: orekActive.windowText
        }

        Label {
            id: nameLabel
            Layout.fillWidth: true
            text: "User Name"
            width: 100
            color: orekActive.windowText
        }
        TextField {
            id: userName
            Layout.fillWidth: true
            placeholderText: "Enter the user name"
            color: orekActive.windowText
        }

        Label {
            text: "Password"
            Layout.fillWidth: true
            width: 100
            color: orekActive.windowText
        }
        TextField {
            id: password
            echoMode: "Password"
            Layout.fillWidth: true
            placeholderText: "Enter your password"
            color: orekActive.windowText
        }
        Label {
            text: ""
            Layout.fillWidth: true
            width: 100
            color: orekActive.windowText
        }
        Button {
            text: "Login"
            background: orekActive.alternateBase
//            : orekActive.windowText
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
