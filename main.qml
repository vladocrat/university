import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.12
import User 1.0

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Students Management System")

    QtObject {
        id: internal

        function openChildWindow(windowName) {
            var child = Qt.createComponent(windowName);
            var window = child.createObject(root);
            window.show();
        }
    }

    Component.onCompleted: {
        //root.visible = false;
        //internal.openChildWindow("LoginForm.qml");
    }

    Rectangle {
        id: topbar

        anchors.top: parent.top
        width: parent.width
        height: parent.height * 0.1
        color: "grey"

        RowLayout {
            anchors.fill: parent
            spacing: 1

            Text {
                Layout.alignment : Qt.AlignRight
                text: User.role
            }

            Item {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: 1
            }
        }
    }

    Rectangle {
        id: mainMenu

        anchors.top: topbar.bottom
        height: root.height
        width: root.width / 4
        color: "red"
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Button {
                id: btn

                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "student"
                    }
                }

                onClicked: {
                    if (studentMenu.visible === true) {
                        studentMenu.visible = false;
                    } else {
                        studentMenu.visible = true;
                    }
                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "contract"
                    }
                }

                onClicked: {
                    if (contractMenu.visible === true) {
                        contractMenu.visible = false;
                    } else {
                        contractMenu.visible = true;
                    }
                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "gap year"
                    }
                }

                onClicked: {
                    if (gapYearMenu.visible === true) {
                        gapYearMenu.visible = false;
                    } else {
                        gapYearMenu.visible = true;
                    }
                }
            }

            Item {
                Layout.preferredHeight: parent.height - btn.height
                Layout.preferredWidth: 1
            }
        }
    }

    Rectangle {
        id: studentMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 4
        color: "blue"
        border.width: 1
        visible: false

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "get all"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "insert"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "update"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "delete"
                    }
                }

                onClicked: {

                }
            }

            Item {
                Layout.preferredHeight: parent.height - btn.height
                Layout.preferredWidth: 1
            }
        }
    }

    Rectangle {
        id: contractMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 4
        color: "blue"
        border.width: 1
        visible: false

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "get all"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "insert"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "update"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "delete"
                    }
                }

                onClicked: {

                }
            }

            Item {
                Layout.preferredHeight: parent.height - btn.height
                Layout.preferredWidth: 1
            }
        }
    }

    Rectangle {
        id: gapYearMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 4
        color: "blue"
        border.width: 1
        visible: false

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "get all"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "insert"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "update"
                    }
                }

                onClicked: {

                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                background: Rectangle {
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "delete"
                    }
                }

                onClicked: {

                }
            }

            Item {
                Layout.preferredHeight: parent.height - btn.height
                Layout.preferredWidth: 1
            }
        }
    }
}
