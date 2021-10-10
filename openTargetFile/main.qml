import QtQuick 2.12
import QtQuick.Controls 2.14
import QtQuick.Window 2.14
import PreviewInMurray 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Row{
        anchors.centerIn: parent;
        spacing: 5
        Button{
            id: btn;
            width: 80;
            height: 50;
            text:"open file"
            onClicked:{
                console.log("open file ")
                PreIM.openTargetFile();
            }
        }
        Button{
            id:cloBtn;
            width: 80;
            height: 50;
            text: "close";
            onClicked: {
                console.log("close all program");
                PreIM.finishAllProgram();
            }
        }
    }


//    PreIM{
//        id:preIn;
//    }
}
