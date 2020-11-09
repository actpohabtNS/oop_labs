#ifndef MOVIETOSEE_H
#define MOVIETOSEE_H

#include <QTime>
#include <QDate>
#include <QString>

struct MovieToSee {
    QString title;
    QString genre;
    QString description;
    QTime length;
    QDate added;
};

#endif // MOVIETOSEE_H
