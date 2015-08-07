
#include "command.h"
#include "serialportlistener.h"
#include "serialportwriter.h"
#include <QCoreApplication>


QT_USE_NAMESPACE

Command::Command(QSerialPort *serialPort, QObject *parent)
    : QObject(parent)
    ,m_flagHigh(false)
    , m_flagLow(false)
{
    m_listener = new SerialPortListener(serialPort);
    m_writer = new SerialPortWriter(serialPort);

    connect(m_listener,SIGNAL(getData(QByteArray)),this,SLOT(analyzeTrame(QByteArray)));
    connect(this,SIGNAL(sendOrdre(QByteArray)),m_writer,SLOT(writeOrder(QByteArray)));
}

Command::~Command()
{

}

//slots

void Command::ledon(){
    m_writer->write("LEDON\n");
}

void Command::ledoff(){
    m_writer->write("LEDOFF\n");
}

void Command::analyzeTrame(const QByteArray &trame){
    if(trame.contains("HIGH")){
        m_flagHigh = true;
        emit sendOrdre("LEDON\n");
    }else if(trame.contains("LOW")){
        m_flagLow = true;
        emit sendOrdre("LEDOFF\n");

    }else{
        m_flagHigh = false;
        m_flagLow = false;
    }
}

