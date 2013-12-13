#-------------------------------------------------
#
# Project created by QtCreator 2013-10-23T00:15:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tinyxml2.cpp \
    jsonparse.cpp \
    test.cpp \
    readfile.cpp \
    myqbuilder.cpp

HEADERS  += mainwindow.h \
    tinyxml2.h \
    myqbuilder.h \
    utils.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    window.xml

LIBS += -lyajl

QMAKE_CXXFLAGS += -std=c++11
