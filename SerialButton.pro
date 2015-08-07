#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T16:39:22
#
#-------------------------------------------------

QT       += core gui\
            widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialButton
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialportwriter.cpp \
    serialportlistener.cpp \
    command.cpp

HEADERS  += mainwindow.h \
    serialportwriter.h \
    serialportlistener.h \
    command.h

FORMS    += mainwindow.ui
