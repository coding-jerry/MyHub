#include "PreviewInMurray.h"
#include <QDebug>
#include <QFileInfo>
#include <iostream>

PreviewInMurray* PreviewInMurray::m_previewInMurray = nullptr;
QList<QProcess*>* PreviewInMurray::processList;
QMutex PreviewInMurray::mutex;
PreviewInMurray::PreviewInMurray(QObject* parent):QObject(parent)
{
    qDebug() << __FUNCTION__ << __LINE__ << endl;

}

PreviewInMurray::~PreviewInMurray()
{
    std::cout << "~PreviewInMurray" << std::endl;
}

void PreviewInMurray::finishAllProgram()
{
    qDebug() << "proCess ID "<< processList->at(0)->processId();
    for (int i = 0; i < PreviewInMurray::processList->size(); ++i) {

       QProcess* m_pro = processList->at(i);
       if(m_pro->isOpen())
       {
           m_pro->close();
       }
    }
}

PreviewInMurray *PreviewInMurray::getInstance()
{
    if(!m_previewInMurray)
    {
        QMutexLocker locker(&mutex);
        if(!m_previewInMurray)
        {
            m_previewInMurray = new PreviewInMurray;
            processList = new QList<QProcess*>;
        }
    }
    return m_previewInMurray;
}

QObject *PreviewInMurray::create_previewInMurray(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if(!m_previewInMurray)
    {
        m_previewInMurray = new PreviewInMurray;
        PreviewInMurray::processList = new QList< QProcess* >;
    }
    return m_previewInMurray;
}

bool PreviewInMurray::openTargetFile(const QString &program, const QString &argument)
{
    bool retResult = true;
    QFileInfo tarFile = QFileInfo(argument);
    qDebug() << __FUNCTION__ << __LINE__ << tarFile.absoluteFilePath() << endl;
    QProcess *tarPro = new QProcess();
    processList->append(tarPro); //保存进程列表
    qDebug() << __FUNCTION__ << __LINE__ << processList->at(0)->processId() << tarPro->processId();
    QStringList argS = QStringList(argument);
//    QStringList argS;
//    argS << "--init_geo_path=" << "resource\geometry\hoverbike\TheRocket.obj";
    QString arg1 = "C:\\WINDOWS\\system32\\mspaint.exe";
    QString arg2 = " C:\\Users\\10314\\Desktop\\123.bmp";
    QString common = arg1 + arg2 ;
    tarPro->start(common);
//    tarPro->execute(program,argS);
//    QProcess::startDetached(program,argS);
    qDebug() << __FUNCTION__ << __LINE__ << tarPro->waitForStarted() << program;
//    int retCode = tarPro->execute(program,argS);
//    qDebug() << retCode<< endl;
    return retResult;
}
