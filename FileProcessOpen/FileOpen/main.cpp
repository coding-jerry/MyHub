#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <fileprocess.h>

static QObject* create_qObject_provider(QQmlEngine* engine,QJSEngine* scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    FileProcess* filePro = new FileProcess();
    return filePro;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty("FileOP",new FileProcess(qApp));
    qmlRegisterSingletonType<FileProcess>("FileProcess",1,0,"FileOP",create_qObject_provider);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

