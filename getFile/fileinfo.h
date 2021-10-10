#ifndef FILEINFO_H
#define FILEINFO_H
#include <QObject>
#include <QDir>
#include <QFile>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QList>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QCryptographicHash>
#define DEFAULT_PATH "D:/root"
class FileInfo: public QObject
{
    Q_OBJECT
public:
    FileInfo();
    void loadJson();
    QList<QString> compareFileJson();
    QList<QVariantMap> loadFileInfo(const QString &dir,QList<QVariantMap> &listFileInfo);

    void createJsonValue(const QString &fileName , const QMap<QString,QString>&fileInfoList ,const QStringList & folderName  , bool isfile = true );
    Q_INVOKABLE QList<QVariantMap> getListFileInfo() const;

signals:
    void sendLocalFileInfoList(const QList<QVariantMap> listFileInfo);
private:
    QList<QString> *fileList;
    int m_nFilesCount;//文件个数
    int m_nDirCount;//目录个数
//    QJsonObject root;
//    QStringList splitPathName;
    QMap<QString,QString> *fileInfoList;//保存文件对应的信息
    QMap<QString,QJsonObject> *allFolderName;//保存所有出现的目录 key 目录名 value 代表文件名
    QList<QVariantMap> listFileInfo;
};

#endif // FILEINFO_H
