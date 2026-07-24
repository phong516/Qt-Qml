#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include "types/TodoTypes.hpp"

class TodoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TodoModel(QObject * parent = nullptr): QAbstractListModel(parent) {}
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = doneRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool addTask(const Task_t& task);
    bool removeTask(const QString& uuid);
    bool setDone(const QString& uuid, bool done);

    int totalCount() const;
    int doneCount() const;
    int todoCount() const;

    // TODO: const QList<Task_t>& tasks() const;

private:
    QList<Task_t> m_data{};
};