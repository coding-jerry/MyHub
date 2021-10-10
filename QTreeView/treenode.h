#ifndef TREENODE_H
#define TREENODE_H
#include <QObject>
#include <QList>
#include <QVariant>
#include <QStringList>
#include <QModelIndex>

class TreeNode
{
public:
    TreeNode(const QList<QVariant> &data,TreeNode* parent);
    ~TreeNode();

    //添加子节点---子节点可以有很多个
    void appendChild(TreeNode* child);
    //删除子节点
    void deleteAllChild();
    //获得子节点---根据行row得到
    TreeNode *child(int row);

    //获得子节点的总数
    int childCount()const;
    //获得列的总数
    int columnCount()const;
    //获得数据
    QVariant data(int column) const;

    //获得当前行数row
    int row()const;

    //获得父节点
    TreeNode *parent();

    //设置父节点
    void setParent(TreeNode* parent);

    //设置数据
    void setNodeData(QVariant data,int index);

private:
    TreeNode *pParentNode;//存放父节点
    QList<TreeNode*> mChildeNodes;//存放子节点
    QList<QVariant> mNodeData;//存放数据

};

#endif // TREENODE_H
