#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QMap>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QSet>


class FileSystemWatcher : public QObject
{
    Q_OBJECT
private: //Function
    explicit FileSystemWatcher(QObject *parent = nullptr);
    bool setNewFolderPath(const QString &path,const QStringList &newFileList);
private: //member
    static FileSystemWatcher *pIntance; //单例
    QFileSystemWatcher *pQFileSystemWathcer; //QFileSystemWatcher 变量
    QMap<QString,QStringList> m_currentContentMap;//每个监控内容目录列表

public: //Function
    static void addWatchPath(QString path);

    static FileSystemWatcher *getPIntance();

    QMap<QString, QStringList> getCurrentContentMap() const;

public slots:
    void directoryUpdated(const QString &path); //目录更新时调用，path是监视的路径
    void fileUpdated(const QString &path); //监视单个文件
signals:
    void sendDirectoryUpdated(QStringList &newFileList,QStringList &delFileList);
    void sendFileUpdated(const QString &newFile);

};

#endif // FILESYSTEMWATCHER_H
