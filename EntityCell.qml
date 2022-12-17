import QtQuick 2.15
import QtQuick.Layouts 1.15

RowLayout {
    id: root

    property string text: ""
    property int leftSpace: 1

    Item {
        Layout.preferredWidth: root.leftSpace
        Layout.fillHeight: true
    }

    Text {
        text: root.text
    }
}
