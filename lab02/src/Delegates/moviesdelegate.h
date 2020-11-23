#ifndef MOVIESDELEGATE_H
#define MOVIESDELEGATE_H

#include "hoverrowdelegate.h"
#include "../dataDef/movieTypes.h"

class MoviesDelegate : public HoverRowDelegate
{
    Q_OBJECT

protected:
    int _moveColumn;
    int _copyColumn;
    int _deleteColumn;

public:
    MoviesDelegate(QObject *parent = nullptr, MovieTypes type = MovieTypes::unknown);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setMovieType(MovieTypes type);
};

#endif // MOVIESDELEGATE_H
