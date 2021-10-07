#include "filesystemwatcher.h"

FileSystemWatcher* FileSystemWatcher::pIntance = nullptr;
FileSystemWatcher::FileSystemWatcher(QObject *parent) : QObject(parent)
{

}

bool FileSystemWatcher::setNewFolderPath(const QString &path,const QStringList &newFileList)
{
    qDebug() << __FUNCTION__ << __LINE__  << " path >> "<< path;
    bool retResult = false;
    foreach(QString str,newFileList)
    {
        QString the_path = (path + "/" + str);
        QFileInfo file(the_path);
        if(file.isDir())
        {
            qDebug() << __FUNCTION__ << __LINE__ << the_path;
            pIntance->addWatchPath(the_path);
            QDir dir(the_path);
            QStringList newFileList = dir.entryList(QDir::NoDot | QDir::NoDotDot | QDir::AllDirs | QDir::Files,QDir::DirsFirst);
            qDebug() << __FUNCTION__ << __LINE__ << newFileList.length();
            setNewFolderPath(the_path,newFileList);
            retResult = true;
        }
    }

    return retResult;
}

QMap<QString, QStringList> FileSystemWatcher::getCurrentContentMap() const
{
    return m_currentContentMap;
}

FileSystemWatcher *FileSystemWatcher::getPIntance()
{
    if(pIntance == nullptr)
    {
        pIntance = new FileSystemWatcher();
        pIntance->pQFileSystemWathcer = new QFileSystemWatcher();

        //链接QFileSystem 信号 directoryChanged和 fileChanged
        connect(pIntance->pQFileSystemWathcer,SIGNAL(directoryChanged(QString)),pIntance,SLOT(directoryUpdated(QString)));
        connect(pIntance->pQFileSystemWathcer,SIGNAL(fileChanged(QString)),pIntance,SLOT(fileUpdated(QString)));
    }
    return pIntance;
}

void FileSystemWatcher::addWatchPath(QString path)
{
    qDebug() << QString("watching path: %1").arg(path);
    if(pIntance == nullptr)
    {
        pIntance = new FileSystemWatcher();
        pIntance->pQFileSystemWathcer = new QFileSystemWatcher();

        //链接QFileSystem 信号 directoryChanged和 fileChanged
        connect(pIntance->pQFileSystemWathcer,SIGNAL(directoryChanged(QString)),pIntance,SLOT(directoryUpdated(QString)));
        connect(pIntance->pQFileSystemWathcer,SIGNAL(fileChanged(QString)),pIntance,SLOT(fileUpdated(QString)));
    }
    pIntance->pQFileSystemWathcer->addPath(path);
    QFileInfo file(path);
    if(file.isDir())
    {
        //拿到目录后先遍历是否存在文件夹，如果存在就加入
        const QDir the_dir(path);
        pIntance->m_currentContentMap[path] = the_dir.entryList(QDir::NoDot | QDir::NoDotDot | QDir::AllDirs | QDir::Files,QDir::DirsFirst);
        pIntance->setNewFolderPath(path,pIntance->m_currentContentMap[path]);
    }
}
//接收监控地址的文件变化
void FileSystemWatcher::directoryUpdated(const QString &path)
{
    qDebug() << QString("Dir updated: %1").arg(path);

    QStringList currEntryList = m_currentContentMap[path];
    const QDir dir(path);

    QStringList newEntryList = dir.entryList(QDir::NoDot | QDir::NoDotDot | QDir::AllDirs | QDir::Files,QDir::DirsFirst);

    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);

    //添加新文件
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFile = newFiles.toList();

    //删除文件
    QSet<QString> delFiles = currentDirSet - newDirSet;
    QStringList delFile = delFiles.toList();

    //更新当前设置
    m_currentContentMap[path] = newEntryList;

    if(!newFile.isEmpty() && !delFile.isEmpty())
    {
        pIntance->setNewFolderPath(path,newFile);
        qDebug() << __FUNCTION__ << __LINE__ << "has new files and deleted files";
    }
    else
    {
        if(!newFile.isEmpty())
        {
            pIntance->setNewFolderPath(path,newFile);
            qDebug() << __FUNCTION__ << __LINE__ << "has new files";
        }
        if(!delFile.isEmpty())
        {
            qDebug() << __FUNCTION__ << __LINE__ << "has deleted files";
        }
    }
    //向列表发送文件列表（新增或删除）
    emit sendDirectoryUpdated(newFile,delFile);
}

void FileSystemWatcher::fileUpdated(const QString &path)
{
    QFileInfo file(path);
    QString strPath = file.absolutePath();
    QString strName = file.fileName();

    qDebug() << QString("the file %1 at path %2 is updated").arg(strName).arg(strPath);
    emit sendFileUpdated(strName);
}
