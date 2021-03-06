#ifndef COMMAND_H
#define COMMAND_H

#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QByteArray>
#include <QObject>

class SerialPortListener;
class SerialPortWriter;

class SerialManager : public QObject
{
    Q_OBJECT

public:
    SerialManager(SerialPortListener *listener, SerialPortWriter *writer, QObject *parent = 0);
    ~SerialManager();
    void ledon();//if listen "LEDSTATE = 1" --> m_writer send an order to the arduino
    void ledoff();


private slots:

    void analyzeTrame(const QByteArray &trame);


signals:
    void sendOrdre(const QByteArray &data);

private:
    SerialPortListener *m_listener;
    SerialPortWriter *m_writer;
    QByteArray m_transmitData;
    QTextStream     m_standardOutput;
};

#endif // COMMAND_H

