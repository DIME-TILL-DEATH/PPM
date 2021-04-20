#include "udpsocket.h"

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkDatagram>

UdpSocket::UdpSocket(QObject *parent):
    QObject(parent)
{
    addressPPM.setAddress("192.168.104.107");
    portPPM = 50080;

    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    for(int i=0; i<interfaces.size(); i++)
    {
       qDebug() << interfaces.at(i).name();
       QList<QNetworkAddressEntry> addresses = interfaces.at(i).addressEntries();
       for(int a=0; a<addresses.size(); a++)
       {
           qDebug() << addresses.at(a).ip() << ", protocol:" << addresses.at(a).ip().protocol();
       }
    }

    socket = new QUdpSocket(this);
   // socket->bind(QHostAddress("192.168.104.10"), 0);

    QByteArray data("Write datagramm from eth_32774");

//    QNetworkDatagram datagram;
//    datagram.setData(data);
//    datagram.setDestination(addressPPM, portPPM);
//    datagram.setSender(interfaces.at(0).interfaceFromName("ethernet_32774").addressEntries().at(1).ip());
//    datagram.setInterfaceIndex(interfaces.at(0).interfaceFromName("ethernet_32774").index());


    socket->bind(interfaces.at(0).interfaceFromName("ethernet_32774").addressEntries().at(1).ip(), 0, QUdpSocket::ShareAddress);
   // qDebug() << interfaces.at(0).interfaceFromName("ethernet_32774");

    qDebug() << socket->writeDatagram("Bind", 4, addressPPM, portPPM);
//    qDebug() << socket->writeDatagram(datagram);

    connect(socket, SIGNAL(readyRead()), this, SLOT(catData()));
}

UdpSocket::~UdpSocket()
{
}

void UdpSocket::catData()
{
    while(socket->hasPendingDatagrams())
    {
        // try QNetworkDatagram
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        qDebug() << QTime::currentTime().toString()
                      << QString("recieved datagram %1:%2| %3.")
                         .arg(sender.toString()).arg(senderPort).arg(QString::fromLocal8Bit(datagram));

        QByteArray out_datagram = "I've received a message: ";

              out_datagram.append(datagram);
              qDebug() << socket->writeDatagram(out_datagram.data(), sender, senderPort);
    }
}
