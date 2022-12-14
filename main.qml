import QtQuick 2.15
import QtQuick.Window 2.15

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
        //internal.openChildWindow("LoginForm.qml");
        //root.visible = false;
    }

    TopBar {
        width: parent.width
        height: parent.height * 0.1
    }
}
