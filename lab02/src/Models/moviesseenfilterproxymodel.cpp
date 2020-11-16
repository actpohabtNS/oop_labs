#include "moviesseenfilterproxymodel.h"

#include <QDebug>

MoviesSeenFilterProxyModel::MoviesSeenFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool MoviesSeenFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    for (int column = 0; column < sourceModel()->columnCount(); column++) {
        QModelIndex index = sourceModel()->index(sourceRow, column, sourceParent);

        if (sourceModel()->data(index).toString().contains(filterRegExp()))
            return true;
    }

    return false;
}
