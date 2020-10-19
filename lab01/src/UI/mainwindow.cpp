#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_console = new Console(ui->graphConsole);
    this->_initGraphs();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_initGraphs()
{
    this->_lgr = new LGraph<Network, int>();
    this->_mgr = new MGraph<Network, int>();

    this->_currGraph = dynamic_cast<Graph<Network, int>*>(this->_lgr);
    this->_curr_IA_T = IA_t::IPv4;
}

void MainWindow::_setGraphValues(const Graph<Network, int> &graph){
    ui->nodesLabel->setText(QString::number(graph.nodes()));
    ui->edgesLabel->setText(QString::number(graph.edges()));
}

void MainWindow::_manage2InputsButton(const QLineEdit *l1, const QLineEdit *l2, QPushButton *b) {
    b->setEnabled(!l1->text().isEmpty() && !l2->text().isEmpty());
}


void MainWindow::on_createNewGraphButton_clicked()
{
    switch (this->_curr_IA_T) {
        case IA_t::IPv4:
            this->_lgr = new LGraph<Network, int>();
            break;

        case IA_t::IPv6:
            this->_mgr = new MGraph<Network, int>();
            break;
    }

    this->_console->newPar();
    this->_console->printTech(this->_currGraph->typeStr() + ": ");
    this->_console->newLine();
    this->_console->print("Created new graph!");
}



// -------------------------------------- SLOTS --------------------------------------

void MainWindow::on_adjMatrixRadioButton_clicked() {
    this->_currGraph = dynamic_cast<Graph<Network, int>*>(this->_lgr);
    this->_setGraphValues(*this->_currGraph);
}

void MainWindow::on_adjListRadioButton_clicked() {
    this->_currGraph = dynamic_cast<Graph<Network, int>*>(this->_mgr);
    this->_setGraphValues(*this->_currGraph);
}

void MainWindow::on_printGraphButton_clicked() {
    this->_console->newPar();
    this->_console->printTech(this->_currGraph->typeStr() + ": ");
    this->_console->newLine();

    if (this->_currGraph->nodes() == 0)
        this->_console->print("Graph is empty!");
    else
        this->_console->print(this->_currGraph->QStr());
}



// -------------------------------------- MANAGING BUTTONS ENABLED/DISABLED --------------------------------------

void MainWindow::on_addNodeInput_textChanged(const QString &arg1) {
    ui->addNodeButton->setEnabled(!arg1.isEmpty());
}

void MainWindow::on_addEdgeFromNodeInput_textChanged(const QString &arg1) {
    arg1.isEmpty();
    this->_manage2InputsButton(ui->addEdgeFromNodeInput, ui->addEdgeToNodeInput, ui->addEdgeButton);
}

void MainWindow::on_addEdgeToNodeInput_textChanged(const QString &arg1) {
    arg1.isEmpty();
    this->_manage2InputsButton(ui->addEdgeFromNodeInput, ui->addEdgeToNodeInput, ui->addEdgeButton);
}

void MainWindow::on_removeNodeInput_textChanged(const QString &arg1) {
    ui->removeNodeButton->setEnabled(!arg1.isEmpty());
}

void MainWindow::on_removeEdgeFromNodeInput_textChanged(const QString &arg1){
    arg1.isEmpty();
    this->_manage2InputsButton(ui->removeEdgeFromNodeInput, ui->removeEdgeToNodeInput, ui->removeEdgeButton);
}

void MainWindow::on_removeEdgeToNodeInput_textChanged(const QString &arg1) {
    arg1.isEmpty();
    this->_manage2InputsButton(ui->removeEdgeFromNodeInput, ui->removeEdgeToNodeInput, ui->removeEdgeButton);
}

void MainWindow::on_minDistanceFromNodeInput_textChanged(const QString &arg1) {
    arg1.isEmpty();
    this->_manage2InputsButton(ui->minDistanceFromNodeInput, ui->minDistanceToNodeInput, ui->minDistanceButton);
}

void MainWindow::on_minDistanceToNodeInput_textChanged(const QString &arg1) {
    arg1.isEmpty();
    this->_manage2InputsButton(ui->minDistanceFromNodeInput, ui->minDistanceToNodeInput, ui->minDistanceButton);
}



// -------------------------------------- MANAGING BUTTONS CLICKS --------------------------------------

void MainWindow::on_addNodeButton_clicked() {

}
