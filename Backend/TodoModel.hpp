#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

struct Todo {
    QString uuid;
    QString description;
    bool done;
};

class TodoModel : public QAbstractListModel
{
    Q_OBJECT

public:
};