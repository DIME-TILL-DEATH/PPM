#ifndef ETH_SETTINGS_WINDOW_H
#define ETH_SETTINGS_WINDOW_H

#include <QDialog>
#include <QListView>

#include <QtNetwork/QHostAddress>

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

protected:
    void showEvent(QShowEvent *);

private slots:
    void on_listWidget_itemSelectionChanged();

private:
    Ui::eth_settings_window *ui;

    QHostAddress selectedAdapter;
};

#endif // ETH_SETTINGS_WINDOW_H
