#include "eth_settings_window.h"
#include "ui_eth_settings_window.h"

#include "udpsocket.h"

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>


// !!!!!!!!!!БЕЗОБРАЗИЕ!!!!!!!!!!!!!!!!!
struct s_interfaceForSelect
{
    QNetworkInterface interface;
    QHostAddress address;
};
QHash<QString, s_interfaceForSelect> interfacesForSelect;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

eth_settings_window::eth_settings_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eth_settings_window)
{
    ui->setupUi(this);
}

eth_settings_window::~eth_settings_window()
{
    delete ui;
}

void eth_settings_window::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    QList<QNetworkAddressEntry> addresses;
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    QString itemName;
    QList<QNetworkInterface>::Iterator i;
    QList<QNetworkAddressEntry>::Iterator a;
    for(i=interfaces.begin(); i!=interfaces.end(); i++)
    {
       addresses = (*i).addressEntries();
       for(a=addresses.begin(); a!=addresses.end(); a++)
       {
           if((*a).ip().protocol() == QAbstractSocket::IPv4Protocol)
           {
               itemName = (*i).name()+"::"+(*a).ip().toString();
               ui->listWidget->addItem(itemName);
               interfacesForSelect.insert(itemName, {*i, (*a).ip()});
           }
       }
    }
}

void eth_settings_window::on_listWidget_itemSelectionChanged()
{
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    selectedAdapter = interfacesForSelect.find(curItem->text())->address;
}

QHostAddress eth_settings_window::getSelectedAdapter()
{
    return selectedAdapter;
}
