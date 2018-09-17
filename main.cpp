#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "render.h"
#include "automaton.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("automaton_model", new Automaton);
    engine.addImageProvider(QStringLiteral("a"), new Render(110));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
