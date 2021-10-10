import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import FileInfo 1.0
Window {
    id:root
    visible: true
    width: 640
    height: 480
    property var i: 0
    property var fileInfo: undefined
    property var listFile: []
    title: qsTr("Hello World")
//    function onSigDownloadFinished(sNewFileJsonStr){
//        var modelData = outputFile
//    }
    FileInfo{
        id: fileInfolist
        property var fileList : []
        onSendLocalFileInfoList: {
            console.log("listFileInfo >>>> ")
            listFile = listFileInfo
            fileInfolist.fileList = listFileInfo;
        }
    }
    Rectangle{
        id: txtRec
        width: 200
        height: 50
        anchors.alignWhenCentered: parent

        color: "lightBlue"
        Text {
            id: txt
            color: "black"
            anchors.fill: parent
            text: fileInfo
        }
    }


    Button{
        id:btn
        width: 50
        height: 50
        anchors.top: txtRec.bottom;
        text: "Button"

        onClicked: {
            console.log("listFile >>>> ");
            var fileList = fileInfolist.getListFileInfo();
            console.log(listFile)
            root.fileInfo = fileInfolist.fileList[i]
            i++;
        }
    }
}
