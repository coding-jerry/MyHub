#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "fileinfo.h"
int main(int argc, char *argv[])
{
    qDebug() << "------" << endl;
//    FileInfo file;
    qmlRegisterType<FileInfo>("FileInfo",1,0,"FileInfo");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
