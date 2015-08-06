#ifndef SERIALPORTLISTENER_H
#define SERIALPORTLISTENER_H

#include <QtCore/QtGlobal>

#include <QtSerialPort/QSerialPort>


#include <QTextStream>
#include <QByteArray>
#include <QObject>

class SerialPortListener : public QObject
{
    Q_OBJECT

public:
    SerialPortListener(QSerialPort *serialPort, QObject *parent = 0);
    ~SerialPortListener();

    void write(const QByteArray &writeData);

private slots:
    void readData();
    void handleError(QSerialPort::SerialPortError error);//enum du type d'erreur

private:
    QSerialPort     *m_serialPort;
    QByteArray      m_Data;// donnees recues
};

#endif // SERIALPORTLISTENER_H

