#include "movieToSeeModel.h"

#include <QFile>
#include <QDebug>

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

    return _moviesToSee.size();
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
            const MovieToSee& result = _moviesToSee[row];
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
                    return QString::number(result.length) + " min";
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

bool MovieToSeeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // Removal not implemented
    endRemoveRows();
    return true;
}

void MovieToSeeModel::sort(int column, Qt::SortOrder order)
{
    switch(column) {
            case 0:
                std::sort(_moviesToSee.begin(),_moviesToSee.end(), [order](const MovieToSee& a, const MovieToSee& b) {
                return order == Qt::AscendingOrder ? a.title < b.title : a.title > b.title;
                });
                break;

            case 5:
                std::sort(_moviesToSee.begin(),_moviesToSee.end(), [order](const MovieToSee& a, const MovieToSee& b) {
                return order == Qt::AscendingOrder ? a.added < b.added : a.added > b.added;
                });
                break;

            case 6:
                std::sort(_moviesToSee.begin(),_moviesToSee.end(), [order](const MovieToSee& a, const MovieToSee& b) {
                return order == Qt::AscendingOrder ? a.length < b.length : a.length > b.length;
                });
                break;

        }

    emit dataChanged(index(0,0),index(_moviesToSee.size(),5));
}

QString MovieToSeeModel::toString(int row) const
{
    auto movie = _moviesToSee[_moviesToSee.size() - 1 - row];

    QString str = "";
    str += "Title: " + movie.title + "\n";
    str += "Genre: " + movie.genre + "\n";
    str += "Description: " + movie.description + "\n";
    str += "Length: " + QString::number(movie.length) + " min";

    return str;
}

void MovieToSeeModel::loadFromFile()
{
    loadFromFile(_filepath);
}

void MovieToSeeModel::loadFromFile(const QString &filepath)
{
    MovieToSee movie;

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

        this->insertRow(_moviesToSee.size());
        _moviesToSee.push_back(movie);
    }

    file.close();
}

void MovieToSeeModel::importFromFile(const QString &filepath)
{
    MovieToSee movie;

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

void MovieToSeeModel::addToFile(const MovieToSee &movie) const
{
    addToFile(movie, _filepath);
}

void MovieToSeeModel::addToFile(const MovieToSee &movie, const QString &filepath) const
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

void MovieToSeeModel::flushToFile() const
{
    flushToFile(_filepath);
}

void MovieToSeeModel::flushToFile(const QString &filepath) const
{
    QFile file(filepath);
    file.open(QIODevice::Truncate | QIODevice::WriteOnly);

    if (!file.isOpen()) {
        qDebug() << "addToFile: file can Not be opened!";
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_1);

    for (auto movie : _moviesToSee)
        stream << movie;

    file.close();
}

void MovieToSeeModel::addMovie(const MovieToSee &movie)
{
    this->insertRow(_moviesToSee.size());
    _moviesToSee.push_back(movie);
    addToFile(movie);
}

void MovieToSeeModel::removeMovie(int row)
{
    this->removeRow(row);
    _moviesToSee.erase(_moviesToSee.end() - 1 - row);
    flushToFile();
}

void MovieToSeeModel::editMovie(int row, const MovieToSee &movie)
{
    _moviesToSee[_moviesToSee.size() - 1 - row] = movie;
    flushToFile();
    emit dataChanged(index(row,0),index(row,columnCount()));
}

void MovieToSeeModel::setFilepath(QString path)
{
    _filepath = path;
}

int MovieToSeeModel::titleRow(const QString &title) const
{
    for (int row = 0; row < rowCount(); row++) {
        if (_moviesToSee[row].title.toUpper() == title.toUpper())
             return _moviesToSee.size() - 1 - row;
    }

    return -1;
}

const MovieToSee &MovieToSeeModel::movie(int row) const
{
    return _moviesToSee[_moviesToSee.size() - 1 - row];
}

const std::vector<MovieToSee> &MovieToSeeModel::moviesSeen() const
{
    return _moviesToSee;
}


