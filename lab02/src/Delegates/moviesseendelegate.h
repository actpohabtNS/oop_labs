#ifndef MOVIESSEENDELEGATE_H
#define MOVIESSEENDELEGATE_H

#include "hoverrowdelegate.h"

class MoviesSeenDelegate : public HoverRowDelegate
{
    Q_OBJECT

public:
    MoviesSeenDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MOVIESSEENDELEGATE_H
