#include "moviesSeenModel.h"

#include <QDataStream>
#include <QDebug>
#include <string>
#include <QFile>
#include <QClipboard>
#include <QGuiApplication>

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
                    return QString::number(result.length) + " min";
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

bool MoviesSeenModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // Removal not implemented
    endRemoveRows();
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

QString MoviesSeenModel::toString(int row) const
{
    auto movie = _moviesSeen[_moviesSeen.size() - 1 - row];

    QString str = "";
    str += "Title: " + movie.title + "\n";
    str += "Rate: " + QString::number(movie.rate) + "\n";
    str += "Genre: " + movie.genre + "\n";
    str += "Description: " + movie.description + "\n";
    str += "Group: " + movie.group + "\n";
    str += "Length: " + QString::number(movie.length) + " min";

    return str;
}

void MoviesSeenModel::loadFromFile()
{
    loadFromFile(_filepath);
}

void MoviesSeenModel::loadFromFile(const QString &filepath)
{
    MovieSeen movie;

    QFile file(filepath);
    file.open(QIODevice::ReadOnly);

    if (!file.isOpen()) {
        qDebug() << "loadData: file can Not be opened!";
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_1);

    while(!stream.atEnd()) {
        stream >> movie;

        if (titleRow(movie.title) != -1)
            continue;

        this->insertRow(_moviesSeen.size());
        _moviesSeen.push_back(movie);
    }

    file.close();
}

void MoviesSeenModel::importFromFile(const QString &filepath)
{
    MovieSeen movie;

    QFile file(filepath);
    file.open(QIODevice::ReadOnly);

    if (!file.isOpen()) {
        qDebug() << "loadData: file can Not be opened!";
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_1);

    while(!stream.atEnd()) {
        stream >> movie;

        if (titleRow(movie.title) != -1)
            continue;

        movie.added = QDate::currentDate();
        addMovie(movie);
    }

    file.close();
}

void MoviesSeenModel::addToFile(const MovieSeen &movie) const
{
    addToFile(movie, _filepath);
}

void MoviesSeenModel::addToFile(const MovieSeen &movie, const QString &filepath) const
{
    QFile file(filepath);
    file.open(QIODevice::Append | QIODevice::WriteOnly);

    if (!file.isOpen()) {
        qDebug() << "addToFile: file can Not be opened!";
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_1);

    stream << movie;

    file.close();
}

void MoviesSeenModel::flushToFile() const
{
    flushToFile(_filepath);
}

void MoviesSeenModel::flushToFile(const QString &filepath) const
{
    QFile file(filepath);
    file.open(QIODevice::Truncate | QIODevice::WriteOnly);

    if (!file.isOpen()) {
        qDebug() << "addToFile: file can Not be opened!";
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_1);

    for (auto movie : _moviesSeen)
        stream << movie;

    file.close();
}

void MoviesSeenModel::addMovie(const MovieSeen &movie)
{
    this->insertRow(_moviesSeen.size());
    _moviesSeen.push_back(movie);
    addToFile(movie);
}

void MoviesSeenModel::removeMovie(int row)
{
    this->removeRow(row);
    _moviesSeen.erase(_moviesSeen.end() - 1 - row);
    flushToFile();
}

void MoviesSeenModel::editMovie(int row, const MovieSeen &movie)
{
    _moviesSeen[_moviesSeen.size() - 1 - row] = movie;
    flushToFile();
    emit dataChanged(index(row,0),index(row,columnCount()));
}

void MoviesSeenModel::setFilepath(QString path)
{
    _filepath = path;
}

int MoviesSeenModel::titleRow(const QString& title) const
{
    for (int row = 0; row < rowCount(); row++) {
        if (_moviesSeen[row].title.toUpper() == title.toUpper())
             return _moviesSeen.size() - 1 - row;
    }

    return -1;
}

const MovieSeen &MoviesSeenModel::movie(int row) const
{
    return _moviesSeen[_moviesSeen.size() - 1 - row];
}

const std::vector<MovieSeen> &MoviesSeenModel::moviesSeen() const
{
    return _moviesSeen;
}
