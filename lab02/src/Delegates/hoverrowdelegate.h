#ifndef HOVERROWDELEGATE_H
#define HOVERROWDELEGATE_H

#include <QStyledItemDelegate>

class HoverRowDelegate : public QStyledItemDelegate
{
    Q_OBJECT

protected:
    int _hovered_row;

public:
    HoverRowDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
    void onHoverIndexChanged(const QModelIndex& item);
    void onLeaveTableEvent();
};

#endif // HOVERROWDELEGATE_H
