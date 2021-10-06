#include "fileprocess.h"
#include <QDebug>

FileProcess::FileProcess(QObject* parent)
{
    listPro = new QList<QProcess*>;
}

bool FileProcess::openTargetFile(const QString &program, const QString &argument)
{
    bool retResult = false;
    qDebug() << __FUNCTION__ << __LINE__ << argument;
    QStringList argS(argument);
    QProcess* tarPro = new QProcess;
    tarPro->start(program,argS);
    qDebug() << __FUNCTION__ << __LINE__ << tarPro->processId() << endl;
    if(tarPro->processId() != 0 )
        retResult = true;
    listPro->push_back(tarPro);
    return retResult;
}

bool FileProcess::closeTargetProgram()
{
    bool retResult = false;
//    for(auto midPro = listPro;)
//    {
//        midPro->close();
//    }
    if(!listPro->isEmpty())
    {
        listPro->at(0)->close();
        listPro->removeAt(0);
        retResult = true;
    }

    return retResult;
}
