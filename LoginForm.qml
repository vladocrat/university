import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import LoginController 1.0

Window {
    width: 400
    height: 480
    maximumHeight: 480
    maximumWidth: 400
    minimumHeight: 480
    minimumWidth: 400
    visible: true
    title: qsTr("Login")

    QtObject {
        id: internal

        property int heightFactor: 8
        property int widthFactor: 2
    }

    ColumnLayout {
        anchors.fill: parent

        Keys.onEnterPressed: loginBtn.clicked()
        Keys.onReturnPressed: loginBtn.clicked()

        Item {
            Layout.preferredHeight: internal.heightFactor * 3
            Layout.fillWidth: true
        }

        Text {
            Layout.alignment: Qt.AlignCenter
            text: "LOGIN"
            font.pointSize: 20
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: internal.heightFactor
        }

        TextField {
            id: email

            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: parent.height / internal.heightFactor
            Layout.preferredWidth: parent.width / internal.widthFactor
            placeholderText: "email"
            background: Rectangle {
                border.color: "red"
                border.width: 3
            }
        }

        TextField {
            id: password

            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: parent.height / internal.heightFactor
            Layout.preferredWidth: parent.width / internal.widthFactor
            placeholderText: "password"
            background: Rectangle {
                border.color: "red"
                border.width: 3
            }
        }

        Button {
            id: loginBtn

            Layout.alignment: Qt.AlignCenter
            text: "login"

            onClicked: {
                console.log("login attempt");

                if (!LoginController.login(email.text, password.text))
                {
                    //TODO show popup
                    console.log("failed to login");
                }

                //TODO redirect to main window
            }
        }
    }
}
