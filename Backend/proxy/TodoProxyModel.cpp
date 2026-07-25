#include "TodoProxyModel.hpp"

bool TodoProxyModel::setFilter(Filter filter)
{
    m_filter = filter;
    invalidateRowsFilter();
    return true;
}

bool TodoProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    bool isDone = sourceModel()->data(index, doneRole).toBool();
    switch (m_filter) 
    {
        case Filter::All:
            return true;
        case Filter::Done:
            return isDone;
        case Filter::Todo:
            return !isDone;
    }
    return false;
}