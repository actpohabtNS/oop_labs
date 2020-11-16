#include "movieSeen.h"

QDataStream & operator<<(QDataStream & str, const MovieSeen & movie)
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
    str >> movie.title
        >> movie.rate
        >> movie.genre
        >> movie.description
        >> movie.group
        >> movie.added
        >> movie.length;

    return str;
}
