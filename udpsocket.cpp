#include "udpsocket.h"

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

UdpSocket::UdpSocket(QObject *parent):
    QObject(parent)
{
    in = new QUdpSocket(this);
    out = new QUdpSocket(this);

    in->bind(QHostAddress::LocalHost, portIn);
    out->connectToHost(QHostAddress::LocalHost, portOut);

    connect(in, SIGNAL(readyRead()), this, SLOT(catData()));


   // out->writeDatagram("hi!", 16, QHostAddress::LocalHost, 50090);
}

UdpSocket::~UdpSocket()
{

}

void UdpSocket::catData()
{
    while(in->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(in->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;
        in->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        qDebug() << QTime::currentTime().toString()
                      << QString("recieved datagram %1:%2| %3.")
                         .arg(sender.toString()).arg(senderPort).arg(QString::fromLocal8Bit(datagram));

        QByteArray out_datagram = "I've received a message: ";

              out_datagram.append(datagram);
              out->write(out_datagram.data());
    }
}
