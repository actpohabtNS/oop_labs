#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Models/moviesSeenModel.h"
#include "../Models/moviesToSeeModel.h"
#include "../Models/moviesfilterproxymodel.h"
#include "../Delegates/moviesdelegate.h"
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

    void on_tv_seenTable_clicked(const QModelIndex &index);

    void on_btn_seenCopyAll_clicked();

    void on_btn_seenExport_clicked();

    void on_btn_seenImport_clicked();

    void on_moviesTabs_currentChanged(int);

    void on_btn_addToSee_clicked();

    void on_le_toSeeTitle_textChanged(const QString &arg1);

    void on_le_toSeeGenre_textChanged(const QString &arg1);

    void on_le_toSeeSearch_textChanged(const QString &arg1);

    void on_tv_toSeeTable_clicked(const QModelIndex &index);

    void on_btn_toSeeCopyAll_clicked();

    void on_btn_toSeeExport_clicked();

    void on_btn_toSeeImport_clicked();

private:
    Ui::MainWindow *ui;

    MoviesSeenModel* _moviesSeenModel;
    MoviesFilterProxyModel* _moviesSeenFilter;
    MoviesDelegate* _moviesSeenDelegate;

    MoviesToSeeModel* _moviesToSeeModel;
    MoviesFilterProxyModel* _moviesToSeeFilter;
    MoviesDelegate* _moviesToSeeDelegate;

    int _editSeenRow;
    int _editToSeeRow;

    void _setUpSeen();
    void _setUpToSee();

    void _enableButtonIfNotEmpty(QPushButton *button, std::vector<QLineEdit *> lineEdits);
    bool _checkHighlightIsEmpty(std::vector<QLineEdit*> lineEdits, QColor color = {"#cc1616"});
    bool _checkHighlightIsUniqueSeen(QLineEdit* lineEdit, QColor color = {"#cc1616"});
    bool _checkHighlightIsUniqueToSee(QLineEdit* lineEdit, QColor color = {"#cc1616"});
    void _setBorderBottomColor(QLineEdit* lineEdit, QColor color = {"#5b5c5c"});

    void _clearQLineEdits(std::vector<QLineEdit*> lineEdits);
    void _clearSeenMovieInputs();
    void _clearToSeeMovieInputs();

    void _stretchTabs();
    void _setRelativeTabsHeight(float percent);

    void _setupMovieSeenTable();
    void _setupMovieToSeeTable();
    void _setUpLockedTable(QTableView* table, int rowHeight = 60);
    void _setTableColumnWidths(QTableView* table, const std::vector<int>& proportions);

};
#endif // MAINWINDOW_H
