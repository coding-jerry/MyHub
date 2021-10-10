import QtQuick 2.0
import QtQuick.Controls 2.12

ToolTip {
    id: control
    text: qsTr("A descriptive tool tip")
    padding: 12
    delay:800
    x:parent.x - parent.width
    y:parent.y+parent.height + 8
    contentItem: Text {
        text: control.text
        color: "#E3E3E3"

        wrapMode: Text.Wrap

    }

    background: Rectangle {
        radius: 4
        border.width: 1
        border.color: "#5A5A5A"
        color: "#323232"
    }
}
