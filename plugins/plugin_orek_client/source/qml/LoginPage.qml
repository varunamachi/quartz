import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Layouts 1.3

import "orek.js" as Orek

Rectangle {
    id: lp
    signal logInError(string error)
    signal loggedIn


    anchors.fill: parent

    GridLayout {
        anchors.fill: parent
        id: loginGrid
        columns: 2
        rowSpacing: 5
        Label {
            id: addrLabel
            text: "Server Address"
        }
        TextField {
            id: orekServer
            text: "http://localhost:8000"
            Layout.fillWidth: true
        }

        Label {
            id: nameLabel
            text: "User Name"
        }
        TextField {
            id: userName
            Layout.fillWidth: true
            text: "two"
        }

        Label {
            text: "Password"
        }
        TextField {
            id: password
            echoMode: "Password"
            Layout.fillWidth: true
            text: "two"
        }
        Label {
            text: ""
            Layout.fillWidth: true
        }
        Button {
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
