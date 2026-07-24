#pragma once

#include "TodoStorageInterface.hpp"
#include <QFile>
#include <JsonDocument>

class TodoJsonStorage : public TodoStorageInterface
{
public:
    explicit TodoJsonStorage(const QString &filePath): m_filePath(filePath) {}

    StorageResult load(QList<Task_t> &tasks) override;
    StorageResult save(const QList<Task_t> &tasks) override;

private:
// Save
    QJsonDocument tasksToDocument(const QList<Task_t> &tasks);
    QJsonArray tasksToArray(const QList<Task_t> &tasks);
    QJsonObject arrayToRootObject(const QJsonArray &array);
    QByteArray documentToByteArray(const QJsonDocument &document);

// Load
    StorageError byteArrayToDocument(const QByteArray &byteArray, QJsonDocument &outDocument); // validate json syntax -> parse error
    StorageError documentToRootObject(const QJsonDocument &document, QJsonObject &outObject); // validate root object -> invalid json schema
    StorageError rootObjectToArray(const QJsonObject &rootObject, QJsonArray &outArray); // validate tasks array -> invalid json schema
    StorageError arrayToTasks(const QJsonArray &array, QList<Task_t>& outTasks); // validate task object -> invalid type schema 

// Validation
    StorageError isValidSchema(const QJsonObject &taskObject);

    QString m_filePath;
};
