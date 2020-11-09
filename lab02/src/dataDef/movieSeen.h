#ifndef MOVIESEEN_H
#define MOVIESEEN_H

#include <QTime>
#include <QDate>
#include <QString>

struct MovieSeen {
    QString title;
    char rate;
    QString genre;
    QString description;
    QString group;
    QDate added;
    QTime length;
};

#endif // MOVIESEEN_H
