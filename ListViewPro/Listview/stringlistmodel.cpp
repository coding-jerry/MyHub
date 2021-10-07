#include "stringlistmodel.h"

//#define PATH "D:/Creator/workPro"

StringListModel::StringListModel(QObject *parent)
{
    Q_UNUSED(parent);
    path = "D:/Creator/workPro";
    initFunc();
//    QDir the_dir(path);
//    QStringList dirList = the_dir.entryList(QDir::NoDot| QDir::NoDotDot | QDir::AllDirs | QDir::Files,QDir::DirsFirst);
//    if(dirList.contains("."))
//    {
//        dirList.removeOne(".");
//        dirList.removeOne("..");
//    }
//    stringList.append(dirList);
    bool ret = getAllFiles(path,stringList);
    if(ret){
        qDebug() << __FUNCTION__ << __LINE__ << "isSuccessful >> "  << ret;
    }
    qDebug() << __FUNCTION__ << __LINE__ << stringList.length();
}

StringListModel::~StringListModel()
{
    delete delFilesList;
    delete newFilesList;
}

int StringListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return stringList.length();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    qDebug() << __FUNCTION__ << __LINE__ ;
    QVariant retResult = QVariant();
    if(role == 0){
        role = DescriptionRole;
    }
    if(index.isValid())
    {
        switch (role)
        {
        case DescriptionRole:{
            qDebug() << __FUNCTION__ << __LINE__ << role;
            retResult = stringList.at(index.row());
            }
            break;
        }
    }
    return QVariant(retResult);
    
}

QVariant StringListModel::dataForQml(int row,int role)
{
    role = (Qt::UserRole + role);
    QVariant retResult = QVariant();
    if(row != -1)
    {
        qDebug() << row << role;
        switch (role)
        {
        case DescriptionRole:{
            qDebug() << __FUNCTION__ << __LINE__ << role;
            retResult = stringList.at(row);
            qDebug() << "retResult >>> " << retResult.toString();
        }
            break;
        case LocalPath:{
            qDebug() << __FUNCTION__ << __LINE__ << role;
            retResult = getLocalPath(row,role);
            qDebug() << "retResult >>> " << retResult.toString();
        }
        }//end switch
    }


    return retResult;
}

QVariant StringListModel::getLocalPath(int row,int role)
{
    QVariant retResult = QVariant();
    if(role == LocalPath){
        QString fileName = stringList.at(row);
        QMap<QString,QStringList> pathKey = fileWathcerInstance->getCurrentContentMap();
        foreach(QString key,pathKey.keys())
        {
            QStringList strList = pathKey[key];
            if(stringList.contains(fileName))
            {
                retResult = key;
                break;
            }
        }
    }

    return retResult;

}

QHash<int, QByteArray> StringListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DescriptionRole] = "description";
    return names;
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;

}

bool StringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool retResult = false;
    if(index.isValid() && role == DescriptionRole)
    {
        stringList.replace(index.row(),value.toString());
        emit dataChanged(index,index);
        retResult = true;
    }
    return retResult;
}

bool StringListModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    bool retResult = false;
    if(position < 0 || position > stringList.size() || rows <= 0)
    {
        retResult = false;
    }
    else{
        beginInsertRows(parent,position,position + rows - 1);
        for(int i = 0;i<rows;i++)
        {
            stringList.insert(position,newFilesList->at(i));
        }
        endInsertRows();
        retResult = true;
    }

    return retResult;

}

bool StringListModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    bool retResult = false;
    if(position < 0 || position > stringList.size() || rows <= 0)
    {
        retResult = false;
    }
    else
    {
        beginRemoveRows(parent,position,position + rows -1);
        for(int i = 0;i<rows; ++i)
        {
            stringList.removeAt(position);
        }
        endRemoveRows();
        retResult = true;
    }
    return retResult;
}

bool StringListModel::textInsertRows(int position, int rows)
{
    return insertRows(position,rows);
}

bool StringListModel::textRemoveRows(int position, int rows)
{
    return removeRows(position,rows);
}

void StringListModel::initFunc()
{
    QString filepath = "D:/Creator/workPro/";
    fileWathcerInstance = FileSystemWatcher::getPIntance();
    fileWathcerInstance->addWatchPath(filepath);
    connect(fileWathcerInstance,SIGNAL(sendDirectoryUpdated(QStringList&,QStringList&))
            ,this,SLOT(rcvDirectoryUpdated(QStringList&,QStringList&))); //监视目录新文件或删除的文件
    connect(fileWathcerInstance,SIGNAL(sendFileUpdated(QString)),
            this,SLOT(rcvFileUpdated(QString))); //监视单个文件的变化

    newFilesList = new QStringList();
    delFilesList = new QStringList();
}

bool StringListModel::getAllFiles(const QString &path,QStringList & fileList)
{
    bool retResult = true;
    QDir dir(path);
    QStringList allFileslist = dir.entryList(QDir::NoDot | QDir::NoDotDot | QDir::AllDirs | QDir::Files,QDir::DirsFirst);
    if(!allFileslist.isEmpty())
    {
        fileList << allFileslist;

        foreach(QString str,allFileslist)
        {

            QString the_path = (path + "/" + str);
            qDebug() << __FUNCTION__ << __LINE__ << "fileName :"<< the_path << endl;
            QFileInfo file(the_path);
            if(file.isDir())
            {
                fileWathcerInstance->addWatchPath(the_path);
                dir.setPath(the_path);
                getAllFiles(the_path,fileList);

            }
        }
    }
    return retResult;
}
//接收文件列表（新增和删除）
void StringListModel::rcvDirectoryUpdated(QStringList &newFileList, QStringList &delFileList)
{
    qDebug() << __FUNCTION__ << __LINE__ << "directory updated" ;

    int rows = 0;
    if(!newFileList.isEmpty())
    {
        foreach(QString str,newFileList)
        {
            qDebug() << QString("%1 is new file").arg(str);
        }
        int position = rowCount();//从尾部插入
        rows = newFileList.length();
        *this->newFilesList = newFileList;
        insertRows(position,rows);
    }

    if(!delFileList.isEmpty())
    {
        foreach(QString str,delFileList)
        {
            qDebug() << QString("%1 had been deleted").arg(str);
        }
        rows = delFileList.length();
        *this->delFilesList = delFileList;
        foreach(QString delstr,delFileList)
        {
            QStringView strView(delstr);
            int position = stringList.indexOf(strView);
            if(position != -1)
            {
                removeRows(position,1);
            }
        }
    }
}

void StringListModel::rcvFileUpdated(const QString &path)
{
    qDebug() << QString("%1 had been updated").arg(path);
}



