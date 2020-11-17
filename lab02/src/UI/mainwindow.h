#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Models/movieSeenModel.h"
#include "../Models/movieToSeeModel.h"
#include "../Models/moviesseenfilterproxymodel.h"
#include "../Delegates/hoverrowdelegate.h"
#include "hovertableview.h"

#include <memory>

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showEvent(QShowEvent *ev);
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_btn_addSeen_clicked();

    void on_le_seenTitle_textChanged(const QString &arg1);

    void on_le_seenGenre_textChanged(const QString &arg1);

    void on_le_seenSearch_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    std::shared_ptr<MovieSeenModel> _movieSeenModel;
    std::shared_ptr<MovieToSeeModel> _movieToSeeModel;
    MoviesSeenFilterProxyModel* _moviesSeenFilter;
    HoverRowDelegate* _hoverRowDelegate;

    void _enableButtonIfNotEmpty(QPushButton *button, std::vector<QLineEdit *> lineEdits);
    bool _checkHighlightIsEmpty(std::vector<QLineEdit*> lineEdits, QColor color = {"#cc1616"});
    bool _checkHighlightIsUniqueSeen(QLineEdit* lineEdit, QColor color = {"#cc1616"});
    void _setBorderBottomColor(QLineEdit* lineEdit, QColor color = {"#5b5c5c"});

    void _clearQLineEdits(std::vector<QLineEdit*> lineEdits);
    void _clearSeenMovieInputs();

    void _stretchTabs();
    void _setRelativeTabsHeight(float percent);

    void _setupMovieSeenTable();
    void _setTableColumnWidths(QTableView* table, const std::vector<int>& proportions);

};
#endif // MAINWINDOW_H
