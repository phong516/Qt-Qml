#include "TodoModel.hpp"
#include <algorithm>

int TodoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.size();
}

QVariant TodoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_data.size())
    {
        return QVariant();
    }
    const Task_t &task = m_data[index.row()];
    switch (role)
    {
    case TaskRole::uuidRole:
        return task.uuid;
    case TaskRole::descriptionRole:
        return task.description;
    case TaskRole::doneRole:
        return task.done;
    }
    return QVariant();
}

QHash<int, QByteArray> TodoModel::roleNames() const
{
    QHash<int, QByteArray> roles{};
    roles[TaskRole::uuidRole] = "uuid";
    roles[TaskRole::descriptionRole] = "desc";
    roles[TaskRole::doneRole] = "done";
    return roles;
}

bool TodoModel::addTask(const Task_t &task)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(task);
    endInsertRows();
    return true;
}

bool TodoModel::removeTask(const QString &uuid)
{
    const auto it = std::find_if(m_data.begin(), m_data.end(), [&uuid](const Task_t &task)
                                 { return task.uuid == uuid; });
    if (it != m_data.end())
    {
        beginRemoveRows(QModelIndex(), std::distance(m_data.begin(), it), std::distance(m_data.begin(), it));
        m_data.erase(it);
        endRemoveRows();
        return true;
    }
    return false;
}

bool TodoModel::setDone(const QString &uuid, bool done)
{
    const auto it = std::find_if(m_data.begin(), m_data.end(), [&uuid](const Task_t &task)
                                 { return task.uuid == uuid; });
    if (it != m_data.end())
    {
        it->done = done;
        QModelIndex index = this->index(std::distance(m_data.begin(), it));
        emit dataChanged(index, index, {TaskRole::doneRole});
        return true;
    }
    return false;
}

int TodoModel::totalCount() const
{
    return m_data.size();
}

int TodoModel::doneCount() const
{
    return std::count_if(m_data.begin(), m_data.end(), [](const Task_t &task)
                         { return task.done; });
}

int TodoModel::todoCount() const
{
    return std::count_if(m_data.begin(), m_data.end(), [](const Task_t &task)
                         { return !task.done; });
}
