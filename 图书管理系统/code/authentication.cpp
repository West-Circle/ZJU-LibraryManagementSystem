#include "authentication.h"
#include "ui_authentication.h"
#include "mainwindow.h"
Authentication::Authentication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Authentication)
{
    ui->setupUi(this);
}

Authentication::~Authentication()
{
    delete ui;
}

void Authentication::on_authentic_button_clicked()
{
    reg = new Register();
    if(QString::compare(code, ui->code_line->text()) == 0){
        QMessageBox::information(this,"验证成功","验证码正确,请注册您的管理员账号!");
        this->close();
        reg->show();
    }else{
        QMessageBox::warning(this,"验证错误","验证码错误,请输入正确的验证码!");
    }
}

void Authentication::on_back_button_clicked()
{
    this->close();
    MainWindow *w = new MainWindow();
    w->show();
}
