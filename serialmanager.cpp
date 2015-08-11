
#include "serialmanager.h"
#include "serialportlistener.h"
#include "serialportwriter.h"
#include <QCoreApplication>
#include <QDebug>


QT_USE_NAMESPACE

SerialManager::SerialManager(SerialPortListener *listener, SerialPortWriter *writer, QObject *parent)
    : QObject(parent)
    , m_listener(listener)
    , m_writer(writer)
{

    connect(m_listener,SIGNAL(getData(QByteArray)),this,SLOT(analyzeTrame(QByteArray)));
    connect(this,SIGNAL(sendOrdre(QByteArray)),m_writer,SLOT(writeOrder(QByteArray)));
}

SerialManager::~SerialManager()
{

}

//slots

void SerialManager::ledon(){
    m_writer->write("LEDON\n");
}

void SerialManager::ledoff(){
    m_writer->write("LEDOFF\n");
}

void SerialManager::analyzeTrame(const QByteArray &trame){

    static QByteArray temp;
    // static bool flag_H;
    // static bool flag_L;
    static int indexOf_H;
    static int indexOf_L;


    temp.append(trame);


    qDebug() << "Entree dans l'analyse";
    qDebug() << temp;


    if(temp.contains("HIGH")){
        indexOf_H = temp.indexOf("HIGH");
    }else{
        indexOf_H = 50;
    }

    if(temp.contains("LOW")){
        indexOf_L = temp.indexOf("LOW");
    }else{
        indexOf_L=50;
    }


    if(temp.contains("HIGH") && (indexOf_H < indexOf_L)){

        temp.remove(0,(indexOf_H+4)); // on efface du début du buffer et le motif HIGH

        emit sendOrdre("LEDON\n");

    }else if(temp.contains("LOW") && (indexOf_L < indexOf_H)){

        temp.remove(0,(indexOf_L+3)); // on efface du début du buffer jusqu'à 1ere occurence de LOW

        emit sendOrdre("LEDOFF\n");

    }else{
        temp.clear();

        //vider le buffer
    }
}

