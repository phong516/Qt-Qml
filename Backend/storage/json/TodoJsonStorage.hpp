#pragma once

#include "TodoStorageInterface.hpp"
#include <QFile>
#include <

class TodoJsonStorage : public TodoStorageInterface
{
public:
    explicit TodoJsonStorage(const QString &filePath): m_file(filePath) {}

    StorageResult load(QList<Task_t> &tasks) override;
    StorageResult save(const QList<Task_t> &tasks) override;

private:
    QJsonArray toJson(const QList<Task_t> &tasks) const;
    QList<Task_t> fromJson(const QJsonArray &array) const;

    QFile m_file;
};
