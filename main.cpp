#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Backend/manager/TodoManager.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TodoManager manager{&app};
    
    TodoModel model{&manager};
    TodoProxyModel filter{&model};
    TodoStorageInterface *storage = new TodoJsonStorage("tasks.json");
    manager.setModel(&model);
    filter.setSourceModel(&model);
    manager.setProxyModel(&filter);
    manager.setStorage(storage);
    manager.run();

    QQmlApplicationEngine engine;
    
    engine.rootContext()->setContextProperty("manager", &manager);

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
