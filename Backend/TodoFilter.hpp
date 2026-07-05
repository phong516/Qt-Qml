#pragma once
#include <QSortFilterProxyModel>

class TodoFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TodoFilter(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}
};