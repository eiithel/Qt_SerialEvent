
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
    static bool flag_H;
    static bool flag_L;

    temp.append(trame);


    qDebug() << "Entree dans l'analyse";
    qDebug() << temp;

    if(temp.contains("HIGH") && !flag_H){
        flag_H = true;
        flag_L = false;

        temp.remove(0,(temp.indexOf("HIGH")+4)); // on efface du début du buffer et le motif HIGH
        //cela ne fonctionne pas

        emit sendOrdre("LEDON\n");
        //vider le buffer

    }else if(temp.contains("LOW") && !flag_L){
        flag_L = true;
        flag_H = false;

        temp.remove(0,(temp.indexOf("LOW")+3)); // on efface du début du buffer jusqu'à 1ere occurence de HIGH

        emit sendOrdre("LEDOFF\n");

    }else{
        temp.clear();
        flag_H = false;
        flag_L = false;

        //vider le buffer
    }
}

