#include "moviesSeenModel.h"

#include <QDataStream>
#include <QDebug>
#include <string>
#include <QFile>

MoviesSeenModel::MoviesSeenModel(QObject *parent)
    : QAbstractTableModel(parent) {}

QVariant MoviesSeenModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                QStringList headers{
                                   "",
                                   "Title",
                                   "Rate",
                                   "Genre",
                                   "Description",
                                   "Group",
                                   "Added",
                                   "",
                                   "Length",
                                    };
                return headers[section];
            }
        }
    return QVariant();
}

int MoviesSeenModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return _moviesSeen.size();
}

int MoviesSeenModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 9;
}

QVariant MoviesSeenModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole) {

            int row = index.row();
            int column = index.column();
            const MovieSeen& result = _moviesSeen[_moviesSeen.size() - 1 - row]; //movies order is reversed in _moviesSeen due to higher performance in writing to file
            switch(column) {
                case 0:
                    return "";
                case 1:
                    return result.title;
                case 2:
                    return QString::number(result.rate);
                case 3:
                    return result.genre;
                case 4:
                    return result.description;
                case 5:
                    return result.group;
                case 6:
                    return result.added.toString(Qt::ISODate);
                case 7:
                    return "";
                case 8:
                    QString qres = "";
                    qres.append(QString::number(result.length.hour() * 60 + result.length.minute()) + " min");

                    return qres;
            }
        }

        return QVariant();
}

bool MoviesSeenModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // Insertion not implemented
    endInsertRows();
    return true;
}

void MoviesSeenModel::sort(int column, Qt::SortOrder order)
{
    switch(column) {
            case 1:
                std::sort(_moviesSeen.begin(),_moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.title > b.title : a.title < b.title;
                });
                break;
            case 2:
                std::sort(_moviesSeen.begin(),_moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.rate > b.rate : a.rate < b.rate;
                });
                break;

            case 6:
                std::sort(_moviesSeen.begin(),_moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.added > b.added : a.added < b.added;
                });
                break;

            case 8:
                std::sort(_moviesSeen.begin(),_moviesSeen.end(), [order](const MovieSeen& a, const MovieSeen& b) {
                return order == Qt::AscendingOrder ? a.length > b.length : a.length < b.length;
                });
                break;

        }

    emit dataChanged(index(0,0),index(_moviesSeen.size(),columnCount()));
}

void MoviesSeenModel::loadData()
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

void MoviesSeenModel::addToFile(const MovieSeen &movie) const
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

void MoviesSeenModel::addMovie(const MovieSeen &movie)
{
    this->insertRow(_moviesSeen.size());
    _moviesSeen.push_back(movie);
    addToFile(movie);
}

void MoviesSeenModel::setFilepath(QString path)
{
    _filepath = path;
}

const std::vector<MovieSeen> &MoviesSeenModel::moviesSeen() const
{
    return _moviesSeen;
}
