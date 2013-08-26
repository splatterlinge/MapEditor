#-------------------------------------------------
#
# Project created by QtCreator 2013-08-24T23:39:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    VegetationModel.cpp

HEADERS  += MainWindow.hpp \
    VegetationModel.hpp

FORMS    += MainWindow.ui
