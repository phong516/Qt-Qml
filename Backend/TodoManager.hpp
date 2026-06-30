#pragma once
#include <QObject>
#include <QtQml>
#include "TodoModel.hpp"

class TodoManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(TodoModel* model WRITE setModel)
    QML_NAMED_ELEMENT(TodoManager);
public:
    explicit TodoManager(QObject* parent = nullptr, TodoModel* model = nullptr): QObject(parent), m_model(model) {}

    enum class Filter {All, Done, Todo};
    Q_ENUM(Filter)

    bool setModel(TodoModel *model);

    Q_INVOKABLE bool addTask(const QString &desc);
    Q_INVOKABLE bool removeTask(const QString& uuid);
    Q_INVOKABLE bool setDone(const QString& uuid, bool done);
    Q_INVOKABLE bool setFilter(Filter filter);
private:
    TodoModel* m_model{nullptr};
    bool updateCount();
    bool resetCount();
};