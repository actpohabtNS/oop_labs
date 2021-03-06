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
    src/Delegates/hoverrowdelegate.cpp \
    src/Delegates/moviesdelegate.cpp \
    src/Models/moviesSeenModel.cpp \
    src/Models/moviesToSeeModel.cpp \
    src/Models/moviesfilterproxymodel.cpp \
    src/UI/hovertableview.cpp \
    src/UI/mainwindow.cpp \
    src/dataDef/movieSeen.cpp \
    src/dataDef/movieToSee.cpp \
    src/dataDef/timevault.cpp \
    src/main.cpp

HEADERS += \
    src/Delegates/hoverrowdelegate.h \
    src/Delegates/moviesdelegate.h \
    src/Models/moviesSeenModel.h \
    src/Models/moviesToSeeModel.h \
    src/Models/moviesfilterproxymodel.h \
    src/UI/hovertableview.h \
    src/dataDef/movie.h \
    src/dataDef/movieSeen.h \
    src/dataDef/movieToSee.h \
    src/UI/mainwindow.h \
    src/dataDef/movieTypes.h \
    src/dataDef/timevault.h

FORMS += \
    src/UI/mainwindow.ui

INCLUDEPATH += src/UI

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
