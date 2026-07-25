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

bool TodoManager::setStorage(TodoStorageInterface *storage)
{
    m_storage = storage;
    return true;
}

bool TodoManager::run()
{
    if (!m_model)
    {
        qFatal("TodoManager: Model is not set. Please set a model before running the manager.");
        return false;
    }
    if (m_storage)
    {
        loadTasks(); 
    }
    else
    {
        qWarning() << "TodoManager: Storage is not set. Tasks will not be loaded from storage.";
    }
    return false;
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
    sync();
    return true;
}

bool TodoManager::removeTask(const QString &uuid)
{
    if (!m_model)
        return false;
    m_model->removeTask(uuid);
    sync();
    return true;
}

bool TodoManager::setDone(const QString &uuid, bool done)
{
    if (!m_model)
        return false;
    m_model->setDone(uuid, done);
    sync();
    return true;
}

bool TodoManager::setFilter(const QString &filter)
{
    if (!m_proxyModel)
        return false;
    const QHash<QString, Filter> filterMap{
        {"all", All},
        {"done", Done},
        {"todo", Todo}};
    auto it = filterMap.find(filter);
    if (it != filterMap.end())
    {
        m_proxyModel->setFilter(it.value());
    }
    return true;
}

bool TodoManager::loadTasks()
{
    if (!m_storage || !m_model)
        return false;
    StorageResult result = m_storage->load(m_model->tasks());
    if (!result.ok())
    {
        qWarning() << "TodoManager: Failed to load tasks from storage:" << result.message
                    << "Error code:" << static_cast<int>(result.error);
        return false;
    }
    return true;
}

bool TodoManager::saveTasks(const QList<Task_t> &tasks)
{
    syncDown();
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

bool TodoManager::sync()
{
    syncUp();
    syncDown();
    return true;
}

StorageResult TodoManager::syncDown()
{
    if (!m_storage || !m_model)
        return StorageResult{StorageError::None, "m_storage or m_model is null"};
    return m_storage->save(m_model->tasks());
}

bool TodoManager::syncUp()
{
    emit countChanged();
    return true;
}
