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

    QUdpSocket *in;
    QUdpSocket *out;

    quint16 portIn = 50080;
    quint16 portOut = 50081;
public:
    UdpSocket(QObject *parent=nullptr);
    ~UdpSocket();

protected slots:
    void catData();
};

#endif // UDPSOCKET_H
