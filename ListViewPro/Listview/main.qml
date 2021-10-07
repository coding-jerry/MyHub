import QtQuick 2.0
import QtQuick.Window 2.2
import StringListModel 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import Qt.labs.platform 1.1
import QtQml.Models 2.2
/*
ListView {
    width: 100; height: 100

    model: myModel
    delegate: Rectangle {
        height: 25
        width: 100
        Rectangle {
            height: 1;
            width: parent.width;
            color: "lightGray"
        }

        color: "red"
        Text { text: modelData }
    }
}
*/
Window{
    id:rootWin;
    visible:true;
    width: 670;
    height: 540;
    title: "Hello world";
    color: "#A8A8A8";
//    ItemSelectionModel{
//        id: sel;
//        model: MystringListModel;
//    }

    ColumnLayout{
        Frame{
            ListView{
                id:listViewObj;
                implicitWidth: 640;
                implicitHeight: 450;
                clip: true;
                model: MystringListModel{//链接model层

                }
                delegate: delCom;
                currentIndex: -1;
                property var lasCurrentIndex: -1;
                /*
                MouseArea{
                    id:mouseObj
                    acceptedButtons: Qt.LeftButton;
                    anchors.fill: parent;
                    enabled: true;
                    property var curIndex;
                    onClicked: {

                        listViewObj.currentIndex = index;
                        console.log("onClicked >>> ",index);
//                        var modelData = listViewObj.model;
                        var fileName = listViewObj.model.dataForQml(index,0)
                        console.log("fileName >>>> ",fileName);

                    }
                }*/
            } //end ListView
        }//end Frame
        Component{
            id:delCom
            Rectangle{
                width: listViewObj.width;
                height: 30;
                border.color: "lightGray";
                color: "DimGrey";
                Text{
                    //                            anchors.fill: parent;
                    anchors.centerIn: parent;
                    text: model.description
                    color: "lightGray";
//                    onEditingFinished: {
//                        model.description = text;
//                        console.log("model.description is :",model.description);
//                    }
                    Layout.fillWidth: true;
                }
                MouseArea{
                    anchors.fill: parent;
                    hoverEnabled: true;

                    onClicked: {
                        if(listViewObj.lasCurrentIndex !== -1)
                        {
                            if(listViewObj.itemAtIndex(listViewObj.lasCurrentIndex))
                            {
                                listViewObj.itemAtIndex(listViewObj.lasCurrentIndex).color =  "DimGrey";
                            }
                        }
                        listViewObj.currentIndex = index;
                        color = "#2894FF";

                        listViewObj.lasCurrentIndex = index;
                        console.log("index >>> ",index);
                        var modelData = listViewObj.model;
                        var fileName = modelData.dataForQml(index,0);
                        console.log("fileName >>>> ",fileName);
                    }
                    onDoubleClicked: {
                        var modelData = listViewObj.model;
                        var filePath = modelData.dataForQml(index,1);
                        console.log("filePath>>> ",filePath);
                        Qt.openUrlExternally(filePath);
                    }

                    onEntered: {
                        if(listViewObj.currentIndex === index)
                        {
                            return;
                        }
                        color = "#8C8C8C";
                    }
                    onExited: {
                        if(listViewObj.currentIndex === index)
                        {
                            return;
                        }
                        color = "DimGrey";
                    }
                }
            }
        } //end Component
        RowLayout{
            Button{
                text: "Add new path";
                onClicked: {
                    listViewObj.model.textInsertRows(listViewObj.count,1);
                }
                Layout.fillWidth :true;
            }
            Button{
                text: "Remove item";
                onClicked: {
                    listViewObj.model.textRemoveRows(listViewObj.count-1,1);
                }
                Layout.fillWidth: true;
            }
        }
    }
}
