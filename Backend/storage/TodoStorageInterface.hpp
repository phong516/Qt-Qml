#pragma once

#include "types/TodoTypes.hpp"
#include <QList>

class TodoStorageInterface
{
public:
    virtual ~TodoStorageInterface() = default;

    virtual StorageResult load(QList<Task_t> &tasks) = 0;

    virtual StorageResult save(const QList<Task_t> &tasks) = 0;
};
