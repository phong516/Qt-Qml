#pragma once
#include <QObject>
#include <QtQml>
#include <TodoModel.hpp>

class TodoManager: public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TodoManager(QObject* parent = nullptr): QObject(parent), m_todoModel(new TodoModel(this)){}

    enum class Filter {All, Done, Todo};
    Q_ENUM(Filter)

    Q_INVOKABLE bool addTask(const QString& desc);
    Q_INVOKABLE bool removeTask(const QString& uuid);
    Q_INVOKABLE bool setDone(const QString& uuid, bool done);
    Q_INVOKABLE bool setFilter(Filter filter);
private:
    TodoModel* m_todoModel{nullptr};
    bool updateCount();
    bool resetCount();
};