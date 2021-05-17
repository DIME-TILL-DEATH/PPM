#include "eth_settings_window.h"
#include "ui_eth_settings_window.h"

#include "udpsocket.h"

#include <QDialogButtonBox>
#include <QMessageBox>

eth_settings_window::eth_settings_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eth_settings_window)
{
    validAddress = true;
    validPort = true;
    isAppStarted = false;

    ui->setupUi(this);
}

eth_settings_window::~eth_settings_window()
{
    delete ui;
}

void eth_settings_window::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    ui->listWidget->clear();
    interfacesForSelect.clear();

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

    // Слегка костыльно
    QList<QListWidgetItem*> currentAdapterSelection = ui->listWidget->findItems(selectedAdapter.toString(), Qt::MatchContains);
    if(currentAdapterSelection.size() != 0)
        ui->listWidget->setCurrentItem(currentAdapterSelection.at(0));

}

void eth_settings_window::accept()
{
    if(selectedAdapter.isNull())
    {
        QMessageBox::information(this, "Ошибка", "Адаптер не выбран!");
    }
    else if(!validAddress)
    {
        QMessageBox::information(this, "Ошибка", "Недопустимый IP адрес ППМ!");
    }
    else
    {
        isAppStarted = true;
        emit accepted();
        this->hide();
    }
}

void eth_settings_window::on_listWidget_itemSelectionChanged()
{
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    selectedAdapter = interfacesForSelect.find(curItem->text())->address;
}

void eth_settings_window::on_lineEditIP_textEdited(const QString &arg1)
{
    QPalette *palette = new QPalette();


    if(!addressPPM.setAddress(arg1))
    {
        palette->setColor(QPalette::Base, Qt::red);
        validAddress = false;
    }
    else
    {
        validAddress = true;
    }
    ui->lineEditIP->setPalette(*palette);
}

void eth_settings_window::on_lineEditPort_textEdited(const QString &arg1)
{
    portPPM = arg1.toInt();
}

QHostAddress eth_settings_window::getSelectedAdapter()
{
    return selectedAdapter;
}

bool eth_settings_window::getAppStartedStatus()
{
    return isAppStarted;
}
