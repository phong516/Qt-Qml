#pragma once
#include <QSortFilterProxyModel>

class TodoFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TodoFilter(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

    enum Filter
    {
        All,
        Done,
        Todo
    };
    Q_ENUM(Filter)
    bool setFilter(Filter filter);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    Filter m_filter{All};
};