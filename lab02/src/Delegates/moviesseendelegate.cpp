#include "moviesseendelegate.h"

#include <QApplication>
#include <QPainter>

MoviesSeenDelegate::MoviesSeenDelegate(QObject *parent)
    : HoverRowDelegate(parent) {}

void MoviesSeenDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    HoverRowDelegate::paint(painter, option, index);

    if (index.row() == _hoveredRow) {
        QRect r = option.rect;//getting the rect of the cell
        int x,y, fontSize;
        fontSize = 18;
        x = r.left() + r.width()/2 - fontSize/2;//the X coordinate
        y = r.top() + r.height()/2 + fontSize/2;//the Y coordinate

        painter->setFont({"Roboto", fontSize});

        if (index.column() == 0) {
            painter->setPen("#7a7d7d");

            if (_hoveredColumn == 0) {
                 QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));

                 painter->setPen("#b3b3b3");
            }

            painter->drawText(x, y, "⎘");
        }

        if (index.column() == 7) {
            painter->setPen("#7a7d7d");

            if (_hoveredColumn == 7) {
                 QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));

                 painter->setPen("#ff0000");
            }

            painter->drawText(x, y, "×");
        }

        QStyledItemDelegate::paint(painter, option, index);
    }

    if (_hoveredColumn != 0 && _hoveredColumn != 7)
        QApplication::restoreOverrideCursor();

}
