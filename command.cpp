
#include "command.h"
#include "serialportlistener.h"
#include "serialportwriter.h"
#include <QCoreApplication>
#include <QDebug>


QT_USE_NAMESPACE

Command::Command(SerialPortListener *listener, SerialPortWriter *writer, QObject *parent)
    : QObject(parent)
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
    QByteArray temp;
    temp.append(trame);

    qDebug() << "Entree dans l'analyse";

    if(temp.contains("HIGH")){

        emit sendOrdre("LEDON\n");
        //vider le buffer
        temp.remove(0,temp.indexOf("HIGH")); // on efface du début du buffer jusqu'à 1ere occurence de HIGH

    }else if(temp.contains("LOW")){

        emit sendOrdre("LEDOFF\n");
        temp.remove(0,temp.indexOf("LOW")); // on efface du début du buffer jusqu'à 1ere occurence de HIGH

    }else{
        temp.clear();
        //vider le buffer
    }
}

