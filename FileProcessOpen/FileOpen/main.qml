import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import FileProcess 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Row{
        id:theRow;
        anchors.centerIn: parent
        Button{
            id:btn

            width: 80;
            height: 40;
            text: "open file"
            onClicked: {
                console.log("onclicked >>> 16");
                var retResult = FileOP.openTargetFile();
                if(retResult)
                {
                    console.log("open file successfully");
                }
            }
        }
        Button{
            id:closBtn;
            width: 150;
            height: 40;
            text: "close all program";
            anchors.leftMargin: 10
            onClicked: {
                console.log("close all files");
                var retResult =FileOP.closeTargetProgram();
                if(retResult)
                {
                    console.log("close all files successfully");
                }
            }//end of onClicked
        }//end of Button
    }//end of Row
}
