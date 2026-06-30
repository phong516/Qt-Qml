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

class TodoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(BackendModel);

public:
    explicit TodoModel(QObject * parent = nullptr): QAbstractListModel(parent) {}
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = doneRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool addTask(const Task_t& task);
    bool removeTask(const QString& uuid);
    bool setDone(const QString& uuid, bool done);
    bool setFilter(const QString& uuid, bool filter);

private:
    QList<Task_t> m_data{};
};