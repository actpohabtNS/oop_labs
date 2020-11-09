#ifndef MOVIETOSEE_H
#define MOVIETOSEE_H

#include <QTime>
#include <QDate>
#include <QString>

struct MovieToSee {
    QString title;
    QString genre;
    QString description;
    QDate added;
    QTime length;
};

#endif // MOVIETOSEE_H
