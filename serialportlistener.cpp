
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportlistener.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>


QT_USE_NAMESPACE

SerialPortListener::SerialPortListener(QSerialPort *serialPort, QObject *parent)
    : QObject(parent)
    , m_serialPort(serialPort)
    , m_standardOutput(stdout)

{
    connect(m_serialPort, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    connect(m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));
    connect(&m_timer, SIGNAL(timeout()), SLOT(handleTimeout()));

    m_timer.start(5000);// si au bout de 5s pas de reponses --> quit

}

SerialPortListener::~SerialPortListener()
{
}

void SerialPortListener::handleReadyRead()
{
    m_Data.append(m_serialPort->readAll());

    if(!m_Data.isEmpty()){
        m_standardOutput << QObject::tr("le buffer fait la taille: ") << m_Data.length() << endl;
        emit getData(m_Data);
    }

    if (!m_timer.isActive())
        m_timer.start(5000);
}

void SerialPortListener::handleTimeout()
{
    if (m_Data.isEmpty()) {
        m_standardOutput << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
        m_standardOutput << QObject::tr("Data successfully received from port %1").arg(m_serialPort->portName()) << endl;
        m_standardOutput << m_Data << endl;
    }

    QCoreApplication::quit();
}

void SerialPortListener::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        m_standardOutput << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
        QCoreApplication::exit(1);
    }
}


QByteArray SerialPortListener::get_Data(){
    return m_Data;
}

