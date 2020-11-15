#ifndef MOVIESEENMODEL_H
#define MOVIESEENMODEL_H

#include "../dataDef/movieSeen.h"

#include <QAbstractTableModel>
#include <QFile>
#include <vector>

class MovieSeenModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MovieSeenModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void sort(int column, Qt::SortOrder order) override;


    void loadData();

    void addToFile(const MovieSeen& movie) const;

    void addMovie(const MovieSeen& movie);

    void setFilepath(QString path);

private:
    std::vector<MovieSeen> _moviesSeen;

    QString _filepath;

};

#endif // MOVIESEENMODEL_H
