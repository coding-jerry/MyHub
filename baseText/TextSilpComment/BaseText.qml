import QtQuick 2.0
import QtQuick.Window 2.12
import QtQml 2.12
/*
Item
{
    property alias btext: baseText.text
    property alias bfontSize: baseText.font.pixelSize
    property alias bfontFamily: baseText.font.family
    property alias bcolor: baseText.color
    property alias bwidth: baseText.width
    property int displacement: 0
    property int showTime: 0
    property bool ishovered: false
    Text {
        id: baseText
        anchors.fill: parent
        //    rotation: mouseArea.ishovered
        //    Behavior on rotation {
        //            PropertyAnimation{
        //                id: myAnimation
        //                target: baseText
        //                properties:"x"
        //                from: baseText.width;
        //                to: displacement;
        //                duration: 3000;
        //            }
        //    }

    }
    MouseArea
    {
        id:mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            console.log("mouse is on the area");

            //算出所需要的位移差值
            displacement = -(baseText.contentWidth - parent.width)
            console.log(baseText.contentWidth,parent.width);
            if(displacement > 0)
            {
                displacement = 0;
                console.log(baseText.text)
            }

            //算出动画需要的时间
            showTime = -(displacement * 40);
            console.log(showTime);
            console.log(displacement);
            baseText.clip = false;
            myAnimation.start();
        }
        onExited: {
            baseText.clip = true;
            myAnimation.stop();
            baseText.x = 0
        }
    }
    PropertyAnimation{
        id: myAnimation
        target: baseText
        properties:"x"
        from: 0;
        to: displacement;
        duration: showTime;
//        easing.type: Easing.Linear
//        easing.type: Easing.OutQuad
    }


/*   //toolTip出现
    MouseArea
       {
           id:mouseArea
           anchors.fill: parent
           hoverEnabled: true

           onEntered: {
               console.log("mouse is on the area");
//               baseText.clip = false;
                ishovered = true
//               loader.sourceComponent = toolTip;//Error: Loader只能与component或文件使用

               if(baseText.contentWidth > parent.width && loader.sourceComponent == null)
               {
                   console.log("loading the source");
//                   loader.setSource("BaseToolTip.qml",
//                                    {"text":"baseText.text",
//                                        "width":"480"});
//                    loader.source = "BaseToolTip.qml"
//                    loader.item.text = baseText.text;
//                    ishovered = true
                    loader.sourceComponent = bComponent;
               }


           }
           onExited: {
//               baseText.clip = true;
//                ishovered = false
               if(baseText.contentWidth > parent.width)
               {
                 console.log("release the source");
//                 loader.sourceComponent = undefined

               }
               ishovered = false
           }

       }

//    BaseToolTip{
//        id: toolTip
//        visible: ishovered
//        text: baseText.text
//        width: 480
//    }

    Loader{
        id: loader
//        anchors.top: parent.bottom
//        anchors.topMargin: 10
//        width: 480;
    }
    Component{
        id: bComponent
            BaseToolTip{
                id: toolTip
                visible: ishovered
                text: baseText.text
                width: 480
            }
    }
}
*/



Text {
    id: baseText

    property bool ishovered: false
    MouseArea
       {
           id:mouseArea
           anchors.fill: parent
           hoverEnabled: true

           onEntered: {
               console.log("mouse is on the area");
                ishovered = true
               if(baseText.contentWidth > parent.width && loader.sourceComponent == null)
               {
                   console.log("loading the source");
                    loader.sourceComponent = bComponent;
               }
           }
           onExited: {

               if(baseText.contentWidth > parent.width)
               {
                 console.log("release the source");
               }
               ishovered = false
           }

       }

    Loader{
        id: loader
    }
    Component{
        id: bComponent
            BaseToolTip{
                id: toolTip
                visible: ishovered
                text: baseText.text
                width: 480
            }
    }
}




