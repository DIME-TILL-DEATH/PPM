#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udpsocket.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
