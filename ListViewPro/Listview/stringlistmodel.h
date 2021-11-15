#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H
#include <QAbstractListModel>
#include <QStringList>
#include <QtDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>

#include "filesystemwatcher.h"

class StringListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
      DescriptionRole = Qt::UserRole,
      LocalPath       = Qt::UserRole + 1,
    };
    explicit StringListModel(QObject* parent = nullptr);
    ~ StringListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QVariant dataForQml(int row,int role = Qt::DisplayRole);
    QVariant getLocalPath(int row,int role = Qt::DisplayRole);
    virtual QHash<int,QByteArray> roleNames() const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index,const QVariant &value,int role) override;

    //position 加入的位置，rows 加入多少行
    bool insertRows(int position,int rows,const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position,int rows,const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE bool textInsertRows(int position,int rows,QVariant text);
    Q_INVOKABLE bool textRemoveRows(int position,int rows);

protected:
    void initFunc();
    bool getAllFiles(const QString & path,QStringList & fileList);
public slots:
    void rcvDirectoryUpdated(QStringList &newFileList,QStringList &delFileList);
    void rcvFileUpdated(const QString &path);

private:
    FileSystemWatcher *fileWathcerInstance;
    QStringList stringList;

    QStringList *newFilesList; //增加的文件
    QStringList *delFilesList; //删除的文件
    QString path;

};

#endif // STRINGLISTMODEL_H
