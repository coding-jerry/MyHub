#include "fileinfo.h"

FileInfo::FileInfo()
{
    //this->loadJson();

//    this->fileList = new QList<QString>;

//    this->fileInfoList = new QMap<QString,QString>();
//    this->allFolderName = new QMap<QString,QJsonObject>();
//    this->allFolderName->insert("root",this->root);
    this->m_nFilesCount = 0;
    this->m_nDirCount = 0;
//    this->listFileInfo = new QList<QVariantMap>();

    /**listFileInfo = */loadFileInfo(DEFAULT_PATH,listFileInfo);

    emit this->sendLocalFileInfoList(this->listFileInfo);
    for(int i= 0;i<this->listFileInfo.size();i++)
    {
        qDebug() << i << " fileName>>>"<< this->listFileInfo.at(i).value("fileName");
        qDebug() << "Md5>>>"<< this->listFileInfo.at(i).value("Md5") <<endl;
    }
}

void FileInfo::loadJson()
{
    QFile loadJsonFile("D:\\fileList.json");
    if(loadJsonFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "loadJsonFile success !" << endl;
    }
    QByteArray allData = loadJsonFile.readAll();
    loadJsonFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData,&jsonError));
    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "json Error >>" << jsonError.errorString();
        return;
    }
    qDebug() << "json success" << endl;
    QJsonObject rootObject = jsonDoc.object();
    if(rootObject.contains("root"))
    {
        QJsonObject typeObject = rootObject.value("root").toObject();
        QStringList keys = typeObject.keys();
        for(int i = 0;i < keys.size();i++)
        {
            qDebug() << "Key" << i << "is:" << keys.at(i) << endl;
        }
        qDebug() << "Type :" << typeObject["Type"].toString() << endl;
        QJsonObject file1 = typeObject.value("file1").toObject();
    }
}

QList<QString> FileInfo::compareFileJson()
{
    return *this->fileList;
}
//遍历目标目录获得相应的信息 保存到jsFileInfo
QList<QVariantMap> FileInfo::loadFileInfo(const QString &dir,QList<QVariantMap> &listFileInfo)
{
    QDir dirtory(dir);
    if(!dirtory.isEmpty() || dirtory.exists())
    {

        dirtory.setFilter(QDir::Dirs | QDir::Files);
        dirtory.setSorting(QDir::DirsFirst);
        QFileInfoList list = dirtory.entryInfoList();
        int i = 0;
        bool bIsDir = false;
        while (i<list.size()) {
            QFileInfo fileinfo = list.at(i);
            if(fileinfo.fileName() == "."|| fileinfo.fileName() == "..")
            {
                i++;
                continue;
            }
            bIsDir = fileinfo.isDir();
            if(bIsDir)
            {
                ++m_nDirCount;//目录个数
                QStringList floderNmae = fileinfo.filePath().split('/');
                int location = floderNmae.size()- 2;
                QString fatherName = floderNmae.at(location);
                QString folder = fileinfo.fileName();
                loadFileInfo(fileinfo.filePath(),listFileInfo);

            }
            else
            {

                QFile file(fileinfo.filePath());
                file.open(QIODevice::ReadOnly);
                QByteArray ba = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
                file.close();

                QString MD5code = ba.toHex().constData();
                QString fileName = fileinfo.fileName();
                QString fileType = fileName.split('.').last();
                QString fileLastModifiled = fileinfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");

                qDebug()<< "absoluteFilePath=" << fileinfo.path() << ">>>>" <<fileinfo.filePath();
                QVariantMap thefile;
                thefile.insert("fileName",fileName);
                thefile.insert("Md5",MD5code);
                this->listFileInfo.insert(m_nFilesCount,thefile);
                ++m_nFilesCount;//文件个数
            }
            ++i;
        }
    }
    return listFileInfo;
}

void FileInfo::createJsonValue( const QString &fileName , const QMap<QString,QString>&fileInfoList ,const QStringList & folderName , bool isfile)
{
    QJsonObject qFileInfo;
    if(isfile)
    {
        QMap<QString,QString>::const_iterator it;

        for( it = fileInfoList.constBegin();it != fileInfoList.constEnd();it++)
        {
            qFileInfo.insert(it.key(),it.value());
        }
        this->fileInfoList->clear();
    }
//    else {
//        qFileInfo.insert("Type","folder");
//    }
//    //判断是否存在QJsonObject，不存在创建
//    if(this->allFolderName->contains(folderName))
//    {
//        QJsonObject folderObject = this->allFolderName->value(folderName);//拿出整个jsonObject对象{"folder":{...}}
//        folderObject = folderObject.value(folderName).toObject();//"folder":{...}

//        folderObject.insert(fileName,qFileInfo);
////         qDebug() <<__LINE__<< folderObject << endl;
//        //刷新数据，将旧的数据拿出来让新的数据覆盖
//        this->allFolderName->remove(folderName);
//        this->allFolderName->insert(folderName,folderObject);
//    }
//    else {
//        QJsonObject midObjecct;
//        midObjecct.insert("Type","folder");
//        midObjecct.insert(fileName,qFileInfo);
//        QJsonObject folderObject;
//        folderObject.insert(folderName,QJsonValue(midObjecct));
////        qDebug() <<__LINE__<< folderObject << endl;

//        this->allFolderName->insert(folderName,folderObject);
////        qDebug() <<__LINE__<< folderObject << endl;
//    }

}

QList<QVariantMap> FileInfo::getListFileInfo() const
{
    return listFileInfo;
}

