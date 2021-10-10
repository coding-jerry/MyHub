#include "treenode.h"


/* 树的节点信息
 * TreeNode *pParentNode;//存放父节点
 * QList<TreeNode*> mChildeNodes;//存放子节点，可能有很多
 * QList<QVariant> mNodeData;//存放数据
*/
TreeNode::TreeNode(const QList<QVariant> &data,TreeNode* parent)
{
    this->pParentNode = parent;
    this->mNodeData = data;
}

TreeNode::~TreeNode()
{

}

void TreeNode::appendChild(TreeNode *child)
{
    child->setParent(this);
    mChildeNodes.append(child);
}

void TreeNode::deleteAllChild()
{
    for(int index = 0;index < mChildeNodes.size();index++)
    {
        mChildeNodes[index]->deleteAllChild();
    }
    qDeleteAll(mChildeNodes);
    mChildeNodes.clear();
}

TreeNode *TreeNode::child(int row)
{
    return mChildeNodes.value(row);
}

int TreeNode::childCount() const
{
    return mChildeNodes.count();
}

int TreeNode::columnCount() const
{
    return mNodeData.count();
}

QVariant TreeNode::data(int column) const
{
    return mNodeData.value(column);
}

int TreeNode::row() const
{
    return pParentNode == nullptr ? 0:pParentNode->mChildeNodes.indexOf(const_cast<TreeNode*>(this));
}

TreeNode *TreeNode::parent()
{
    return this->pParentNode;
}

void TreeNode::setParent(TreeNode *parent)
{
    this->pParentNode = parent;
}

void TreeNode::setNodeData(QVariant data, int index)
{
    this->mNodeData[index] = data;
}
