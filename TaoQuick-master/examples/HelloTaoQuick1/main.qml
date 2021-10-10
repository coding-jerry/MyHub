import QtQml 2.0
import QtQuick 2.9

import QtQuick.Controls 2.0

import TaoQuick 1.0

Rectangle {
    color: "lightblue"
    width: 640
    height: 480
    property int spacePresses: 0;
    CusButton_Blue {
        width: 120
        height: 36
        anchors.centerIn: parent
        text: "Hello"
        onClicked: {
            spacePresses++;
            console.log("hello TaoQuick");
            bt.text ="it is not a text" + spacePresses ;
        }
    }
    BasicText {
        id : bt;
        width: 120;
        height: 36;
        anchors.leftMargin: parent;
        color: 'red'
        text: "it is a text!";

    }
    CusLabel_Left{
        id:cl;
        width: 120;
        height: 36;
        //anchors.rightMargin: parent;
        //horizontalAlignment: bt.right;
        color: CusConfig.textColor;
        text: "Label??"
    }
    CusComboBox{
        id: ccb;
        model: ListModel{
            id:cbItems
            ListElement{text:"节点1";color:"Yellow"}

        }

    }
}
