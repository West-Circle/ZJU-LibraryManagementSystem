#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_loginbutton_clicked()
{
   this->close();
   login = new Login();
   login->show();
}

void MainWindow::on_registerbutton_clicked()
{
    this->close();
    au = new Authentication();
    au->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}
