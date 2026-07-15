#pragma once

#include <QString>

struct Todo
{
    QString uuid;
    QString description;
    bool done;
};

enum TaskRole
{
    uuidRole = Qt::UserRole + 1,
    descriptionRole,
    doneRole
};

struct Task_t
{
    QString uuid;
    QString description;
    bool done;
};

enum Filter
{
    All,
    Done,
    Todo
};

enum class StorageError
{
    None,
    OpenFailed,
    PermissionDenied,
    InvalidFormat,
    DiskFull,
    Unknown
} struct StorageResult
{
    StorageError error;
    QString message;
    bool ok() const
    {
        return error == StorageError::None;
    }
}