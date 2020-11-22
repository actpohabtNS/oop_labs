#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    _movieSeenModel = std::make_shared<MovieSeenModel>();
    _movieToSeeModel = std::make_shared<MovieToSeeModel>();

    _movieSeenModel->setFilepath("moviesSeen.mvf");
    _movieSeenModel->loadData();

    _moviesSeenFilter = new MoviesSeenFilterProxyModel({}, ui->lbl_seenTotalLength,this);
    _moviesSeenFilter->setSourceModel(_movieSeenModel.get());

    ui->tv_seenTable->setModel(_moviesSeenFilter);

    _hoverRowDelegate = new HoverRowDelegate(this);

    connect(ui->tv_seenTable,
            SIGNAL(hoverIndexChanged(const QModelIndex&)),
            _hoverRowDelegate,
            SLOT(onHoverIndexChanged(const QModelIndex&)));
    connect(ui->tv_seenTable,
            SIGNAL(leaveTableEvent()),
            _hoverRowDelegate,
            SLOT(onLeaveTableEvent()));

    ui->tv_seenTable->setItemDelegate(_hoverRowDelegate);

    _setupMovieSeenTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    this->_stretchTabs();
    this->_setRelativeTabsHeight(0.05);
    _setTableColumnWidths(ui->tv_seenTable, {3,15,3,21,29,14,8,2,4});
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   this->_stretchTabs();
   this->_setRelativeTabsHeight(0.05);
   _setTableColumnWidths(ui->tv_seenTable, {3,15,3,21,29,14,8,2,4});
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

    QHeaderView *verticalHeader = ui->tv_seenTable->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(60);

     ui->tv_seenTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

     ui->tv_seenTable->horizontalHeader()->setSortIndicator(6, Qt::DescendingOrder) ;

    _setTableColumnWidths(ui->tv_seenTable, {3,15,3,21,29,14,8,2,4});
}

void MainWindow::_setTableColumnWidths(QTableView* table, const std::vector<int>& proportions)
{
    if (table == nullptr || table->model() == nullptr)
        return;

    int propSum = std::accumulate(proportions.begin(), proportions.end(), 0);
    int tableWidth = table->width();
    double partialWidth = static_cast<double>(tableWidth)/propSum;

    uint columnCount = table->model()->columnCount();

    for (uint idx = 0; idx < proportions.size() && idx < columnCount; idx++) {
        table->setColumnWidth(idx, partialWidth * proportions[idx]);
    }

}


void MainWindow::on_btn_addSeen_clicked()
{
    if (_checkHighlightIsEmpty({ui->le_seenTitle,
                    ui->le_seenGenre}) || !_checkHighlightIsUniqueSeen(ui->le_seenTitle))
        return;

    ui->tv_seenTable->setSortingEnabled(false);

    _movieSeenModel->addMovie({ // TODO: add isEditing check
                                  ui->le_seenTitle->text(),
                                  static_cast<quint8>(ui->sb_seenRate->value()),
                                  ui->le_seenGenre->text(),
                                  ui->le_seenDesc->text(),
                                  ui->le_seenGroup->text(),
                                  QDate::currentDate(),
                                  ui->te_seenLength->time()
                              });

    ui->tv_seenTable->setSortingEnabled(true);

    _clearSeenMovieInputs();
}

void MainWindow::_enableButtonIfNotEmpty(QPushButton *button, std::vector<QLineEdit*> lineEdits)
{
    bool isEnabled = true;

    std::for_each(lineEdits.begin(), lineEdits.end(), [&isEnabled](QLineEdit *lineEdit){
        if (lineEdit && lineEdit->text().isEmpty())
            isEnabled = false;
    });

    button->setEnabled(isEnabled);
}

bool MainWindow::_checkHighlightIsEmpty(std::vector<QLineEdit *> lineEdits, QColor color)
{
    bool anyEmpty = false;

    std::for_each(lineEdits.begin(), lineEdits.end(), [color, &anyEmpty](QLineEdit *lineEdit){
        if (lineEdit && lineEdit->text().isEmpty()) {
            lineEdit->setStyleSheet(lineEdit->styleSheet() + "QLineEdit {"
                                                             "border-bottom-color: " + color.name(QColor::HexRgb) + ";}");
            anyEmpty = true;
        }
    });

    return anyEmpty;
}

bool MainWindow::_checkHighlightIsUniqueSeen(QLineEdit *lineEdit, QColor color)
{
    bool unique = true;

    std::vector<MovieSeen> movies = _movieSeenModel->moviesSeen();

    for (const auto& movie : movies) {
        if (movie.title.toUpper() == lineEdit->text().simplified().toUpper()) { // simplified - chech if "Title" != " Title  "
            lineEdit->setStyleSheet(lineEdit->styleSheet() + "QLineEdit {"
                                                             "border-bottom-color: " + color.name(QColor::HexRgb) + ";}");
            unique = false;
            break;
        }
    }

    return unique;
}

void MainWindow::_setBorderBottomColor(QLineEdit *lineEdit, QColor color)
{
    lineEdit->setStyleSheet(lineEdit->styleSheet() + "QLineEdit {"
                                                     "border-bottom-color: " + color.name(QColor::HexRgb) + ";}");
}

void MainWindow::_clearQLineEdits(std::vector<QLineEdit *> lineEdits)
{
    for (auto lineEdit : lineEdits) {
        if (lineEdit)
            lineEdit->clear();
    }
}

void MainWindow::_clearSeenMovieInputs()
{
    _clearQLineEdits({ui->le_seenTitle, ui->le_seenGenre, ui->le_seenDesc, ui->le_seenGroup});
    ui->sb_seenRate->setValue(0);
    ui->te_seenLength->setTime({0,0});
}

void MainWindow::on_le_seenTitle_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) {
        _setBorderBottomColor(ui->le_seenTitle);
    }
}

void MainWindow::on_le_seenGenre_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) {
        _setBorderBottomColor(ui->le_seenGenre);
    }
}

void MainWindow::on_le_seenSearch_textChanged(const QString &arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive);
    _moviesSeenFilter->setFilterRegExp(regExp);
}
