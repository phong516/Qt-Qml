#pragma once
#include <QObject>
#include <QtQml>

class TodoManager: public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TodoManager(QObject* parent = nullptr): QObject(parent) {}

    enum class Filter {All, Done, Todo};
    Q_ENUM(Filter)

    Q_INVOKABLE bool addTask(const QString& desc);
    Q_INVOKABLE bool removeTask(const QString& uuid);
    Q_INVOKABLE bool setDone(const QString& uuid, bool done);
    Q_INVOKABLE bool setFilter(Filter filter);
private:
    QObject* m_model{nullptr};
    bool updateCount();
    bool resetCount();
};