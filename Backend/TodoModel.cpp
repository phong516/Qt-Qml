#include "TodoModel.hpp"
#include <algorithm>

int TodoModel::rowCount(const QModelIndex & parent) const
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
    const Task_t& task = m_data[index.row()];
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

QHash<int,QByteArray> TodoModel::roleNames() const
{
    QHash<int, QByteArray> roles{};
    roles[TaskRole::uuidRole] = "uuid";
    roles[TaskRole::descriptionRole] = "desc";
    roles[TaskRole::doneRole] = "done";
    return roles;
}

bool TodoModel::addTask(const Task_t &task)
{
    m_data.push_back(task);
    return true;
}

bool TodoModel::removeTask(const QString &uuid)
{
    const auto it = std::find_if(m_data.begin(), m_data.end(), [&uuid](const Task_t& task) { return task.uuid == uuid; });
    if (it != m_data.end())
    {
        m_data.erase(it);
        return true;
    }
    return false;
}

bool TodoModel::setDone(const QString &uuid, bool done)
{
    const auto it = std::find_if(m_data.begin(), m_data.end(), [&uuid](const Task_t& task) { return task.uuid == uuid; });
    if (it != m_data.end())
    {
        it->done = done;
        return true;
    }
    return false;
}

bool TodoModel::setFilter(const QString &uuid, bool filter)
{
    return true;
}
