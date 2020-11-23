#include "hovertableview.h"

#include <QStandardItem>
#include <QDebug>

HoverTableView::HoverTableView(QWidget *parent)
    : QTableView(parent)
{
    setMouseTracking(true);
}

void HoverTableView::mouseMoveEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    emit hoverIndexChanged(index);
    viewport()->update();
}

void HoverTableView::leaveEvent(QEvent*)
{
    emit leaveTableEvent();
    viewport()->update();
}
