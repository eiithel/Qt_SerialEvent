#ifndef COMMAND_H
#define COMMAND_H

#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QByteArray>
#include <QObject>

class SerialPortListener;
class SerialPortWriter;

class Command : public QObject
{
    Q_OBJECT

public:
    Command(QSerialPort *serialPort, QObject *parent = 0);
    ~Command();
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
    bool m_flagHigh;
    bool m_flagLow;
};

#endif // COMMAND_H

