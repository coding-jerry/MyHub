#include "filesystemwatcher.h"

FileSystemWatcher* FileSystemWatcher::pInstance;
FileSystemWatcher::FileSystemWatcher(QObject *parent) : QObject(parent)
{

}

void FileSystemWatcher::addWatchTarPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);
    if(pInstance == nullptr)
    {
        pInstance = new FileSystemWatcher();
        pInstance->pQFileSystemWatcher = new QFileSystemWatcher();

        connect(pInstance->pQFileSystemWatcher,SIGNAL(directoryChanged(QString)),
                pInstance,SLOT(directoryUpdated(QString)));
        connect(pInstance->pQFileSystemWatcher,SIGNAL(fileChanged(QString)),
                pInstance,SLOT(fileUpdated(QString)));

        connect(pInstance,SIGNAL(sendDirUpdated(QStringList&,QStringList&)),
                pInstance,SLOT(rcvDirUpdated(QStringList&,QStringList&)));
        connect(pInstance,SIGNAL(sendFileUpdated(QString)),
                pInstance,SLOT(rcvFileUpdated(QString)));
    }
    //添加监控路径
    pInstance->pQFileSystemWatcher->addPath(path);

    QFileInfo file(path);
    if(file.isDir())
    {
        qDebug() << __FUNCTION__ << __LINE__ << path << " is dir" << endl;
        const QDir dirw(path);
        pInstance->m_currentContentMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

void FileSystemWatcher::directoryUpdated(const QString &path)
{
    qDebug() << QString("Directory updated: %1").arg(path);
    QStringList currEntryList = m_currentContentMap[path]; //之前保存的文件和目录
    const QDir dir(path);

    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst); //现在保存的文件和目录

    foreach (QString str, currEntryList)
    {
        qDebug() << "currEntryList: "<< str;
    }
    qDebug( ) << "***************************"<< endl;

    foreach (QString str, newEntryList)
    {
        qDebug() << "newEntryList: "<< str;
    }
    qDebug( ) << "+++++++++++++++++++++++++++"<< endl;

    //计算差值--可得到删除或增加
    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);

    //增加 当前列表大于之前列表
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFliesList = newFiles.toList();

    //删除 之前列表大于当前列表
    QSet<QString> delFiles = currentDirSet - newDirSet;
    QStringList delFilesList =delFiles.toList();

    foreach (QString str, newFliesList)
    {
        qDebug() << "newFliesList: "<< str;
    }
    qDebug( ) << "---------------------------"<< endl;

    foreach (QString str, delFilesList)
    {
        qDebug() << "delFilesList: "<< str;
    }
    qDebug( ) << "+++++++++++++++++++++++++++"<< endl;

    m_currentContentMap[path] = newFliesList;

    emit sendDirUpdated(newFliesList,delFilesList);
}

void FileSystemWatcher::fileUpdated(const QString &path)
{
    QFileInfo file(path);
    QString strPath = file.absolutePath();
    QString strName = file.fileName();

    qDebug() << QString("The file %1 at path %2 is updated").arg(strName).arg(strPath) << endl;
    emit sendFileUpdated(path);
}

void FileSystemWatcher::rcvDirUpdated(QStringList &newFilesList, QStringList &delFilesList)
{
    qDebug() << __FUNCTION__ << __LINE__;
    if(!newFilesList.isEmpty() && !delFilesList.isEmpty())
    {
        qDebug() << __FUNCTION__ << __LINE__ << "has new files and del files";
        foreach (QString str, newFilesList)
        {
            qDebug() << str << "(new)";
        }
        foreach (QString str, delFilesList)
        {
            qDebug() << str << "(del)";
        }
    }
    else
    {
        if(!newFilesList.isEmpty())
        {
            qDebug() << __FUNCTION__ << __LINE__ << "has new files: " << endl;
            foreach (QString str, newFilesList)
            {
                qDebug() << str << "(new)";
            }
        }
        if(!delFilesList.isEmpty())
        {
            qDebug() << __FUNCTION__ << __LINE__ << "has del files: " << endl;
            foreach (QString str, delFilesList)
            {
                qDebug() << str << "(del)";
            }
        }
    }
}

void FileSystemWatcher::rcvFileUpdated(const QString &filePath)
{
    QFileInfo file(filePath);
    QString strPath = file.absolutePath();
    QString strName = file.fileName();

    qDebug() << __FUNCTION__ << __LINE__ << QString("The file %1 at path %2 is updated").arg(strName).arg(strPath) << endl;
}
