#ifndef MOVIESFILTERPROXYMODEL_H
#define MOVIESFILTERPROXYMODEL_H

#include "../dataDef/timevault.h"

#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QLabel>

class MoviesFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MoviesFilterProxyModel(QObject *parent = nullptr);
    MoviesFilterProxyModel(const TimeVault& timeVault, QLabel *label, QObject *parent = nullptr);

    void setTimeVault(const TimeVault& timeVault);
    void setTimeDisplay(QLabel *label);


public slots:
    void setFilterRegExp(const QRegExp &regExp);
    void invalidate();

protected:
    mutable TimeVault _timeVault;
    QLabel *_timeLabel;

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // MOVIESFILTERPROXYMODEL_H
