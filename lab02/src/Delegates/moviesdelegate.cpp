#include "moviesdelegate.h"

#include <QApplication>
#include <QPainter>

MoviesDelegate::MoviesDelegate(QObject *parent, MovieTypes type)
    : HoverRowDelegate(parent)
{
    setMovieType(type);
}

void MoviesDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    HoverRowDelegate::paint(painter, option, index);

    if (index.row() == _hoveredRow) {
        QRect r = option.rect;//getting the rect of the cell
        int x,y, fontSize;
        fontSize = 18;

        QString text;

        if (index.column() == _moveColumn) {
            painter->setPen("#7a7d7d");
            text = "⇐";

            if (_hoveredColumn == _moveColumn) {
                 QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));

                 painter->setPen("#b3b3b3");
            }
        }

        if (index.column() == _editColumn) {
            painter->setPen("#7a7d7d");
            text = "⛭";
            fontSize = 14;

            if (_hoveredColumn == _editColumn) {
                 QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));

                 painter->setPen("#b3b3b3");
            }
        }

        if (index.column() == _deleteColumn) {
            painter->setPen("#7a7d7d");
            text = "×";

            if (_hoveredColumn == _deleteColumn) {
                 QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));

                 painter->setPen("#ff0000");
            }
        }

        x = r.left() + r.width()/2 - fontSize/2;//the X coordinate
        y = r.top() + r.height()/2 + fontSize/2;//the Y coordinate

        painter->setFont({"Roboto", fontSize});
        painter->drawText(x, y, text);

        QStyledItemDelegate::paint(painter, option, index);
    }

    if (_hoveredColumn != _moveColumn &&
            _hoveredColumn != _editColumn &&
            _hoveredColumn != _deleteColumn)
        QApplication::restoreOverrideCursor();

}

void MoviesDelegate::setMovieType(MovieTypes type)
{
    switch (type) {
        case MovieTypes::movieSeen:
            _moveColumn = -1;
            _editColumn = 0;
            _deleteColumn = 7;
        break;

        case MovieTypes::movieToSee:
            _moveColumn = 0;
            _editColumn = 1;
            _deleteColumn = 6;
        break;

        case MovieTypes::unknown:
        default:
        _moveColumn = -1;
        _editColumn = -1;
        _deleteColumn = -1;
    }
}
