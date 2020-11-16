#ifndef MOVIESEEN_H
#define MOVIESEEN_H

#include <QTime>
#include <QDate>
#include <QString>
#include <QDataStream>

struct MovieSeen {
    QString title;
    quint8 rate;
    QString genre;
    QString description;
    QString group;
    QDate added;
    QTime length;
};

QDataStream & operator<<(QDataStream & str, const MovieSeen & movie);
QDataStream & operator>>(QDataStream & str, MovieSeen & movie);

#endif // MOVIESEEN_H
