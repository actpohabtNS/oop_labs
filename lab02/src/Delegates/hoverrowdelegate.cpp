#include "hoverrowdelegate.h"

#include <QPainter>

HoverRowDelegate::HoverRowDelegate(QObject *parent)
    : QStyledItemDelegate{parent}, _hoveredRow{-1}, _hoveredColumn{-1}, _hoverColor("#4f4f50") {}

void HoverRowDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    if(index.row() == _hoveredRow) {
        opt.state |= QStyle::State_MouseOver;
        painter->fillRect(option.rect, QBrush{_hoverColor});
    } else {
        opt.state &= ~QStyle::State_MouseOver;
    }

    QStyledItemDelegate::paint(painter, opt, index);
}

void HoverRowDelegate::setHoverColor(const QColor &color)
{
    _hoverColor = color;
}

void HoverRowDelegate::onHoverIndexChanged(const QModelIndex &item)
{
    _hoveredRow = item.row();
    _hoveredColumn = item.column();
}

void HoverRowDelegate::onLeaveTableEvent()
{
    _hoveredRow = -1;
    _hoveredColumn = -1;
}
