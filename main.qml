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

            MenuButton {
                id: btn

                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "student"

                onClicked: {
                    if (studentMenu.visible === true) {
                        studentMenu.visible = false;
                    } else {
                        studentMenu.visible = true;
                    }
                }
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "contract"

                onClicked: {
                    if (contractMenu.visible === true) {
                        contractMenu.visible = false;
                    } else {
                        contractMenu.visible = true;
                    }
                }
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "gap year"

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

    ActionsMenu {
        id: studentMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 4
    }

    ActionsMenu {
        id: contractMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 4
    }

    ActionsMenu {
        id: gapYearMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 4
    }
}
