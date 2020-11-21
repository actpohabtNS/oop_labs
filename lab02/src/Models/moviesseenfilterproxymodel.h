#ifndef MOVIESSEENFILTERPROXYMODEL_H
#define MOVIESSEENFILTERPROXYMODEL_H

#include "../dataDef/timevault.h"

#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QLabel>

class MoviesSeenFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MoviesSeenFilterProxyModel(QObject *parent = nullptr);
    MoviesSeenFilterProxyModel(const TimeVault& timeVault, QLabel *label, QObject *parent = nullptr);

    void setTimeVault(const TimeVault& timeVault);
    void setTimeDisplay(QLabel *label);

public slots:
    void setFilterRegExp(const QRegExp &regExp);

protected:
    mutable TimeVault _timeVault;
    QLabel *_timeLabel;

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // MOVIESSEENFILTERPROXYMODEL_H
