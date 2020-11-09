#include "movieSeenModel.h"

MovieSeenModel::MovieSeenModel(QObject *parent)
    : QAbstractTableModel(parent) {}

QVariant MovieSeenModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                QStringList headers{
                                   "Title",
                                   "Rate",
                                   "Genre",
                                   "Description",
                                   "Group",
                                   "Added",
                                   "Length",
                                    };
                return headers[section];
            }
        }
    return QVariant();
}

int MovieSeenModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return moviesSeen.size();
}

int MovieSeenModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 7;
}

QVariant MovieSeenModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole) {

            int row = index.row();
            int column = index.column();
            const MovieSeen& result = moviesSeen[row];
            switch(column) {
                case 0:
                    return result.title;
                case 1:
                    return QString::number(result.rate);
                case 2:
                    return result.genre;
                case 3:
                    return result.description;
                case 4:
                    return result.group;
                case 5:
                    return result.added.toString(Qt::ISODate);
                case 6:
                    QString qres = "";
                    if (result.length.hour() > 0)
                        qres.append(QString::number(result.length.hour()) + "h");

                    qres.append(QString::number(result.length.minute()) + "m");

                    return qres;
            }
        }

        return QVariant();
}

bool MovieSeenModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // Insertion not implemented
    endInsertRows();
    return true;
}

void MovieSeenModel::sort(int column, Qt::SortOrder order)
{
    switch(column) {
            case 0:
                std::sort(moviesSeen.begin(),moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.title < b.title : a.title > b.title;
                });
                break;
            case 1:
                std::sort(moviesSeen.begin(),moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.rate < b.rate : a.rate > b.rate;
                });
                break;

            case 5:
                std::sort(moviesSeen.begin(),moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.added < b.added : a.added > b.added;
                });
                break;

            case 6:
                std::sort(moviesSeen.begin(),moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.length < b.length : a.length > b.length;
                });
                break;

        }

    emit dataChanged(index(0,0),index(moviesSeen.size(),7));
}

void MovieSeenModel::addMovie(const MovieSeen &movie)
{
    this->insertRow(moviesSeen.size());
    moviesSeen.push_back(movie);
}


