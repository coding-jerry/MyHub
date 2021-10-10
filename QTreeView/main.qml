import QtQuick 2.12
import QtQuick.Window 2.12
import QtQml 2.12

import QtQml.Models 2.2
import QtQuick.Controls 1.4    //1.4版本才有TreeView
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("TreeView Test")

    Rectangle {
        id: root
        height: parent.height
        width: parent.width
        color: "#87CEEB"

        property var treeModel: mControl.getTreeModel()

        //用于节点选中
        ItemSelectionModel {
            id: sel
            model: root.treeModel
        }

        TreeView {
            id: myTree
            anchors.fill: parent
            headerVisible: false
            backgroundVisible : false   //隐藏背景
            style: treeViewStyle
            model: root.treeModel
            selection: sel

            TableViewColumn {
                width: myTree.width
                title: "Name"
                role: "name"
            }

            itemDelegate: Item {
                Image {
                    id: nodeTextImage
                    anchors.verticalCenter: parent.verticalCenter
                    source: ""
                }
                Text {
                    id: nameText
                    anchors.left: nodeTextImage.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    color: "white"
                    elide: styleData.elideMode
                    text: styleData.value
                    font.pointSize: 16
                }
                Drag.active:itemMouse.drag.active
                Drag.dragType: Drag.Automatic;      //选择自动开始拖动
                Drag.supportedActions: Qt.CopyAction;   //选择复制数据到DropArea
                Drag.onDragFinished: {              //拖拽结束

                }

                MouseArea {
                    id: itemMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    drag.target: nameText

                    property bool isExpand: true    //点击展开树节点
                    onClicked: {
                        sel.setCurrentIndex(styleData.index, 0x0010)    //点击Item，设置选中当前节点
                        if (isExpand) {
                            emit: myTree.expand(styleData.index)
                            isExpand = false;
                            mControl.updateNodeName(styleData.index)
                            console.log("clicked");
                        }
                        else {
                            emit: myTree.collapse(styleData.index)
                            isExpand = true;
                        }
                    }
                    onDoubleClicked: {  //刷新子节点
                        myTree.collapse(styleData.index)  //先收起再展开，不然会有bug
                        mControl.updateNode(styleData.index)
                        myTree.expand(styleData.index)
                    }
                }
            }
        }
    }

    Component {
        id: treeViewStyle
        TreeViewStyle {
            padding.left: 2
            padding.right: 2
            indentation: 30  //节点间缩进
            rowDelegate: Rectangle {
                color: styleData.selected ? "#007DFF" : "transparent"   //选中节点后的颜色和背景色
                height: 30
            }
/*
            branchDelegate: Image {  //节点展开收缩图标
                id: nodeImage
                source: {
                    return styleData.isExpanded ? "" : ""
                }
            }
*/
        }
    }
}
