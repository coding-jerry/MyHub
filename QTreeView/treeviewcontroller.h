#ifndef TREEVIEWCONTROLLER_H
#define TREEVIEWCONTROLLER_H

#include <QObject>
#include "treemodel.h"

class TreeViewController : public QObject
{
    Q_OBJECT
public:
    explicit TreeViewController(QObject *parent = nullptr);
    ~TreeViewController();

public slots:
    Q_INVOKABLE QAbstractItemModel *getTreeModel();
    Q_INVOKABLE void updateNodeName(const QModelIndex& index);
    Q_INVOKABLE void updateNode(const QModelIndex& index);

private:
    TreeModel* m_TreeModel;


};

#endif // TREEVIEWCONTROLLER_H
