import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root

    signal getAllClicked();
    signal insertClicked();
    signal deleteClicked();
    signal updateClicked();

    color: "blue"
    border.width: 1
    visible: false

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        MenuButton {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 40
            Layout.fillWidth: true
            pressColor: "red"
            btnText: "get all"

            onClicked: {
                root.getAllClicked();
            }
        }

        MenuButton {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 40
            Layout.fillWidth: true
            pressColor: "red"
            btnText: "insert"

            onClicked: {
                root.insertClicked();
            }
        }

        MenuButton {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 40
            Layout.fillWidth: true
            pressColor: "red"
            btnText: "update"

            onClicked: {
                root.updateClicked();
            }
        }

        MenuButton {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 40
            Layout.fillWidth: true
            pressColor: "red"
            btnText: "delete"

            onClicked: {
                root.deleteClicked();
            }
        }

        Item {
            Layout.preferredHeight: parent.height - btn.height
            Layout.preferredWidth: 1
        }
    }
}
