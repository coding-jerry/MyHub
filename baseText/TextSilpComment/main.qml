import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Rectangle{
        id: baseText
        width: 30
        height: 30
        anchors.centerIn: parent
        BaseText{
            width: 30
            height: 20
////            bcolor: "red"
//            btext: "12123456789545";
////            banchors.left: parent.left
//            banchors.leftMargin: 8
////            banchors.verticalCenter: parent.verticalCenter
//            bcolor: "red"
////            bfontFamily: FC.textFontRegular
//            bfontSize: 14
//            bwidth: 200

//            clip: true
////            bfont.pixelSize: 20
            text: "12123456789545"
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 14
            color: "red"
            clip: true
        }
    }

    Row {
               spacing: 10
//               anchors.top: baseText.bottom
//               x:baseText.x
//               y:baseText.y+100
               anchors.fill: parent

               Text { text: qsTr("请输入密码：") ;
                      font.pointSize: 15
                      verticalAlignment: Text.AlignVCenter
               }

               TextField {
                   id: control
                   placeholderText: qsTr("Enter description")
                   anchors.centerIn: parent
                   focus: true
                   background: Rectangle {
                       implicitWidth: 200
                       implicitHeight: 40
                       color: "yellow"
                       border.color: "black"
                   }
               }
           }


}
