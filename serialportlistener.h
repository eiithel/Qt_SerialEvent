#ifndef SERIALPORTLISTENER_H
#define SERIALPORTLISTENER_H

#include <QtCore/QtGlobal>

#include <QtSerialPort/QSerialPort>

#include <QTimer>
#include <QTextStream>
#include <QByteArray>
#include <QObject>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE


class SerialPortListener : public QObject
{
    Q_OBJECT

public:
    SerialPortListener(QSerialPort *serialPort, QObject *parent = 0);
    ~SerialPortListener();
    QByteArray get_Data();


signals:
    void getData(const QByteArray &data);

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);


private:
    QSerialPort     *m_serialPort;
    QByteArray      m_Data;// donnees recues
    QByteArray      m_TransmitData; // donnees transmises
    QTextStream     m_standardOutput;//ou l'on ecrit/recupere les donnees
    QTimer          m_timer;
};

#endif // SERIALPORTLISTENER_H

