#include "mainwindow.h"
#include "udpsocket.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UdpSocket udp;
    MainWindow w;
    w.show();
    return a.exec();
}
