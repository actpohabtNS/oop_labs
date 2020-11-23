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

    bool removeRows(int row, int count, const QModelIndex& parent);

    void sort(int column, Qt::SortOrder order) override;


    void toClipboard(int row) const;

    void loadData();

    void addToFile(const MovieSeen& movie) const;

    void flushToFile() const;

    void addMovie(const MovieSeen& movie);

    void removeMovie(int row);

    void setFilepath(QString path);

    const std::vector<MovieSeen>& moviesSeen() const;

private:
    std::vector<MovieSeen> _moviesSeen;

    QString _filepath;
};

#endif // MOVIESSEENMODEL_H
