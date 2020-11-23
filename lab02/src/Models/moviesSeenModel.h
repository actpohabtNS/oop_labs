#ifndef MOVIESSEENMODEL_H
#define MOVIESSEENMODEL_H

#include "../dataDef/movieSeen.h"

#include <QAbstractTableModel>
#include <QFile>
#include <vector>

class MoviesSeenModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MoviesSeenModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    void sort(int column, Qt::SortOrder order) override;


    QString toString(int row) const;

    void loadFromFile();
    void loadFromFile(const QString& filepath);

    void importFromFile(const QString& filepath);

    void addToFile(const MovieSeen& movie) const;
    void addToFile(const MovieSeen& movie, const QString& filepath) const;

    void flushToFile() const;
    void flushToFile(const QString& filepath) const;

    void addMovie(const MovieSeen& movie);
    void removeMovie(int row);

    void setFilepath(QString path);

    bool containsTitle(const QString& title) const;

    const MovieSeen& movie(int row) const;
    const std::vector<MovieSeen>& moviesSeen() const;

private:
    std::vector<MovieSeen> _moviesSeen;

    QString _filepath;
};

#endif // MOVIESSEENMODEL_H
