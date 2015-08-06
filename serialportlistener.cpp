
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportlistener.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>


SerialPortListener::SerialPortListener(QSerialPort *serialPort, QObject *parent)
    : QObject(parent)
    , m_serialPort(serialPort)
    , m_Data(0)

{
    connect(m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)),SLOT(handleError(QSerialPort::SerialPortError)));
    connect(m_serialPort, SIGNAL(readyRead()), SLOT(readData()));
}


void SerialPortListener::readData()
{
    m_Data = serial->readAll();
}

