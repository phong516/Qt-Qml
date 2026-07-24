#include "TodoJsonStorage.hpp"

StorageResult TodoJsonStorage::load(QList<Task_t> &tasks)
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return StorageResult{StorageError::OpenFailed, file.errorString()};
    }
    QByteArray data = file.readAll();
    if (data.trimmed().isEmpty())
    {
        qDebug() << "File is empty.";
        return StorageResult{StorageError::EmptyFile, "File is empty"};
    }
    StorageError err{StorageError::Unknown};
    QJsonDocument document;
    err = byteArrayToDocument(data, document);
    if (err != StorageError::None)
        return StorageResult{err, "Parse error"};

    QJsonObject rootObject;
    err = documentToRootObject(document, rootObject);
    if (err != StorageError::None)
        return StorageResult{err, "Invalid JSON schema"};

    if (isValidSchema(rootObject) != StorageError::None)
        return StorageResult{StorageError::InvalidJsonSchema, "Invalid JSON schema"};

    QJsonArray array;
    err = rootObjectToArray(rootObject, array);
    if (err != StorageError::None)
        return StorageResult{err, "Invalid tasks array"};

    err = arrayToTasks(array, tasks);
    if (err != StorageError::None)
        return StorageResult{err, "Invalid task format"};
    return StorageResult{StorageError::None, ""};
}

StorageResult TodoJsonStorage::save(const QList<Task_t> &tasks)
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return StorageResult{StorageError::OpenFailed, file.errorString()};
    }
    QJsonDocument document = tasksToDocument(tasks);
    QByteArray data = documentToByteArray(document);
    qint64 written = file.write(data);
    if (written == -1)
    {
        qDebug() << "Failed to write file:" << file.errorString();
        return StorageResult{StorageError::WriteFailed, file.errorString()};
    }
    return StorageResult{StorageError::None, ""};
}

QJsonDocument TodoJsonStorage::tasksToDocument(const QList<Task_t> &tasks)
{
    QJsonArray array = tasksToArray(tasks);
    QJsonObject rootObject = arrayToRootObject(array);
    return QJsonDocument(rootObject);
}

QJsonArray TodoJsonStorage::tasksToArray(const QList<Task_t> &tasks)
{
    QJsonArray array;
    for (const Task_t &task : tasks)
    {
        QJsonObject taskObject;
        taskObject["uuid"] = task.uuid;
        taskObject["description"] = task.description;
        taskObject["done"] = task.done;
        array.append(taskObject);
    }
    return array;
}

QJsonObject TodoJsonStorage::arrayToRootObject(const QJsonArray &array)
{
    QJsonObject rootObject;
    rootObject["tasks"] = array;
    return rootObject;
}

QByteArray TodoJsonStorage::documentToByteArray(const QJsonDocument &document)
{
    return document.toJson(QJsonDocument::Indented);
}

StorageError TodoJsonStorage::byteArrayToDocument(const QByteArray &byteArray, QJsonDocument &outDocument)
{
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(byteArray, &parseError);
    if (parseError.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON parse error:" << parseError.errorString();
        return StorageError::ParseError;
    }
    outDocument = document;
    return StorageError::None;
}

StorageError TodoJsonStorage::documentToRootObject(const QJsonDocument &document, QJsonObject &outObject)
{
    if (!document.isObject())
    {
        qDebug() << "Invalid JSON format: root is not an object.";
        return StorageError::InvalidJsonSchema;
    }
    outObject = document.object();
    return StorageError::None;
}

StorageError TodoJsonStorage::rootObjectToArray(const QJsonObject &rootObject, QJsonArray &outArray)
{
    if (!rootObject.contains("tasks") || !rootObject["tasks"].isArray())
    {
        qDebug() << "Invalid JSON format: 'tasks' key is missing or not an array.";
        return StorageError::InvalidJsonSchema;
    }
    outArray = rootObject["tasks"].toArray();
    return StorageError::None;
}

StorageError TodoJsonStorage::arrayToTasks(const QJsonArray &array, QList<Task_t> &outTasks)
{
    for (const QJsonValue &taskValue : array)
    {
        if (!taskValue.isObject())
        {
            qDebug() << "Invalid JSON format: task is not an object.";
            return StorageError::InvalidJsonSchema;
        }
        Task_t task;
        QJsonObject taskObj = taskValue.toObject();
        task.uuid = taskObj["uuid"].toString();
        task.description = taskObj["description"].toString();
        task.done = taskObj["done"].toBool();
        outTasks.append(task);
    }
    return StorageError::None;
}

StorageError TodoJsonStorage::isValidSchema(const QJsonObject &taskObject)
{
    if (!taskObject.contains("tasks") || !taskObject["tasks"].isArray())
    {
        return StorageError::InvalidJsonSchema;
    }
    for (const QJsonValue &taskValue : taskObject["tasks"].toArray())
    {
        if (!taskValue.isObject())
        {
            return StorageError::InvalidJsonSchema;
        }
        QJsonObject taskObj = taskValue.toObject();
        if (!taskObj.contains("uuid") || !taskObj["uuid"].isString() ||
            !taskObj.contains("description") || !taskObj["description"].isString() ||
            !taskObj.contains("done") || !taskObj["done"].isBool())
        {
            return StorageError::InvalidTypeSchema;
        }
    }
    return StorageError::None;
}