#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "eth_settings_window.h"

#include "udpsocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_textEdited(const QString &arg1);

    void ethSettingsChanged();
    void ethSettingsRejected();
    void on_actionEthernet_triggered();

private:
    eth_settings_window ui_ethSettings;
    UdpSocket udp;

    QString sendMsg;
    QString recievedMsg;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
