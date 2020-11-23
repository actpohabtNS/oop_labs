#include "moviesfilterproxymodel.h"

MoviesFilterProxyModel::MoviesFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent), _timeVault{}, _timeLabel {nullptr} {}

MoviesFilterProxyModel::MoviesFilterProxyModel(const TimeVault &timeVault, QLabel *label, QObject *parent)
 : QSortFilterProxyModel(parent), _timeLabel {label}
{
    setTimeVault(timeVault);
}

void MoviesFilterProxyModel::setTimeVault(const TimeVault &timeVault)
{
    _timeVault = TimeVault{timeVault.hours(), timeVault.minutes()};
}

void MoviesFilterProxyModel::setTimeDisplay(QLabel *label)
{
    _timeLabel = label;
}

void MoviesFilterProxyModel::setFilterRegExp(const QRegExp &regExp)
{
    _timeVault.nullify();
    _timeLabel->setText(_timeVault.toString());

    QSortFilterProxyModel::setFilterRegExp(regExp);
}

void MoviesFilterProxyModel::invalidate()
{
    _timeVault.nullify();
    _timeLabel->setText(_timeVault.toString());

    QSortFilterProxyModel::invalidate();
}

bool MoviesFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
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
