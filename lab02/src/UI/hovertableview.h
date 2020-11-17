#ifndef HOVERTABLEVIEW_H
#define HOVERTABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>

class HoverTableView : public QTableView
{
    Q_OBJECT

public:
    HoverTableView(QWidget *parent);
    void mouseMoveEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void hoverIndexChanged(const QModelIndex& item);
    void leaveTableEvent();
};

#endif // HOVERTABLEVIEW_H
