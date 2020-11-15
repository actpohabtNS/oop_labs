#include "movieSeen.h"

QDataStream & operator<<(QDataStream & str, const MovieSeen & movie) // this overload is NOT working somehow!!
{
    str << movie.title
        << movie.rate
        << movie.genre
        << movie.description
        << movie.group
        << movie.added
        << movie.length;

    return str;
}

QDataStream & operator>>(QDataStream & str, MovieSeen & movie)
{
    QString rate;

    str >> movie.title
        >> rate
        >> movie.genre
        >> movie.description
        >> movie.group
        >> movie.added
        >> movie.length;

    movie.rate = rate.toShort();

    return str;
}
