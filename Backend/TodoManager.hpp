#pragma once
#include <QObject>
#include <QtQml>
#include "TodoModel.hpp"
#include "TodoFilter.hpp"

class TodoManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TodoFilter* proxyModel READ proxyModel)

    Q_PROPERTY(int totalCount READ totalCount)
    Q_PROPERTY(int doneCount READ doneCount)
    Q_PROPERTY(int todoCount READ todoCount)

    QML_NAMED_ELEMENT(TodoManager);

public:
    explicit TodoManager(QObject *parent = nullptr) : QObject(parent) {}

    enum class Filter
    {
        All,
        Done,
        Todo
    };
    Q_ENUM(Filter)

    bool setModel(TodoModel *model);
    bool setProxyModel(TodoFilter *filterModel);

    Q_INVOKABLE bool addTask(const QString &desc);
    Q_INVOKABLE bool removeTask(const QString &uuid);
    Q_INVOKABLE bool setDone(const QString &uuid, bool done);
    Q_INVOKABLE bool setFilter(Filter filter);

    int totalCount() const;
    int doneCount() const;
    int todoCount() const;

    TodoFilter* proxyModel() const;

private:
    TodoModel *m_model{nullptr};
    TodoFilter *m_proxyModel{nullptr};
};