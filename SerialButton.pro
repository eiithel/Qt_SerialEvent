#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T16:39:22
#
#-------------------------------------------------

QT       += core gui\
            widgets serialport\
            core websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialButton
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialportwriter.cpp \
    serialportlistener.cpp \
    serialmanager.cpp \
    socket.cpp

HEADERS  += mainwindow.h \
    serialportwriter.h \
    serialportlistener.h \
    serialmanager.h \
    socket.h

FORMS    += mainwindow.ui
