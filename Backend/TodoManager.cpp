#include "TodoManager.hpp"
#include <QUuid>
#include <QVariant>

bool TodoManager::setModel(TodoModel* model)
{
    m_model = model;
    return true;
}

bool TodoManager::addTask(const QString& desc)
{
    if (!m_model)
        return false;
    Task_t task {
        .uuid = QUuid::createUuid().toString(),
        .description = desc,
        .done = false
    };
    m_model->addTask(task);
    return true;
}

bool TodoManager::removeTask(const QString& uuid)
{
    if (!m_model)
        return false;
    m_model->removeTask(uuid);
    return true;
}

bool TodoManager::setDone(const QString &uuid, bool done)
{
    if (!m_model)
        return false;
    m_model->setDone(uuid, done);
    return true;
}

bool TodoManager::setFilter(Filter filter)
{
    return true;
}
