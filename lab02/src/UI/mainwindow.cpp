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

    _setUpSeen();
    _setUpToSee();
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
    _setTableColumnWidths(ui->tv_toSeeTable, {3,3,15,28,32,8,2,8});
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   this->_stretchTabs();
   this->_setRelativeTabsHeight(0.05);
   _setTableColumnWidths(ui->tv_seenTable, {3,15,3,21,29,14,8,2,4});
   _setTableColumnWidths(ui->tv_toSeeTable, {3,3,15,28,32,8,2,8});
}

void MainWindow::on_moviesTabs_currentChanged(int)
{
    _setTableColumnWidths(ui->tv_seenTable, {3,15,3,21,29,14,8,2,4});
    _setTableColumnWidths(ui->tv_toSeeTable, {3,3,15,28,32,8,2,8});
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
     _setUpLockedTable(ui->tv_seenTable);

     ui->tv_seenTable->sortByColumn(6, Qt::DescendingOrder);

     _setTableColumnWidths(ui->tv_seenTable, {3,15,3,21,29,14,8,2,4});
}

void MainWindow::_setupMovieToSeeTable()
{
     _setUpLockedTable(ui->tv_toSeeTable);

     ui->tv_toSeeTable->sortByColumn(5, Qt::DescendingOrder);

     _setTableColumnWidths(ui->tv_toSeeTable, {3,3,15,28,32,8,2,8});
}

void MainWindow::_setUpLockedTable(QTableView *table, int rowHeight)
{
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    table->horizontalHeader()->setStretchLastSection(true); // for table to take all availible space
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);

    QHeaderView *verticalHeader = table->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(rowHeight);
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

    MovieSeen movie = { ui->le_seenTitle->text().simplified(),
                   static_cast<quint8>(ui->sb_seenRate->value()),
                   ui->le_seenGenre->text().simplified(),
                   ui->le_seenDesc->text().simplified(),
                   ui->le_seenGroup->text().simplified(),
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

void MainWindow::on_btn_addToSee_clicked()
{
    if (_checkHighlightIsEmpty({ui->le_toSeeTitle,
                    ui->le_toSeeGenre}) || !_checkHighlightIsUniqueToSee(ui->le_toSeeTitle))
        return;

    MovieToSee movie = { ui->le_toSeeTitle->text().simplified(),
                   ui->le_toSeeGenre->text().simplified(),
                   ui->le_toSeeDesc->text().simplified(),
                   QDate(),
                   static_cast<quint16>(ui->sb_toSeeLength->value())
               };

    if (_editToSeeRow == -1) {
        movie.added = QDate::currentDate();
        _moviesToSeeModel->addMovie(movie);
    } else {
        movie.added = _moviesToSeeModel->movie(_editToSeeRow).added;
        _moviesToSeeModel->editMovie(_editToSeeRow, movie);

        _editToSeeRow = -1;
        ui->btn_addToSee->setText("+");
        ui->btn_addToSee->setToolTip("Add movie");
    }

    _moviesToSeeFilter->invalidate();
    _clearToSeeMovieInputs();
}

void MainWindow::_enableButtonIfNotEmpty(QPushButton *button, std::vector<QLineEdit*> lineEdits)
{
    bool isEnabled = true;

    std::for_each(lineEdits.begin(), lineEdits.end(), [&isEnabled](QLineEdit *lineEdit){
        if (lineEdit && lineEdit->text().simplified().isEmpty())
            isEnabled = false;
    });

    button->setEnabled(isEnabled);
}

bool MainWindow::_checkHighlightIsEmpty(std::vector<QLineEdit *> lineEdits, QColor color)
{
    bool anyEmpty = false;

    std::for_each(lineEdits.begin(), lineEdits.end(), [color, &anyEmpty](QLineEdit *lineEdit){
        if (lineEdit && lineEdit->text().simplified().isEmpty()) {
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

bool MainWindow::_checkHighlightIsUniqueToSee(QLineEdit *lineEdit, QColor color)
{
    int titleRow = _moviesToSeeModel->titleRow(lineEdit->text().simplified());

    if (titleRow != -1 && titleRow != _editToSeeRow) {
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

void MainWindow::_clearToSeeMovieInputs()
{
    _clearQLineEdits({ui->le_toSeeTitle, ui->le_toSeeGenre, ui->le_toSeeDesc});
    ui->sb_toSeeLength->setValue(1);
}

void MainWindow::on_le_seenTitle_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) {
        _setBorderBottomColor(ui->le_seenTitle);
    }
}

void MainWindow::on_le_toSeeTitle_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) {
        _setBorderBottomColor(ui->le_toSeeTitle);
    }
}

void MainWindow::on_le_seenGenre_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) {
        _setBorderBottomColor(ui->le_seenGenre);
    }
}

void MainWindow::on_le_toSeeGenre_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) {
        _setBorderBottomColor(ui->le_toSeeGenre);
    }
}

void MainWindow::on_le_seenSearch_textChanged(const QString &arg1)
{
    QRegExp regExp(arg1.simplified(), Qt::CaseInsensitive);
    _moviesSeenFilter->setFilterRegExp(regExp);
}

