#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../dataDef/movieTypes.h"

#include <algorithm>
#include <QDebug>
#include <QGuiApplication>
#include <QClipboard>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    _moviesSeenModel = new MoviesSeenModel();
    _moviesToSeeModel = new MoviesToSeeModel();

    _moviesSeenModel->setFilepath("moviesSeen.mfsn");
    _moviesSeenModel->loadFromFile();

    _moviesSeenFilter = new MoviesSeenFilterProxyModel({}, ui->lbl_seenTotalLength,this);
    _moviesSeenFilter->setSourceModel(_moviesSeenModel);

    ui->tv_seenTable->setModel(_moviesSeenFilter);

    _moviesSeenDelegate = new MoviesDelegate(this, MovieTypes::movieSeen);

    connect(ui->tv_seenTable,
            SIGNAL(hoverIndexChanged(const QModelIndex&)),
            _moviesSeenDelegate,
            SLOT(onHoverIndexChanged(const QModelIndex&)));
    connect(ui->tv_seenTable,
            SIGNAL(leaveTableEvent()),
            _moviesSeenDelegate,
            SLOT(onLeaveTableEvent()));

    ui->tv_seenTable->setItemDelegate(_moviesSeenDelegate);

    _setupMovieSeenTable();

    _editSeenRow = -1;
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

     ui->tv_seenTable->sortByColumn(6, Qt::DescendingOrder);

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

    MovieSeen movie = { ui->le_seenTitle->text(),
                   static_cast<quint8>(ui->sb_seenRate->value()),
                   ui->le_seenGenre->text(),
                   ui->le_seenDesc->text(),
                   ui->le_seenGroup->text(),
                   QDate(),
                   static_cast<quint16>(ui->sb_seenLength->value())
               };

    if (_editSeenRow == -1) {
        movie.added = QDate::currentDate();
        _moviesSeenModel->addMovie(movie);
    } else {
        movie.added = _moviesSeenModel->movie(_editSeenRow).added;
        _moviesSeenModel->editMovie(_editSeenRow, movie);

        _editSeenRow = -1;
        ui->btn_addSeen->setText("+");
        ui->btn_addSeen->setToolTip("Add movie");
    }

    _moviesSeenFilter->invalidate();
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
    int titleRow = _moviesSeenModel->titleRow(lineEdit->text().simplified());

    if (titleRow != -1 && titleRow != _editSeenRow) {
        lineEdit->setStyleSheet(lineEdit->styleSheet() + "QLineEdit {"
                                                         "border-bottom-color: " + color.name(QColor::HexRgb) + ";}");
        return false;
    }

    return true;;
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
    ui->sb_seenLength->setValue(1);
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

void MainWindow::on_tv_seenTable_clicked(const QModelIndex &index)
{
    int sourceRow = _moviesSeenFilter->mapToSource(index).row();

    switch (index.column()) {
        case 0: {
            _editSeenRow = sourceRow;
            ui->btn_addSeen->setText("✓");
            ui->btn_addSeen->setToolTip("Confirm edits");

            auto movie = _moviesSeenModel->movie(sourceRow);
            ui->le_seenTitle->setText(movie.title);
            ui->sb_seenRate->setValue(movie.rate);
            ui->le_seenGenre->setText(movie.genre);
            ui->le_seenDesc->setText(movie.description);
            ui->le_seenGroup->setText(movie.group);
            ui->sb_seenLength->setValue(movie.length);
            break;
        }

        case 7: {

        if (_editSeenRow == sourceRow) {
            _editSeenRow = -1;
            ui->btn_addSeen->setText("+");
            ui->btn_addSeen->setToolTip("Add movie");

            _clearSeenMovieInputs();
        }
            _moviesSeenModel->removeMovie(sourceRow);
            _moviesSeenFilter->invalidate();
            break;
        }

        default: {
            QGuiApplication::clipboard()->setText(
                        _moviesSeenModel->toString(sourceRow)
                        );
        }
    }
}

void MainWindow::on_btn_seenCopyAll_clicked()
{
    QString str;

    for (int row = 0; row < _moviesSeenFilter->rowCount(); row++)
        str += ((row == 0) ? "" : "\n\n") + _moviesSeenModel->toString(
                    _moviesSeenFilter->mapToSource(_moviesSeenFilter->index(row, 0)).row()
                    );

    QGuiApplication::clipboard()->setText(str);
}

void MainWindow::on_btn_seenExport_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this,
           tr("Save Movies Seen list"), "",
           tr("Moviefy Movies Seen (*.mfsn);;All Files (*)"));

    for (int row = _moviesSeenFilter->rowCount() - 1; row >= 0; row--)
        _moviesSeenModel->addToFile(
                    _moviesSeenModel->movie(
                        _moviesSeenFilter->mapToSource(_moviesSeenFilter->index(row, 0)).row()
                        ),
                    filepath
                    );
}

void MainWindow::on_btn_seenImport_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,
           tr("Load Movies Seen list"), "",
           tr("Moviefy Movies Seen (*.mfsn);;All Files (*)"));

    _moviesSeenModel->importFromFile(filepath);
    _moviesSeenFilter->invalidate();
}
