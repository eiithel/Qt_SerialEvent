#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T16:39:22
#
#-------------------------------------------------

QT       += core gui\
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialButton
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialportwriter.cpp

HEADERS  += mainwindow.h \
    serialportwriter.h

FORMS    += mainwindow.ui
