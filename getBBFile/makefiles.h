#ifndef MAKEFILES_H
#define MAKEFILES_H
#include <QString>
#include <QObject>
#include <QFile>
#include <QFileInfo>


class MakeFiles :public QObject
{
    Q_OBJECT
public:
    MakeFiles();
    bool writeTargetFiles(QString fileName = "file",QString type = "txt",int fileNUm = 5,double fileSize = 1024*1000*10);

    void setSavePath(const QString &value);

signals:
    void sendProgress(int size);
protected:
    static void write_Thread(QString pathAndName,int fileSize,MakeFiles* parent,char c);
    bool write_files(QString pathAndName,int fileSize,char content);
    char c;
    QString savePath;

};

#endif // MAKEFILES_H
