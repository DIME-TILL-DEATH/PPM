#ifndef ETH_SETTINGS_WINDOW_H
#define ETH_SETTINGS_WINDOW_H

#include <QDialog>
#include <QListView>

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>


struct s_interfaceForSelect
{
    QNetworkInterface interface;
    QHostAddress address;
};

namespace Ui {
class eth_settings_window;
}

class eth_settings_window : public QDialog
{
    Q_OBJECT

public:
    explicit eth_settings_window(QWidget *parent = nullptr);
    ~eth_settings_window();

    QHostAddress getSelectedAdapter();
    bool getAppStartedStatus();

protected:
    void showEvent(QShowEvent *);

private slots:
    void accept();
    void on_listWidget_itemSelectionChanged();
    void on_lineEditIP_textEdited(const QString &arg1);
    void on_lineEditPort_textEdited(const QString &arg1);

private:
    Ui::eth_settings_window *ui;

    QHash<QString, s_interfaceForSelect> interfacesForSelect;

    QHostAddress selectedAdapter;
    QHostAddress addressPPM;
    quint16 portPPM;

    bool validAddress;
    bool validPort;
    bool isAppStarted;
};

#endif // ETH_SETTINGS_WINDOW_H
