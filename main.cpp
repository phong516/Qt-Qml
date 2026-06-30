#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Backend/TodoManager.hpp"
#include "Backend/TodoModel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    
    // TodoManager manager;
    // TodoModel model;
    // manager.setModel(&model);
    
    // engine.rootContext()->setContextProperty("TodoManager", &manager);

#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("learn", "Main");
#else
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [](QObject *obj, const QUrl &) {
            if (!obj)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral("qrc:/learn/Main.qml")));
#endif
    
    return QCoreApplication::exec();
}
