#include "TodoManager.hpp"
#include <QUuid>
#include <QVariant>

bool TodoManager::setModel(TodoModel *model)
{
    m_model = model;
    return true;
}

bool TodoManager::setProxyModel(TodoProxyModel *filterModel)
{
    m_proxyModel = filterModel;
    emit proxyModelChanged();
    return true;
}

bool TodoManager::addTask(const QString &desc)
{
    if (!m_model)
        return false;
    Task_t task{
        .uuid = QUuid::createUuid().toString(),
        .description = desc,
        .done = false};
    m_model->addTask(task);
    emit countChanged();
    return true;
}

bool TodoManager::removeTask(const QString &uuid)
{
    if (!m_model)
        return false;
    m_model->removeTask(uuid);
    emit countChanged();
    return true;
}

bool TodoManager::setDone(const QString &uuid, bool done)
{
    if (!m_model)
        return false;
    m_model->setDone(uuid, done);
    emit countChanged();
    return true;
}

bool TodoManager::setFilter(const QString& filter)
{
    if (!m_proxyModel)
        return false;
    const QHash<QString, Filter> filterMap{
        {"all", All},
        {"done", Done},
        {"todo", Todo}
    };
    auto it = filterMap.find(filter);
    if (it != filterMap.end())
    {
        m_proxyModel->setFilter(it.value());
    }
    return true;
}

int TodoManager::totalCount() const
{
    return m_model ? m_model->totalCount() : 0;
}

int TodoManager::doneCount() const
{
    return m_model ? m_model->doneCount() : 0;
}

int TodoManager::todoCount() const
{
    return m_model ? m_model->todoCount() : 0;
}

TodoProxyModel *TodoManager::proxyModel() const
{
    return m_proxyModel;
}