void MainWindow::on_le_toSeeSearch_textChanged(const QString &arg1)
{
    QRegExp regExp(arg1.simplified(), Qt::CaseInsensitive);
    _moviesToSeeFilter->setFilterRegExp(regExp);
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

void MainWindow::on_tv_toSeeTable_clicked(const QModelIndex &index)
{
    int sourceRow = _moviesToSeeFilter->mapToSource(index).row();

    switch (index.column()) {
        case 0: {
            auto movieToSee = _moviesToSeeModel->movie(sourceRow);

            MovieSeen movieSeen;
            movieSeen.title = movieToSee.title;
            movieSeen.rate = 0;
            movieSeen.genre = movieToSee.genre;
            movieSeen.description = movieToSee.description;
            movieSeen.group = "";
            movieSeen.added = QDate::currentDate();
            movieSeen.length = movieToSee.length;

            if (_moviesSeenModel->titleRow(movieSeen.title) == -1) {
                _moviesSeenModel->addMovie(movieSeen);
                _moviesSeenFilter->invalidate();
            }
            // Fallthrough here to delete movie
        }

        case 6: {
        if (_editToSeeRow == sourceRow) {
            _editToSeeRow = -1;
            ui->btn_addToSee->setText("+");
            ui->btn_addToSee->setToolTip("Add movie");

            _clearToSeeMovieInputs();
        }
            _moviesToSeeModel->removeMovie(sourceRow);
            _moviesToSeeFilter->invalidate();
            break;
        }

        case 1: {
            _editToSeeRow = sourceRow;
            ui->btn_addToSee->setText("✓");
            ui->btn_addToSee->setToolTip("Confirm edits");

            auto movie = _moviesToSeeModel->movie(sourceRow);
            ui->le_toSeeTitle->setText(movie.title);
            ui->le_toSeeGenre->setText(movie.genre);
            ui->le_toSeeDesc->setText(movie.description);
            ui->sb_toSeeLength->setValue(movie.length);
            break;
        }

        default: {
            QGuiApplication::clipboard()->setText(
                        _moviesToSeeModel->toString(sourceRow)
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

void MainWindow::on_btn_toSeeCopyAll_clicked()
{
    QString str;

    for (int row = 0; row < _moviesToSeeFilter->rowCount(); row++)
        str += ((row == 0) ? "" : "\n\n") + _moviesToSeeModel->toString(
                    _moviesToSeeFilter->mapToSource(_moviesToSeeFilter->index(row, 0)).row()
                    );

    QGuiApplication::clipboard()->setText(str);
}

void MainWindow::on_btn_seenExport_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this,
           tr("Save Movies Seen list"), "",
           tr("Moviefy Movies Seen (*.mfsn)"));

    for (int row = _moviesSeenFilter->rowCount() - 1; row >= 0; row--)
        _moviesSeenModel->addToFile(
                    _moviesSeenModel->movie(
                        _moviesSeenFilter->mapToSource(_moviesSeenFilter->index(row, 0)).row()
                        ),
                    filepath
                    );
}

void MainWindow::on_btn_toSeeExport_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this,
           tr("Save Movies To See list"), "",
           tr("Moviefy Movies To See (*.mfts)"));

    for (int row = _moviesToSeeFilter->rowCount() - 1; row >= 0; row--)
        _moviesToSeeModel->addToFile(
                    _moviesToSeeModel->movie(
                        _moviesToSeeFilter->mapToSource(_moviesToSeeFilter->index(row, 0)).row()
                        ),
                    filepath
                    );
}

void MainWindow::on_btn_seenImport_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,
           tr("Load Movies Seen list"), "",
           tr("Moviefy Movies Seen (*.mfsn)"));

    _moviesSeenModel->importFromFile(filepath);
    _moviesSeenFilter->invalidate();
}

void MainWindow::on_btn_toSeeImport_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,
           tr("Load Movies ToSee list"), "",
           tr("Moviefy Movies To See (*.mfts)"));

    _moviesToSeeModel->importFromFile(filepath);
    _moviesToSeeFilter->invalidate();
}

void MainWindow::_setUpSeen()
{
    _moviesSeenModel = new MoviesSeenModel();

    _moviesSeenModel->setFilepath("moviesSeen.mfsn");
    _moviesSeenModel->loadFromFile();

    _moviesSeenFilter = new MoviesFilterProxyModel({}, ui->lbl_seenTotalLength,this);
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

void MainWindow::_setUpToSee()
{
    _moviesToSeeModel = new MoviesToSeeModel();

    _moviesToSeeModel->setFilepath("moviesToSee.mfts");
    _moviesToSeeModel->loadFromFile();

    _moviesToSeeFilter = new MoviesFilterProxyModel({}, ui->lbl_toSeeTotalLength,this);
    _moviesToSeeFilter->setSourceModel(_moviesToSeeModel);

    ui->tv_toSeeTable->setModel(_moviesToSeeFilter);

    _moviesToSeeDelegate = new MoviesDelegate(this, MovieTypes::movieToSee);

    connect(ui->tv_toSeeTable,
            SIGNAL(hoverIndexChanged(const QModelIndex&)),
            _moviesToSeeDelegate,
            SLOT(onHoverIndexChanged(const QModelIndex&)));
    connect(ui->tv_toSeeTable,
            SIGNAL(leaveTableEvent()),
            _moviesToSeeDelegate,
            SLOT(onLeaveTableEvent()));

    ui->tv_toSeeTable->setItemDelegate(_moviesToSeeDelegate);

    _setupMovieToSeeTable();

    _editToSeeRow = -1;
}
