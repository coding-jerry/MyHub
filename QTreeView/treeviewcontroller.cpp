#include "treeviewcontroller.h"

TreeViewController::TreeViewController(QObject *parent) : QObject(parent)
{
    this->m_TreeModel = new TreeModel();
}

TreeViewController::~TreeViewController()
{
    delete this->m_TreeModel;
}

QAbstractItemModel *TreeViewController::getTreeModel()
{
    return m_TreeModel;
}

void TreeViewController::updateNodeName(const QModelIndex &index)
{
    this->m_TreeModel->setNodeName("1",index);
}

void TreeViewController::updateNode(const QModelIndex &index)
{
    QList<QVariant> list_sc;
    list_sc.append("四川");
    this->m_TreeModel->appendChild(index,list_sc,0);

    QList<QVariant> list_bj;
    list_bj.append("北京");
    this->m_TreeModel->appendChild(index,list_bj,1);
}
