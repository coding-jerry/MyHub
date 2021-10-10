#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <fstream> //std::ofstream
#include <QMutex>
#include <QFile>
#include "filesystemwatcher.h"

#if defined(QT_NO_DEBUG) //设置release标志位，release才输出log文档
#   define _RELEASE_VERSION 1
#else
#   define _DEBUG_VERSION 1
#endif

std::ofstream outDebug_log;
#define CURRENT_PATH "./log/"
void debugMessageLog(QtMsgType _type,const QMessageLogContext &context,const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

     if(_type == QtDebugMsg)
     {
         //输出格式
         QString logtext = "qDebug:  ";
         QString context_info = QString("F:(%1) L:(%2)").arg(QString(context.file)).arg(context.line);
         QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
         QString current_date = QString("(%1)").arg(current_date_time);

//         std::string message = qPrintable(QString("%1 %2 \t%3 \t%4").arg(logtext).arg(context_info).arg(current_date).arg(msg)); //(qDebug:) (F:fileInfo L:Line) (dateTime) (qDebug->Message)
//         outDebug_log << message << "\r\n";
         QString strMsg = QString("%1 %2 \t%3 \t%4").arg(logtext).arg(context_info).arg(current_date).arg(msg);
         QString logtxt = QString("compareFilesLog.txt");
         QFile file(CURRENT_PATH + logtxt);
         if(file.open(QIODevice::ReadWrite | QIODevice::Append ))
         {
             QTextStream stream(&file);
             stream << strMsg << "\r\n";
             file.flush();
             file.close();
         }
     }
     const char *file = context.file ? context.file : "";
     const char *function = context.function ? context.function : "";
     QByteArray localMsg = msg.toLocal8Bit();
//     fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
     fprintf(stderr, "Debug: %s (%s:%u, %s)\n", file, function, context.line, localMsg.constData());

     mutex.unlock();
}
int main(int argc, char *argv[])
{
#if _RELEASE_VERSION
    qInstallMessageHandler(debugMessageLog);
#endif

    /*
     * 输出文件
     * 未能指定相关路径
     */
    /*
    QString logtxt =  QString(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
    logtxt.append("-log.txt");
    qDebug() << logtxt << endl;
    outDebug_log.open(qPrintable(logtxt),std::ios::out | std::ios::trunc);
    */
    FileSystemWatcher::addWatchTarPath("Z:/Bewatched/sii.txt");
    FileSystemWatcher::addWatchTarPath("Z:/Bewatched/");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
