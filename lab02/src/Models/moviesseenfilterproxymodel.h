#ifndef MOVIESSEENFILTERPROXYMODEL_H
#define MOVIESSEENFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MoviesSeenFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MoviesSeenFilterProxyModel(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // MOVIESSEENFILTERPROXYMODEL_H
