#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    _movieSeenModel = std::make_shared<MovieSeenModel>();
    _movieToSeeModel = std::make_shared<MovieToSeeModel>();

    ui->tv_seenTable->setModel(_movieSeenModel.get());

    _setupMovieSeenTable();

    _movieSeenModel->addMovie({"test1", 5, "Genre", "Description", "Group", });
    _movieSeenModel->addMovie({"test2", 5, "et", "ewwewef", "efe", });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *ev)
{
    this->_stretchTabs();
    this->_setRelativeTabsHeight(0.05);
    _setTableColumnWidths(ui->tv_seenTable, {7,1,10,16,7,2,2});
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   this->_stretchTabs();
   this->_setRelativeTabsHeight(0.05);
   _setTableColumnWidths(ui->tv_seenTable, {7,1,10,16,7,2,2});
}

void MainWindow::_stretchTabs()
{
    int width = ui->moviesTabs->width();
    int tabCount = ui->moviesTabs->count();
    int tabWidth = width / tabCount - 1; // - 1 is done for TabScroll not to appear
    ui->moviesTabs->setStyleSheet( ui->moviesTabs->styleSheet() +
                                        "QTabBar::tab {"
                                        "width: " + QString::number(tabWidth) + "px; }" );
}

void MainWindow::_setRelativeTabsHeight(float percent)
{
    int height = ui->moviesTabs->height();
    int tabHeight = height * percent;
    ui->moviesTabs->setStyleSheet( ui->moviesTabs->styleSheet() +
                                        "QTabBar::tab {"
                                        "height: " + QString::number(tabHeight) + "px; }" );
}

void MainWindow::_setupMovieSeenTable()
{
    ui->tv_seenTable->verticalHeader()->setVisible(false);
    ui->tv_seenTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tv_seenTable->horizontalHeader()->setStretchLastSection(true); // for table to take all availible space
    ui->tv_seenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv_seenTable->setFocusPolicy(Qt::NoFocus);
    ui->tv_seenTable->setSelectionMode(QAbstractItemView::NoSelection);

    _setTableColumnWidths(ui->tv_seenTable, {7,1,10,16,7,2,2});
}

void MainWindow::_setTableColumnWidths(QTableView* table, std::vector<int> proportions)
{
    if (table == nullptr || table->model() == nullptr)
        return;

    int propSum = std::accumulate(proportions.begin(), proportions.end(), 0);
    int tableWidth = table->width();
    double partialWidth = static_cast<double>(tableWidth)/propSum - 1; // - 1 is done for TabScroll not to appear

    uint columnCount = table->model()->columnCount();

    for (uint idx = 0; idx < proportions.size() && idx < columnCount; idx++) {
        table->setColumnWidth(idx, partialWidth * proportions[idx]);
    }
}

