#include "treemodel.h"



TreeModel::TreeModel(QObject *parent)
{
    //创建根节点传入数据 （QVariant）动态数据
    QList<QVariant> list_root;
    list_root.append("RootNode");
    this->pRootNode = new TreeNode(list_root,NULL);

    //传入子节点
    QList<QVariant> list_node1;
    list_node1.append("中国");
    auto item_node1 = new TreeNode(list_node1,this->pRootNode);
    this->pRootNode->appendChild(item_node1);

    //传入孙子节点
    QList<QVariant> list_node1_child;
    list_node1_child.append("广州");
    auto item_node1_child = new TreeNode(list_node1_child,item_node1);
    item_node1->appendChild(item_node1_child);
}

TreeModel::~TreeModel()
{
    this->pRootNode->deleteAllChild();
    delete pRootNode;
}

void TreeModel::appendChild(const QModelIndex &index, QList<QVariant> dataList, int count)
{
    TreeNode* newTreeNode = static_cast<TreeNode*>(index.internalPointer());
    if(newTreeNode->childCount() && count == 0)
    {
        beginRemoveRows(index,0,newTreeNode->childCount()-1);
        newTreeNode->deleteAllChild();
        endRemoveRows();
    }
    TreeNode* midNode = new TreeNode(dataList,newTreeNode);
    beginInsertRows(index,newTreeNode->childCount(),newTreeNode->childCount());
    newTreeNode->appendChild(midNode);
    endInsertRows();

}

void TreeModel::setNodeName(QString appendName, QModelIndex index)
{
    TreeNode *pTreeNode = static_cast<TreeNode*>(index.internalPointer());
    pTreeNode->setNodeData(appendName,0);

    emit dataChanged(index,index);
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return static_cast<TreeNode*>(parent.internalPointer())->columnCount();
    }
    else {
        return pRootNode->columnCount();
    }
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeNode *parentNode;
    if(parent.column() > 0)
    {
        qDebug() << parent.column() << endl;
        return 0;
    }
    if(!parent.isValid())
    {
        parentNode = pRootNode;
    }
    else {
        parentNode = static_cast<TreeNode*>(parent.internalPointer());
    }
    return parentNode->childCount();
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int,QByteArray> names(QAbstractItemModel::roleNames());
    names[NAME] = "name";
    return names;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    switch (role)
    {
    case NAME:
    {
        return static_cast<TreeNode*>(index.internalPointer())->data(0);
    }

    }
    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return 0;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
    {
        return QModelIndex();
    }

    TreeNode *parentNode;
    if(!parent.isValid())
    {
        parentNode = pRootNode;
    }
    else {
        parentNode = static_cast<TreeNode*>(parent.internalPointer());
    }
    TreeNode* childNode = parentNode->child(row);

    if(childNode)
    {
        return createIndex(row,column,childNode);
    }
    else {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return QModelIndex();
    }

    TreeNode* childNode = static_cast<TreeNode*>(index.internalPointer());
    TreeNode* parentNode = childNode->parent();

    if(parentNode == pRootNode)
    {
        return QModelIndex();

    }
    return createIndex(parentNode->row(),0,parentNode);
}

