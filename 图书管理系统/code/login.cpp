#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->AdminID->show();
    ui->cno->hide();
    ui->IDLine->setPlaceholderText("请输入ID");
    ui->PasswordLine->setPlaceholderText("请输入密码");
}

Login::~Login()
{
    delete ui;
}

void Login::on_comboBox_currentIndexChanged(int index)
{
    if(index == 1){
        ui->cno->show();
        ui->AdminID->hide();
    }else{
        ui->cno->hide();
        ui->AdminID->show();
    }
}

void Login::on_back_clicked()
{
    this->close();
    MainWindow *w = new MainWindow();
    w->show();
}

void Login::on_Login_2_clicked()
{
    QSqlQuery query;
    QString password;
    QString id = ui->IDLine->text();
    if(ui->IDLine->text() == "" ){
        QMessageBox::warning(this,tr("登陆失败"),tr("ID不能为空,请重新输入!"),QMessageBox::Ok);
    }
    else if(ui->PasswordLine->text() == ""){
        QMessageBox::warning(this,tr("登陆失败"),tr("密码不能为空,请重新输入!"),QMessageBox::Ok);
    }
    else{ //id和密码都不为空
        if(ui->comboBox->currentIndex() == 0){
            query.exec("select password from admin where adminid = '"+ui->IDLine->text()+"'");
            if(!query.isActive()){
                QMessageBox::critical(this,"登录失败","系统中不存在此管理员ID,请重新输入!",QMessageBox::Ok);
                return;
            }else{
                if(query.next()){
                    password = query.value(0).toString();
                    if(QString::compare(password, ui->PasswordLine->text()) == 0){
                        QMessageBox::information(this,"登录成功","管理员"+ui->IDLine->text()+"登录成功!",QMessageBox::Ok);
                        this->close();
                        admingui = new AdminGUI(nullptr, id);
                        admingui->show();
                    }else{ //password not same != 0
                        QMessageBox::warning(this,"密码错误","密码错误,请重新输入密码!",QMessageBox::Ok);
                    }
                }else{
                    QMessageBox::critical(this,"登录失败","系统中不存在此管理员ID,请重新输入!",QMessageBox::Ok);
                    return;
                }
            }
        }
        else{ //ui->comboBox->currentIndex() == 1
            query.exec("select password from card where cno ='"+ui->IDLine->text()+"'");
            if(!query.isActive()){
                QMessageBox::critical(this,"登录失败","系统中不存在此用户ID,请重新输入!",QMessageBox::Ok);
                return;
            }else{
                if(query.next()){
                    password = query.value(0).toString();
                    if(QString::compare(password, ui->PasswordLine->text()) == 0){
                        QMessageBox::information(this,"登录成功","用户"+ui->IDLine->text()+"登录成功!",QMessageBox::Ok);
                        this->close();
                        usb = new UserSearchBook(nullptr, id);
                        usb->show();
                    }else{ //password not same != 0
                        QMessageBox::warning(this,"密码错误","密码错误,请重新输入密码!",QMessageBox::Ok);
                    }
                }
                else{
                    QMessageBox::critical(this,"登录失败","系统中不存在此用户ID,请重新输入!",QMessageBox::Ok);
                }
            }

        }
    }

}
