#ifndef PREVIEWINMURRAY_H
#define PREVIEWINMURRAY_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDebug>
#include <QList>
#include <QMutex>

class PreviewInMurray: public QObject
{
    Q_OBJECT
public:
    class releaseInstance
    {
    public:
        ~releaseInstance()
        {
            qDebug() << __FUNCTION__ << __LINE__ << "~releaseInstance"<< endl;
            if(PreviewInMurray::m_previewInMurray)
            {
                for (int i = 0; i < PreviewInMurray::processList->size(); ++i) {
                    processList->at(i)->finished(1);
                    processList->at(i)->waitForFinished();
                }
                PreviewInMurray::processList->clear();
                delete PreviewInMurray::processList;
                delete PreviewInMurray::m_previewInMurray;
            }
        }
    };
    Q_INVOKABLE void finishAllProgram();
    static PreviewInMurray* getInstance();

    static QObject* create_previewInMurray(QQmlEngine *engine,QJSEngine *scriptEngine);//qmlRegisterSingletonType的回调函数
    static releaseInstance m_releaseClass;
    Q_INVOKABLE  bool openTargetFile(const QString& program = /*"G:/murray_release/release/Murray.exe"*/"C:\\WINDOWS\\system32\\mspaint.exe" ,const QString &argument = "C:\\Users\\10314\\Desktop\\123.bmp");
    static QList< QProcess* > *processList;
protected:
    static PreviewInMurray *m_previewInMurray;
    static QMutex mutex;
private:
    explicit PreviewInMurray(QObject* parent = nullptr);
    ~PreviewInMurray();


};

#endif // PREVIEWINMURRAY_H
