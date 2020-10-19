#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Graph/Graph.h"
#include "../Graph/LGraph.h"
#include "../Graph/MGraph.h"

#include "../Networks/network.h"

#include "console.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createNewGraphButton_clicked();

    void on_adjMatrixRadioButton_clicked();

    void on_adjListRadioButton_clicked();

    void on_printGraphButton_clicked();

    void on_addNodeInput_textChanged(const QString &arg1);

    void on_addEdgeFromNodeInput_textChanged(const QString &arg1);

    void on_addEdgeToNodeInput_textChanged(const QString &arg1);

    void on_removeNodeInput_textChanged(const QString &arg1);

    void on_removeEdgeFromNodeInput_textChanged(const QString &arg1);

    void on_removeEdgeToNodeInput_textChanged(const QString &arg1);

    void on_minDistanceFromNodeInput_textChanged(const QString &arg1);

    void on_minDistanceToNodeInput_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    MGraph<Network, int>* _mgr;
    LGraph<Network, int>* _lgr;

    Graph<Network, int>* _currGraph;

    Console* _console;

    IA_t _curr_IA_T;

    void _initGraphs();
    void _setGraphValues(const Graph<Network, int>& graph);
    void _manage2InputsButton(const QLineEdit* l1, const QLineEdit* l2, QPushButton* b);
};
#endif // MAINWINDOW_H
