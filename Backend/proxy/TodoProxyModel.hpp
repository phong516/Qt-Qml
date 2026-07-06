#pragma once
#include <QSortFilterProxyModel>

class TodoProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TodoProxyModel(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

    enum Filter
    {
        All,
        Done,
        Todo
    };
    bool setFilter(Filter filter);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    Filter m_filter{All};
};