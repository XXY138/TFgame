#-------------------------------------------------
#
# Project created by QtCreator 2020-05-27T21:57:28
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TFgame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    button.cpp \
    window.cpp \
    gamewindow.cpp \
    tower.cpp \
    enemy.cpp \
    menubutton.cpp \
    frozentower.cpp \
    endwindow.cpp \
    growingtower.cpp \
    tower2.cpp \
    enemy2.cpp \
    gamewindow2.cpp \
    frozentower2.cpp \
    growingtower2.cpp \
    menubutton2.cpp

HEADERS += \
        mainwindow.h \
    button.h \
    window.h \
    gamewindow.h \
    tower.h \
    enemy.h \
    menubutton.h \
    frozentower.h \
    endwindow.h \
    growingtower.h \
    tower2.h \
    enemy2.h \
    gamewindow2.h \
    frozentower2.h \
    growingtower2.h \
    menubutton2.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture.qrc

DISTFILES +=
