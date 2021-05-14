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

    socket = new QUdpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(catData()));
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
              socket->writeDatagram(out_datagram.data(), sender, senderPort);
    }
}

void UdpSocket::writeData(QByteArray msg)
{
    socket->writeDatagram(msg, addressPPM, portPPM);
}

bool UdpSocket::bind(QHostAddress addr)
{
    if(socket->state() == QAbstractSocket::BoundState)
        socket->disconnectFromHost();

    return socket->bind(addr, 61200, QUdpSocket::ShareAddress);
}
