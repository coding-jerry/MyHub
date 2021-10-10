#include "makefiles.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

#define FILE_NAME "the_NO.%1_file.txt"
#define FILE_PATH "Z:/makeFiles/"
#define FILE_SIZE 1024*1024*10
#define FILE_NUM 20

MakeFiles::MakeFiles()
{
    qDebug() << __FUNCTION__ << __LINE__ <<endl;
    qDebug() << "ready to create your files" << endl;
}

bool MakeFiles::writeTargetFiles(QString fileName,QString type, int fileNUm, double fileSize)
{
    qDebug() << __FUNCTION__ << __LINE__ << fileNUm << endl;
    QString midFileName = "the_NO.%1_"+ fileName + "."+type;

    bool retResult = true;
    for(int i = 1; i<= fileNUm;i++)
    {
        qDebug() << __FUNCTION__ << __LINE__ <<endl;
        QString pathAndName = savePath + "/" + QString(midFileName).arg(i);
        c = c+1;
         QtConcurrent::run(write_Thread,pathAndName,fileSize,this,c);
//        bool isSucceed = write_files(pathAndName,realSize);
//        if(!isSucceed){
//            qDebug() << __FUNCTION__ << pathAndName << "write in faild" << endl;
//            retResult = false;
//        }
//        else {
//            qDebug() << __FUNCTION__ << __LINE__ << i;
//        }
    }
    return retResult;
}

void MakeFiles::write_Thread(QString pathAndName, int fileSize,MakeFiles* parent,char c)
{
   parent->write_files(pathAndName,fileSize,c);
}

bool MakeFiles::write_files(QString pathAndName,int fileSize,char content)
{
    bool isSucceed = true;
    int i = 0;
    QFile file(pathAndName);
    if(!file.open(QIODevice::WriteOnly ))
        isSucceed = false;
    for(;i<fileSize ;i++)
    {
        file.write(&content);
    }
    emit sendProgress(fileSize);
    return isSucceed;
}

void MakeFiles::setSavePath(const QString &value)
{
    savePath = value;
}
