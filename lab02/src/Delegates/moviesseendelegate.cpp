#include "moviesseendelegate.h"

#include <QApplication>

MoviesSeenDelegate::MoviesSeenDelegate(QObject *parent)
    : HoverRowDelegate(parent) {}

void MoviesSeenDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    HoverRowDelegate::paint(painter, option, index);

    if (index.row() == _hoveredRow && index.column() == 0) {
        QStyleOptionButton button;
             QRect r = option.rect;//getting the rect of the cell
             int x,y,w,h;
             w = 35;
             h = 35;
             x = r.left() + r.width() - w/2;//the X coordinate
             y = r.top() + r.height()/2 - h/2;//the Y coordinate
             button.rect = QRect(x,y,w,h);
             button.text = "copy";//no text . since if text will be given then it will push the icon to left side based on the coordinates .
             button.state = QStyle::State_Enabled;
             QApplication::style()->drawControl( QStyle::CE_PushButtonLabel, &button, painter);
    }
}
