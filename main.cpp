
#include "serialportwriter.h"
#include "serialportlistener.h"
#include "command.h"

#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QCoreApplication>
#include <QFile>
#include <QStringList>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication coreApplication(argc, argv);
    int argumentCount = QCoreApplication::arguments().size();
    QStringList argumentList = QCoreApplication::arguments();

    QTextStream standardOutput(stdout);

    if (argumentCount == 1) {
        standardOutput << QObject::tr("Usage: %1 <serialportname> [baudrate]").arg(argumentList.first()) << endl;
        return 1;
    }

    QSerialPort serialPort;
    QString serialPortName = argumentList.at(1);
    serialPort.setPortName(serialPortName);

    int serialPortBaudRate = (argumentCount > 2) ? argumentList.at(2).toInt() : QSerialPort::Baud9600;
    serialPort.setBaudRate(serialPortBaudRate);

    serialPort.open(QIODevice::ReadWrite);//ouverture en lecture/ecriture

    SerialPortWriter serialPortWriter(&serialPort);

    SerialPortListener serialPortListener(&serialPort); //creation du port d'écoute asynchrone
    Command command(&serialPortListener, &serialPortWriter);



    //    QByteArray Datas = QByteArray(serialPortListener.get_Data());//on a rien récuperé ici "blanc sur la console"
    //    standardOutput << Datas.capacity() << endl;
    /*normal, il faut que je crée un SLOT transmit qui va transmettre
     *  mon buffer pour que je puisse l'utiliser dans le main!! Car les
     * datas ne sont connues que lorsque le programme
     * est lancé. Il faut que je fasse une classe qui se charge de récupérer la valeur lue
     * */


    //    if(!Datas.isEmpty()){
    //        standardOutput << QObject::tr("buffer recu non vide") << endl;
    //        if(Datas.contains("HIGH")){
    //            serialPortWriter.write("LEDON\n");
    //            standardOutput << QObject::tr("ordre envoye") << endl;
    //        }

    //    }else{
    //        standardOutput << QObject::tr("buffer recu vide") << endl;
    //    }


    return coreApplication.exec();
}
