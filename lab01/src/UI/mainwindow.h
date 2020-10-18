#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Graph/Graph.h"
#include "../Graph/LGraph.h"
#include "../Graph/MGraph.h"

#include "../Networks/network.h"

#include "console.h"

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    MGraph<Network, int>* _mgr;
    LGraph<Network, int>* _lgr;

    Graph<Network, int>* _currGraph;

    Console* _console;

    IA_t _curr_IA_T;

    void _initGraphs();
};
#endif // MAINWINDOW_H
