#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "eth_settings_window.h"

#include "udpsocket.h"

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui_ethSettings.show();
    ui->setupUi(this);

    connect(&ui_ethSettings, SIGNAL(accepted()), this, SLOT(ethSettingsChanged()));
    connect(&ui_ethSettings, SIGNAL(rejected()), this, SLOT(ethSettingsRejected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    udp.writeData(sendMsg.toUtf8());
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    sendMsg = arg1;
}

void MainWindow::ethSettingsChanged()
{
    udp.bind(ui_ethSettings.getSelectedAdapter());
}

void MainWindow::ethSettingsRejected()
{
    if(!ui_ethSettings.getAppStartedStatus())
        qApp->quit();
}

void MainWindow::on_actionEthernet_triggered()
{
    ui_ethSettings.show();
}
