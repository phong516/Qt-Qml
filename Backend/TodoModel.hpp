#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QtQml>

struct Todo {
    QString uuid;
    QString description;
    bool done;
};

class TodoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(TodoModel);

public:
    explicit TodoModel(QObject * parent = nullptr): QAbstractListModel(parent) {}
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool addTask(const QString& description);
    Q_INVOKABLE bool removeTask(const QString& uuid);
    Q_INVOKABLE bool setDone(const QString& uuid, bool done);
    Q_INVOKABLE bool setFilter(const QString& uuid, bool filter);

    enum TaskRole
    {
        uuidRole = Qt::UserRole + 1,
        descriptionRole,
        doneRole
    };
    struct Task_t {
        QString uuid;
        QString description;
        bool done;
    }; 

private:
    QList<Task_t> m_data{};
};