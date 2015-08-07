
#include "command.h"
#include "serialportlistener.h"
#include "serialportwriter.h"
#include <QCoreApplication>


QT_USE_NAMESPACE

Command::Command(SerialPortListener *listener, SerialPortWriter *writer, QObject *parent)
    : QObject(parent)
    ,m_flagHigh(false)
    , m_flagLow(false)
    , m_listener(listener)
    , m_writer(writer)
{

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
    m_standardOutput << QObject::tr("rentre dans l'analyse") << endl;
    //on ne rentre jamais dans le slot d'analyse de la trame.

    if(trame.contains("HIGH")){
        m_flagHigh = true;
        m_standardOutput << QObject::tr("valeur flag") << m_flagHigh << endl;

        emit sendOrdre("LEDON\n");
    }else if(trame.contains("LOW")){
        m_flagLow = true;
        m_standardOutput << QObject::tr("valeur flag") << m_flagLow << endl;

        emit sendOrdre("LEDOFF\n");

    }else{
        m_flagHigh = false;
        m_flagLow = false;
    }
}

