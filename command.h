#ifndef COMMAND_H
#define COMMAND_H

#include <QtCore/QtGlobal>

#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QByteArray>
#include <QObject>

#include "serialportlistener.h"
#include "serialportwriter.h"

class command : public QObject
{
    Q_OBJECT

public:
    command(QSerialPort *serialPort, QObject *parent = 0);
    ~command();

private slots:
    void ledon();//if listen "LEDSTATE = 1" --> m_writer send an order to the arduino
    void ledoff();

private:
    SerialPortListener *m_listener;
    SerialPortListener *m_writer;
};

#endif // COMMAND_H

