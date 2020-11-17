#include "hoverrowdelegate.h"

#include <QPainter>

HoverRowDelegate::HoverRowDelegate(QObject *parent)
    : QStyledItemDelegate{parent}, _hovered_row{-1} {}

void HoverRowDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    if(index.row() == _hovered_row) {
        opt.state |= QStyle::State_MouseOver;
        painter->fillRect(option.rect, QBrush{"#4f4f50"});
    } else {
        opt.state &= ~QStyle::State_MouseOver;
    }

    QStyledItemDelegate::paint(painter, opt, index);
}

void HoverRowDelegate::onHoverIndexChanged(const QModelIndex &item)
{
    _hovered_row = item.row();
}

void HoverRowDelegate::onLeaveTableEvent()
{
    _hovered_row = -1;
}
