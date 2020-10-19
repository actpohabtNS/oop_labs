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

    void on_addNodeButton_clicked();

    void on_addEdgeButton_clicked();

    void on_removeNodeButton_clicked();

    void on_removeEdgeButton_clicked();

    void on_isConnectedButton_clicked();

    void on_isCyclicButton_clicked();

    void on_minDistanceButton_clicked();

private:
    Ui::MainWindow *ui;

    ///
    /// \brief _mgr
    ///
    /// Pointer to MGraph, that can be manipulated by used via GUI
    ///
    MGraph<Network, int>* _mgr;

    ///
    /// \brief _lgr
    ///
    /// Pointer to LGraph, that can be manipulated by used via GUI
    ///
    LGraph<Network, int>* _lgr;

    ///
    /// \brief _currGraph
    ///
    /// Pointer to current graph used in GUI
    ///
    Graph<Network, int>* _currGraph;

    ///
    /// \brief _console
    ///
    /// Pointer to console Widget
    ///
    Console* _console;

    ///
    /// \brief _curr_IA_T
    ///
    /// Current IpAddress type used in GUI
    ///
    IA_t _curr_IA_T;

    // ---------------------- inits during class obj creation ----------------------
    ///
    /// \brief _initGraphs
    ///
    /// Initializing graphs in MainWindow before user can interact with GUI
    ///
    void _initGraphs();


    // ---------------------- other ----------------------
    ///
    /// \brief _printCallerToConsole
    ///
    /// Prints tyme, Graph type and IpAddress type last command was addressed to by user
    ///
    void _printCallerToConsole();


    //---------------------- managing multiple objects in GUI ----------------------
    ///
    /// \brief _setGraphValues
    /// \param graph - Graph which values to be
    ///
    /// Sets current graph's used parameters (nodes & edges number) below console
    ///
    void _setGraphValues(const Graph<Network, int>& graph);

    ///
    /// \brief _manage2InputsButton
    /// \param l1 - QLineEdit to get input from
    /// \param l2 - QLineEdit to get input from
    /// \param b - QPushButton to be controlled
    ///
    /// Set Button enable depending on input from l1 and l2
    ///
    void _manage2InputsButton(const QLineEdit* l1, const QLineEdit* l2, QPushButton* b);

    ///
    /// \brief _setInputMasks
    /// \param type - IpAddress type currently used in GUI
    ///
    /// Sets corresponding to IpAddress yupe InputMask to all inputs
    ///
    void _setInputMasks(IA_t type);


    //---------------------- getters ----------------------
    ///
    /// \brief _curr_IA_t_QStr
    /// \return QString - QString representation of current IpAddress used in GUI
    ///
    /// Returns current IpAddress used in GUI in QString
    ///
    QString _curr_IA_t_QStr() const;


    //---------------------- GUI getters ----------------------
    ///
    /// \brief _getNetwork
    /// \param l - QLineEdit to get input from
    /// \return Network* - Pointer to Network created of input
    ///
    /// Returns pointer to Network created from input of QLineEdit
    ///
    Network* _getNetwork(const QLineEdit* l) const;
};
#endif // MAINWINDOW_H
