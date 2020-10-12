QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Networks/ipv4.cpp \
    src/Networks/ipv6.cpp \
    src/main.cpp \
    src/UI/mainwindow.cpp \
    tests/LGraph_tests.cpp \
    tests/MGraph_tests.cpp \
    tests/doctest_main.cpp \
    tests/ipv4_tests.cpp

HEADERS += \
    src/Graph/Graph.h \
    src/Graph/LGraph.h \
    src/Graph/MGraph.h \
    src/Networks/IpAddress_types.h \
    src/Networks/ipAddress.h \
    src/Networks/ipv4.h \
    src/Networks/ipv6.h \
    src/UI/mainwindow.h \
    tests/doctest.h

FORMS += \
    src/UI/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
