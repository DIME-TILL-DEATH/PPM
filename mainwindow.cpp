#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udpsocket.h"

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkDatagram>

// !!!!!!!!!!БЕЗОБРАЗИЕ!!!!!!!!!!!!!!!!!
struct s_interfaceForSelect
{
    QNetworkInterface interface;
    QHostAddress address;
};

QList<QNetworkInterface> interfaces;
QList<QNetworkAddressEntry> addresses;
QMap<int, s_interfaceForSelect> interfacesForSelect;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    interfaces = QNetworkInterface::allInterfaces();

    ui->setupUi(this);

    QList<QNetworkInterface>::Iterator i;
    QList<QNetworkAddressEntry>::Iterator a;
    for(i=interfaces.begin(); i!=interfaces.end(); i++)
    {
       addresses = (*i).addressEntries();
       for(a=addresses.begin(); a!=addresses.end(); a++)
       {
           if((*a).ip().protocol() == QAbstractSocket::IPv4Protocol)
           {
                ui->listWidget->addItem((*i).name()+"::"+(*a).ip().toString());
                interfacesForSelect.insert(ui->listWidget->count()-1, {*i, (*a).ip()});
           }
       }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    sendMsg = arg1;
}

void MainWindow::on_listWidget_itemSelectionChanged()
{

   ui->textBrowser->append((*interfacesForSelect.find(ui->listWidget->currentRow())).interface.name());
}
