#ifndef SCORELISTVIEW_H
#define SCORELISTVIEW_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>
#include <QtDebug>

class ScoreListView : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        ScorRole = Qt::UserRole + 1,
        NameRole,
    };

    explicit ScoreListView(QObject* parent = nullptr);
    ~ScoreListView();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QVariant dataForQml(int row,int role = Qt::DisplayRole);

    virtual QHash<int,QByteArray> roleNames() const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index,const QVariant &value,int role) override;
    //position 加入的位置，rows 加入多少行
    bool insertRows(int position,int rows,const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position,int rows,const QModelIndex &parent = QModelIndex()) override;
};

#endif // SCORELISTVIEW_H
