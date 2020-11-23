#ifndef HOVERROWDELEGATE_H
#define HOVERROWDELEGATE_H

#include <QStyledItemDelegate>
#include <QColor>

class HoverRowDelegate : public QStyledItemDelegate
{
    Q_OBJECT

protected:
    int _hoveredRow;
    int _hoveredColumn;
    QColor _hoverColor;

public:
    HoverRowDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setHoverColor(const QColor& color);

public slots:
    void onHoverIndexChanged(const QModelIndex& item);
    void onLeaveTableEvent();
};

#endif // HOVERROWDELEGATE_H
