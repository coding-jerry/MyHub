import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls 2.14

Window {

    property bool isHovered: false;
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Hello World")
    Calendar{
        id:theCalendar
    }
    Component
    {
        id:component
        ToolTip {
            id: control

            x:mouse.mouseX;
            y:mouse.mouseY;
            visible: isHovered
            ToolTip.timeout: 5000
            text: qsTr("A descriptive tool tip of what the button does")

            contentItem: Text {
                text: control.text
                font: control.font
                color: "#21be2b"
            }

            background: Rectangle {
                border.color: "#21be2b"
            }
        }
    }
    Loader{
        id:loader;
    }

    MouseArea{
        id:mouse;
        hoverEnabled: true;
        anchors.fill: parent;
        onEntered: {
            isHovered = true;
            console.log("onClicked >>>");
            if(loader.sourceComponent !== component)
                loader.sourceComponent = component;
        }
        onExited: {
            isHovered = false;
            console.log("onReleased>>>>");
        }
    }

}
