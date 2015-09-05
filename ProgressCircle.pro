#-------------------------------------------------
#
# Project created by QtCreator 2015-09-04T13:18:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProgressCircle
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES +=\
    ProgressCircle.cpp \
    Demo.cpp

HEADERS  += \
    ProgressCircle.h \
    DemoItem.h \
    DemoWindow.h

FORMS    += \
    DemoWindow.ui
