#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QtCore/QCoreApplication>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

#include <stdint.h>

class UdpSocket:public QObject
{
    Q_OBJECT

    QUdpSocket *socket;
    QNetworkInterface *interface;

    QHostAddress addressPPM;
    quint16 portPPM;

public:
    UdpSocket(QObject *parent=nullptr);

    void writeData(QByteArray msg);
    bool bind(QHostAddress addr);

    void setPPMPort(quint16 port);
    void setPPMAddress(QHostAddress address);

    quint16 getPPMPort();
    QHostAddress getPPMAddress();

protected slots:
    void catData();
};

#endif // UDPSOCKET_H
