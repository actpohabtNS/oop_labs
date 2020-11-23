#include "movieToSee.h"


QDataStream &operator<<(QDataStream &str, const MovieToSee &movie)
{
    str << movie.title
        << movie.genre
        << movie.description
        << movie.added
        << movie.length;

    return str;
}

QDataStream &operator>>(QDataStream &str, MovieToSee &movie)
{
    str >> movie.title
        >> movie.genre
        >> movie.description
        >> movie.added
        >> movie.length;

    return str;
}
