#ifndef FILEPROCESS_H
#define FILEPROCESS_H

#include<QProcess>
#include<QObject>
#include<QList>

class FileProcess:public QObject
{
    Q_OBJECT
public:
    FileProcess(QObject *parent = nullptr);
//    ~FileProcess();
    Q_INVOKABLE bool openTargetFile(const QString &program = "C:/WINDOWS/system32/mspaint.exe", const QString &argument = "C:\\Users\\m\\Desktop\\1.bmp");
    Q_INVOKABLE bool closeTargetProgram();
private:
    QList<QProcess*> *listPro;
};

#endif // FILEPROCESS_H
