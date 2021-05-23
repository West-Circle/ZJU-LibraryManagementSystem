#include "register.h"
#include "ui_register.h"
#include "mainwindow.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->IDLine->setPlaceholderText("请输入ID");
    ui->PasswordLine->setPlaceholderText("请输入密码");
    ui->nameLine->setPlaceholderText("请输入姓名");
    ui->contact_noLine->setPlaceholderText("请输入联系方式");
}

Register::~Register()
{
    delete ui;
}

void Register::on_back_clicked()
{
    this->close();
    MainWindow *w = new MainWindow();
    w->show();
}

void Register::on_Login_2_clicked()
{

}

void Register::on_RegisterButton_clicked()
{
    QSqlQuery adminQuery;
    QString properties;
    QString values;

    if(ui->IDLine->text() == ""){
        QMessageBox::warning(this,tr("注册失败"),tr("ID不能为空,请重新输入!"),QMessageBox::Ok);
    }
    else if(ui->PasswordLine->text() == ""){
        QMessageBox::warning(this,tr("注册失败"),tr("密码不能为空,请重新输入!"),QMessageBox::Ok);
    }
    else if(ui->nameLine->text() == ""){
        QMessageBox::warning(this,tr("注册失败"),tr("姓名不能为空,请重新输入!"),QMessageBox::Ok);
    }
    else if(ui->contact_noLine->text() == ""){
        QMessageBox::warning(this,tr("注册失败"),tr("联系方式不能为空,请重新输入!"),QMessageBox::Ok);
    }
    else{
        if(ui->PasswordLine->text().length() > 20 || ui->PasswordLine->text().length() < 5){
            QMessageBox::warning(this,"密码输入错误","您所输入的密码长度必须在5-20位之间!",QMessageBox::Ok);
        }else{
            adminQuery.exec("SELECT adminid FROM admin WHERE adminid = '"+ui->IDLine->text()+"'");
            if(adminQuery.next()){
                QMessageBox::warning(this,"注册失败","该管理员ID已被注册,请重新输入新的管理员ID!");
            }else{
                properties = "adminid, password, name, contact_no";
                values = ":adminid, :password, :name, :contact_no";
                adminQuery.prepare("INSERT INTO admin("+properties+") \
                                    VALUES("+values+")");
                adminQuery.bindValue(":adminid",ui->IDLine->text());
                adminQuery.bindValue(":password",ui->PasswordLine->text());
                adminQuery.bindValue(":name",ui->nameLine->text());
                adminQuery.bindValue(":contact_no",ui->contact_noLine->text());
                adminQuery.exec();
                if(adminQuery.isActive()){
                    QMessageBox::information(this,"注册成功","管理员注册成功!",QMessageBox::Ok);
                    this->close();
                    MainWindow *w = new MainWindow();
                    w->show();
                }
                else{
                    QMessageBox::critical(this,"注册失败","注册失败!",QMessageBox::Ok);
                }
            }
        }
    }
}
