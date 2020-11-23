#ifndef MOVIESTOSEEMODEL_H
#define MOVIESTOSEEMODEL_H

#include "../dataDef/movieToSee.h"

#include <QAbstractTableModel>
#include <vector>

class MoviesToSeeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MoviesToSeeModel(QObject *parent = nullptr);

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

    void addToFile(const MovieToSee& movie) const;
    void addToFile(const MovieToSee& movie, const QString& filepath) const;

    void flushToFile() const;
    void flushToFile(const QString& filepath) const;

    void addMovie(const MovieToSee& movie);
    void removeMovie(int row);
    void editMovie(int row, const MovieToSee& movie);

    void setFilepath(QString path);

    int titleRow(const QString& title) const;

    const MovieToSee& movie(int row) const;
    const std::vector<MovieToSee>& moviesSeen() const;

private:
    std::vector<MovieToSee> _moviesToSee;

    QString _filepath;
};

#endif // MOVIESTOSEEMODEL_H
