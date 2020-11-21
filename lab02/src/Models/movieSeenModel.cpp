#include "movieSeenModel.h"

#include <QDataStream>
#include <QDebug>
#include <string>
#include <QFile>

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

    return _moviesSeen.size();
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
            const MovieSeen& result = _moviesSeen[_moviesSeen.size() - 1 - row]; //movies order is reversed in _moviesSeen due to higher performance in writing to file
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
                    qres.append(QString::number(result.length.hour() * 60 + result.length.minute()) + " min");

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
                std::sort(_moviesSeen.begin(),_moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.title < b.title : a.title > b.title;
                });
                break;
            case 1:
                std::sort(_moviesSeen.begin(),_moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.rate < b.rate : a.rate > b.rate;
                });
                break;

            case 5:
                std::sort(_moviesSeen.begin(),_moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.added < b.added : a.added > b.added;
                });
                break;

            case 6:
                std::sort(_moviesSeen.begin(),_moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.length < b.length : a.length > b.length;
                });
                break;

        }

    emit dataChanged(index(0,0),index(_moviesSeen.size(),7));
}

void MovieSeenModel::loadData()
{
    MovieSeen movie;MovieSeen movie1;

    QFile file(_filepath);
    file.open(QIODevice::ReadOnly);

    if (!file.isOpen()) {
        qDebug() << "loadData: file can Not be opened!";
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_1);

    while(!stream.atEnd()) {
        QString rate;

        stream >> movie;

        this->insertRow(_moviesSeen.size());
        _moviesSeen.push_back(movie);
    }

    file.close();
}

void MovieSeenModel::addToFile(const MovieSeen &movie) const
{
    QFile file(_filepath);
    file.open(QIODevice::Append | QIODevice::WriteOnly);

    if (!file.isOpen()) {
        qDebug() << "addToFile: file can Not be opened!";
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_1);

    stream << movie.title
        << movie.rate
        << movie.genre
        << movie.description
        << movie.group
        << movie.added
        << movie.length;

    file.close();
}

void MovieSeenModel::addMovie(const MovieSeen &movie)
{
    this->insertRow(_moviesSeen.size());
    _moviesSeen.push_back(movie);
    addToFile(movie);
}

void MovieSeenModel::setFilepath(QString path)
{
    _filepath = path;
}

const std::vector<MovieSeen> &MovieSeenModel::moviesSeen() const
{
    return _moviesSeen;
}
