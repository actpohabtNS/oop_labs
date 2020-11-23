#include "moviesseenfilterproxymodel.h"

MoviesSeenFilterProxyModel::MoviesSeenFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent), _timeVault{}, _timeLabel {nullptr} {}

MoviesSeenFilterProxyModel::MoviesSeenFilterProxyModel(const TimeVault &timeVault, QLabel *label, QObject *parent)
 : QSortFilterProxyModel(parent), _timeLabel {label}
{
    setTimeVault(timeVault);
}

void MoviesSeenFilterProxyModel::setTimeVault(const TimeVault &timeVault)
{
    _timeVault = TimeVault{timeVault.hours(), timeVault.minutes()};
}

void MoviesSeenFilterProxyModel::setTimeDisplay(QLabel *label)
{
    _timeLabel = label;
}

void MoviesSeenFilterProxyModel::setFilterRegExp(const QRegExp &regExp)
{
    _timeVault.nullify();
    _timeLabel->setText(_timeVault.toString());

    QSortFilterProxyModel::setFilterRegExp(regExp);
}

void MoviesSeenFilterProxyModel::invalidate()
{
    _timeVault.nullify();
    _timeLabel->setText(_timeVault.toString());

    QSortFilterProxyModel::invalidate();
}

bool MoviesSeenFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    bool accepts = false;

    for (int column = 0; column < sourceModel()->columnCount(); column++) {
        QModelIndex index = sourceModel()->index(sourceRow, column, sourceParent);

        if (sourceModel()->data(index).toString().contains(filterRegExp())) {
            accepts = true;
            break;
        }
    }

    if (accepts) {
        QModelIndex index = sourceModel()->index(sourceRow, sourceModel()->columnCount() - 1, sourceParent);

        quint32 mins = sourceModel()->data(index).toString().split(" ")[0].toUInt();

        _timeVault += TimeVault{mins / 60, static_cast<quint8>(mins % 60)};

        _timeLabel->setText(_timeVault.toString());
    }

    return accepts;
}
