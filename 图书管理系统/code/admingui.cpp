#include "admingui.h"
#include "ui_admingui.h"
#include "mainwindow.h"
AdminGUI::AdminGUI(QWidget *parent, QString id) :
    QMainWindow(parent),
    ui(new Ui::AdminGUI)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("登录成功!");
    aid = id;
    ui->adminidlabel->setText(ui->adminidlabel->text() + id);
}

AdminGUI::~AdminGUI()
{
    delete ui;
}

void AdminGUI::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void AdminGUI::on_actionAbout_System_triggered()
{
    QMessageBox::information(this,"关于系统","此图书管理系统的作者为姚熙源,浙江大学,学号3190300677。");
}

void AdminGUI::on_insertbookbutton_clicked()
{
    this->hide();
    ib = new InsertBook(nullptr, aid);
    ib->show();
}

void AdminGUI::on_borrowbookbutton_clicked()
{
    this->hide();
    bb = new BorrowBook(nullptr, aid);
    bb->show();
}

void AdminGUI::on_returnbookbutton_clicked()
{
    this->hide();
    rb = new ReturnBook(nullptr, aid);
    rb->show();
}

void AdminGUI::on_manageuserbutton_clicked()
{
    this->hide();
    mu = new ManageUser(nullptr, aid);
    mu->show();
}

void AdminGUI::on_actionInsert_Book_triggered()
{
    this->hide();
    ib = new InsertBook(nullptr, aid);
    ib->show();
}

void AdminGUI::on_actionBorrow_Book_2_triggered()
{
    this->hide();
    bb = new BorrowBook(nullptr, aid);
    bb->show();
}

void AdminGUI::on_actionReturn_Book_2_triggered()
{
    this->hide();
    rb = new ReturnBook(nullptr, aid);
    rb->show();
}

void AdminGUI::on_actionManage_User_2_triggered()
{
    this->hide();
    mu = new ManageUser(nullptr, aid);
    mu->show();
}

void AdminGUI::on_actionExit_triggered()
{
    //logout
    MainWindow *w = new MainWindow();
    w->show();
    this->close();
}

void AdminGUI::on_actionExit_2_triggered()
{
    this->close();
}
