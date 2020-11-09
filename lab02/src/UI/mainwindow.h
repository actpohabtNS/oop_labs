#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Models/movieSeenModel.h"
#include "../Models/movieToSeeModel.h"

#include <memory>

#include <QMainWindow>
#include <QTableView>

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

private:
    Ui::MainWindow *ui;
    std::shared_ptr<MovieSeenModel> _movieSeenModel;
    std::shared_ptr<MovieToSeeModel> _movieToSeeModel;

    void _stretchTabs();
    void _setRelativeTabsHeight(float percent);

    void _setupMovieSeenTable();
    void _setTableColumnWidths(QTableView* table, std::vector<int> proportions);

};
#endif // MAINWINDOW_H
