#pragma once
#include <QObject>
#include <QtQml>
#include "model/TodoModel.hpp"
#include "proxy/TodoProxyModel.hpp"

class TodoManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TodoProxyModel* proxyModel READ proxyModel NOTIFY proxyModelChanged)

    Q_PROPERTY(int totalCount READ totalCount NOTIFY countChanged)
    Q_PROPERTY(int doneCount READ doneCount NOTIFY countChanged)
    Q_PROPERTY(int todoCount READ todoCount NOTIFY countChanged)

public:
    explicit TodoManager(QObject *parent = nullptr) : QObject(parent) {}


    bool setModel(TodoModel *model);
    bool setProxyModel(TodoProxyModel *filterModel);

    Q_INVOKABLE bool addTask(const QString &desc);
    Q_INVOKABLE bool removeTask(const QString &uuid);
    Q_INVOKABLE bool setDone(const QString &uuid, bool done);
    Q_INVOKABLE bool setFilter(const QString& filter);

    int totalCount() const;
    int doneCount() const;
    int todoCount() const;

    TodoProxyModel* proxyModel() const;

signals:
    void proxyModelChanged();
    void countChanged();

private:
    TodoModel *m_model{nullptr};
    TodoProxyModel *m_proxyModel{nullptr};
};