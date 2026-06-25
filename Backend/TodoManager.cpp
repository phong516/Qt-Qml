#include "TodoManager.hpp"
#include <QUuid>
#include <QVariant>
#include <QMetaObject>

bool TodoManager::setModel(QObject* model)
{
    m_model = model;
    return true;
}

bool TodoManager::addTask(const QString& desc)
{
    if (!m_model)
        return false;
    QVariantMap task{
        {"uuid", QUuid::createUuid().toString()},
        {"desc", desc},
        {"done", false}
    };
    QVariant taskVariant = QVariant::fromValue(task);
    QMetaObject::invokeMethod(m_model, "append", Q_ARG(QVariant, taskVariant));
    return true;
}

bool TodoManager::removeTask(const QString& uuid)
{
    if (!m_model)
        return false;
    for (int i = 0; i < m_model->property("count").toInt(); ++i) {
        QVariantMap task = m_model->property("get").value<QVariantList>().at(i).toMap();
        if (task["uuid"].toString() == uuid) {
            QMetaObject::invokeMethod(m_model, "remove", Q_ARG(int, i));
            return true;
        }
    }
    return false;
}