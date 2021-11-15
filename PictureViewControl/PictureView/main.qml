import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    GridLayout{
        id:gridlayoutObj;
        anchors.centerIn: parent;
        rows: 2;
        rowSpacing: 5;
        columns: 2;
        columnSpacing: 5;

        Rectangle{
            border.color: "gray"
            width: 50;
            height: 50;
            Image {
                id: name
                source: "C:/Users/m/Desktop/1.bmp"
                width: 50;
                height: 50;
                anchors.fill: parent;
            }
        }
        Rectangle{
            border.color: "gray"
            width: 50;
            height: 50;
        }
        Rectangle{
            border.color: "gray"
            width: 50;
            height: 50;
        }
        Rectangle{
            border.color: "gray"
            width: 50;
            height: 50;
        }

    }
}
