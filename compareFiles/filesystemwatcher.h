#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H
/*
 * 实时监测某一路径下文件变化
 *
*/
#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

class FileSystemWatcher : public QObject
{
    Q_OBJECT
public:
    ~FileSystemWatcher(){}
    static void addWatchTarPath(QString path);
public slots:
    void directoryUpdated(const QString &path); //目录更新时调用，path为监控路径
    void fileUpdated(const QString &path);//文件更新时调用

    void rcvDirUpdated(QStringList &newFilesList,QStringList &delFilesList);//监测整个路径下删除或增加的文件或文件夹
    void rcvFileUpdated(const QString &filePath);//监测单个文件

signals:
    void sendDirUpdated(QStringList &newFilesList,QStringList &delFilesList);
    void sendFileUpdated(const QString &filePath);

private:
    explicit FileSystemWatcher(QObject *parent = nullptr);
private:
    static FileSystemWatcher * pInstance; //单例
    QFileSystemWatcher *pQFileSystemWatcher; //变量
    QMap<QString,QStringList> m_currentContentMap;//目录内容

};

#endif // FILESYSTEMWATCHER_H
