#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "PreviewInMurray.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
//    qmlRegisterType<PreviewInMurray>("PreviewInMurray",1,0,"PreIM");
    PreviewInMurray::getInstance();
//    previewIM->create_previewInMurray(nullptr,nullptr);
    qmlRegisterSingletonType<PreviewInMurray>("PreviewInMurray",1,0,"PreIM",PreviewInMurray::create_previewInMurray);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
