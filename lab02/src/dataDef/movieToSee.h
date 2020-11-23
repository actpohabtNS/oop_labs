#ifndef MOVIETOSEE_H
#define MOVIETOSEE_H

#include <QDate>
#include <QString>
#include <QDataStream>

class MovieToSee {
public:
    QString title;
    QString genre;
    QString description;
    QDate added;
    quint16 length;
};

QDataStream & operator<<(QDataStream & str, const MovieToSee & movie);
QDataStream & operator>>(QDataStream & str, MovieToSee & movie);

#endif // MOVIETOSEE_H
