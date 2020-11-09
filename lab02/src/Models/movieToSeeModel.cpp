#include "movieToSeeModel.h"

MovieToSeeModel::MovieToSeeModel(QObject *parent)
    : QAbstractTableModel(parent) {}

QVariant MovieToSeeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                QStringList headers{
                                   "Title",
                                   "Genre",
                                   "Description",
                                   "Added",
                                   "Length",
                                    };
                return headers[section];
            }
        }
    return QVariant();
}

int MovieToSeeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return moviesToSee.size();
}

int MovieToSeeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 5;
}

QVariant MovieToSeeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole) {

            int row = index.row();
            int column = index.column();
            const MovieToSee& result = moviesToSee[row];
            switch(column) {
                case 0:
                    return result.title;
                case 1:
                    return result.genre;
                case 2:
                    return result.description;
                case 3:
                    return result.added.toString(Qt::ISODate);
                case 4:
                    QString qres = "";
                    if (result.length.hour() > 0)
                        qres.append(QString::number(result.length.hour()) + "h");

                    qres.append(QString::number(result.length.minute()) + "m");

                    return qres;
            }
        }

        return QVariant();
}

bool MovieToSeeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // Insertion not implemented
    endInsertRows();
    return true;
}

void MovieToSeeModel::sort(int column, Qt::SortOrder order)
{
    switch(column) {
            case 0:
                std::sort(moviesToSee.begin(),moviesToSee.end(), [order](const MovieToSee& a, const MovieToSee& b) {
                return order == Qt::AscendingOrder ? a.title < b.title : a.title > b.title;
                });
                break;

            case 5:
                std::sort(moviesToSee.begin(),moviesToSee.end(), [order](const MovieToSee& a, const MovieToSee& b) {
                return order == Qt::AscendingOrder ? a.added < b.added : a.added > b.added;
                });
                break;

            case 6:
                std::sort(moviesToSee.begin(),moviesToSee.end(), [order](const MovieToSee& a, const MovieToSee& b) {
                return order == Qt::AscendingOrder ? a.length < b.length : a.length > b.length;
                });
                break;

        }

    emit dataChanged(index(0,0),index(moviesToSee.size(),5));
}

void MovieToSeeModel::addMovie(const MovieToSee &movie)
{
    this->insertRow(moviesToSee.size());
    moviesToSee.push_back(movie);
}


