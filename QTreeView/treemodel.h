#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <QObject>
#include <QDebug>

#include "treenode.h"

class TreeModel : public QAbstractItemModel
{

    Q_OBJECT
    enum nodeRoles {
        NAME = Qt::UserRole + 1
    };

public:
    TreeModel(QObject* parent = nullptr);//初始化节点，形成树状结构
    ~TreeModel();

    //增加子节点
    void appendChild(const QModelIndex& index,QList<QVariant> dataList,int count);

    void setNodeName(QString appendName,QModelIndex index);

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int,QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index,int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row,int column,const QModelIndex &parent= QModelIndex())const override;
    QModelIndex parent(const QModelIndex &index) const override;


private:
    TreeNode *pRootNode;
};

#endif // TREEMODEL_H
