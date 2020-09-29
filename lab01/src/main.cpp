#include "src/UI/mainwindow.h"

#include <QApplication>

#define current_ns unit_doctest

namespace current_ns {
    int main_test(int argc, char* argv[]);
}

int main(int argc, char *argv[])
{
    current_ns::main_test(argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
