#include "addcard.h"
#include "ui_addcard.h"

AddCard::AddCard(QWidget *parent,QString id) :
    QWidget(parent),
    ui(new Ui::AddCard)
{
    ui->setupUi(this);
    ui->idlabel->setText(ui->idlabel->text() + id);
}

AddCard::~AddCard()
{
    delete ui;
}

void AddCard::on_addcardbutton_clicked()
{
    QSqlQuery query;
    QString cno = ui->cno_line->text();
    if(ui->cno_line->text() == ""){
        QMessageBox::warning(this,"输入错误","借书证号不能为空,请输入借书证号!",QMessageBox::Ok);
    }
    else if(ui->password_line->text() == ""){
        QMessageBox::warning(this,"输入错误","密码不能为空,请输入密码!",QMessageBox::Ok);
    }
    else if(ui->name_line->text() == ""){
        QMessageBox::warning(this,"输入错误","姓名不能为空,请输入姓名!",QMessageBox::Ok);
    }
    else if(ui->dept_line->text() == ""){
        QMessageBox::warning(this,"输入错误","科系/单位不能为空,请输入科系/单位!",QMessageBox::Ok);
    }
    else if(ui->category_line->text() == ""){
        QMessageBox::warning(this,"输入错误","类别不能为空,请输入类别!",QMessageBox::Ok);
    }
    else{ //都不空
        query.exec("Select * from card where cno = '"+ui->cno_line->text()+"'");
        if(query.next()){ //if yes then already got this card number in database
            QMessageBox::warning(this,"注册失败","该借书证号已被注册,请重新输入借书证号!");
            ui->cno_line->setText("");
            ui->password_line->setText("");
            ui->dept_line->setText("");
            ui->name_line->setText("");
            ui->category_line->setText("");
        }
        else{ //cno not in database
            query.exec("insert into card values('"+ui->cno_line->text()+
                       "','"+ui->password_line->text()+"','"+ui->name_line->text()+
                       "','"+ui->dept_line->text()+"','"+ui->category_line->text()+"')");
            if(!query.isActive()){
                QMessageBox::warning(this,"注册失败","注册失败,请输入正确信息!");
            }
            else{
                QMessageBox::information(this,"注册成功","注册成功,您的借书证号为"+cno+"");
                this->close();
            }
        }
    }

}
