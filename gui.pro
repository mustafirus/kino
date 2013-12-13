#-------------------------------------------------
#
# Project created by QtCreator 2013-11-15T12:39:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myqbuilder.cpp

HEADERS  += mainwindow.h \
    myqbuilder.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11

unix|win32: LIBS += -ltinyxml2
