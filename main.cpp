#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "render.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    auto render = new Render;

    QQmlApplicationEngine engine;
    engine.addImageProvider(QStringLiteral("a"), render);
    engine.rootContext()->setContextProperty("render", render);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
