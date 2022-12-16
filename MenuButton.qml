import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: root

    property string btnText: ""
    property string hoverColor: "grey"
    property string pressColor: "grey"
    property string defaultColor: "white"

    QtObject {
        id: internal

        property bool activated: false
    }

    hoverEnabled: true
    background: Rectangle {
        id: background

        border.width: 1
        color: root.defaultColor

        Text {
            anchors.centerIn: parent
            text: root.btnText
        }
    }

    onHoveredChanged: {
        if (!internal.activated)
        {
            if (root.hovered)
            {
                background.color = root.hoverColor;
            }
            else
            {
                background.color = root.defaultColor;
            }
        }
        else
        {
            background.color = pressColor;
        }
    }

    onPressed: {
        if (!internal.activated)
        {
            background.color = root.pressColor;
            internal.activated = true;
        }
        else
        {
            background.color = root.defaultColor;
            internal.activated = false;
        }
    }
}
