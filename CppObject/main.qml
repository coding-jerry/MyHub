import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import MyCppObject 1.0
Window {
    id: root;
    visible: true;
    width: 500;
    height: 300;
    title: qsTr("QML调用CPP对象");
    color: "white";

    signal qmlSignalA();
    signal qmlSignalB(string str,int value);

//    signal qmlsendData();
    Menu{
        id:mymenu;

        topPadding: 8;
        bottomPadding: 8;
        leftPadding: 8;
        rightPadding: 8;
        spacing: 8;
        delegate:  MenuItem{
            id:menuitem
            implicitWidth: 208
            implicitHeight: 32
            leftPadding: 16
        }
        background: Rectangle {
            implicitWidth: 208
            implicitHeight: 32
            opacity: enabled ? 1 : 0.3
            radius: 4
            color: "lightblue"

            anchors.fill: parent


        }
    }

    MouseArea{
        anchors.fill: parent;

        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: {
            if(mouse.button == Qt.LeftButton){
                console.log('qml 点击左键');

                cpp_obj.name = "mm";
                cpp_obj.year = 1999;

                console.log(cpp_obj.name + ' Year:' + cpp_obj.year);
                cpp_obj.sendSignal();

                console.log('点击右键');

                root.qmlSignalA();
                root.qmlSignalB('mm',1999);

//                root.qmlsendData();
                console.log(cpp_obj.name);
            }
        }

    }

    CppObject{
        id:cpp_obj;
        property int count: 0;

//        onYearChanged: {
//            count++;
//            console.log('qml onYearChanged',count);
//        }
        onCountChanged: {
            count++;
            console.log('qml onCountChanged',count);
        }
    }

    //组件加载完成执行
    Component.onCompleted: {
        cpp_obj.onCppSignalA.connect(()=>console.log('qml signalA process'));
         cpp_obj.onCppSignalB.connect(processB);

//        root.qmlsendData.connect(cpp_obj.sendData);//error：Function.prototype.connect: target is not a function 对象中的槽函数是私有的所以不可以访问

        root.qmlSignalA.connect(cpp_obj.cppSlotA);
        root.qmlSignalB.connect(cpp_obj.cppSlotB);

    }
    function processB(str,value){
        console.log('qml function processB',str,value);

    }
}
