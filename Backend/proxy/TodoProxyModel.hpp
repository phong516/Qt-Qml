#pragma once
#include <QSortFilterProxyModel>
#include "types/TodoTypes.hpp"

class TodoProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TodoProxyModel(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

    bool setFilter(Filter filter);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    Filter m_filter{All};
};