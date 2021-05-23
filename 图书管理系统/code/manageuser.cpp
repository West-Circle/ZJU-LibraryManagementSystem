#include "manageuser.h"
#include "ui_manageuser.h"
#include "admingui.h"
#include "addcard.h"
ManageUser::ManageUser(QWidget *parent, QString id) :
    QWidget(parent),
    ui(new Ui::ManageUser)
{
    ui->setupUi(this);
    aid = id;
    ui->idlabel->setText(ui->idlabel->text() + id);
}

ManageUser::~ManageUser()
{
    delete ui;
}

void ManageUser::on_back_clicked()
{
    this->hide();
    AdminGUI *ag = new AdminGUI(nullptr, aid);
    ag->show();
}

void ManageUser::on_addcardbutton_clicked()
{
    AddCard *ac = new AddCard(nullptr, aid);
    ac->show();
}

void ManageUser::on_searchcardinfobutton_clicked()
{
    QSqlQuery query;
    ui->BookTable->clearContents();
    query.exec("Select * from card");
    int row = 0;
    QSqlQuery q;
    ui->BookTable->setRowCount(query.size());
    while(query.next()){
        q.exec("Select * from card where cno = '"+query.value(0).toString()+"'");
        if(q.next()){
            for(int i = 0; i < 5 ; i++){
                ui->BookTable->setItem(row, i, new QTableWidgetItem(q.value(i).toString()));
            }
        }
        row++;
    }
    ui->BookTable->show();
}

void ManageUser::on_refreshbutton_clicked()
{
    QSqlQuery query;
    ui->BookTable->clearContents();
    query.exec("Select * from card");
    int row = 0;
    QSqlQuery q;
    ui->BookTable->setRowCount(query.size());
    while(query.next()){
        q.exec("Select * from card where cno = '"+query.value(0).toString()+"'");
        if(q.next()){
            for(int i = 0; i < 5 ; i++){
                ui->BookTable->setItem(row, i, new QTableWidgetItem(q.value(i).toString()));
            }
        }
        row++;
    }
    ui->BookTable->show();
}

void ManageUser::on_deletecardbutton_clicked()
{
    QList<QTableWidgetItem*> list = ui->BookTable->selectedItems();
    if(list.isEmpty()){
        QMessageBox::warning(this,"错误","请选择需要删除的借书证号!");
        return;
    }
    QString cno = list.at(0)->text();
    QSqlQuery borrowquery;
    QSqlQuery cardquery;
    borrowquery.exec("select cno from borrow where cno = '"+cno+"' and return_date is null");
    if(!borrowquery.isActive()){
        QMessageBox::warning(this,"查询错误","查询错误");
    }
    if(borrowquery.next()){ //got book haven't return
        QMessageBox::warning(this,"删除失败","该用户"+cno+"所借阅的书籍仍未归还,无法删除此用户的借书证号,请归还所有书后才来删除!");
    }
    else{ //all book return , can delete succesfully
        //delete the borrow book history info in borrow table
        borrowquery.exec("delete from borrow where cno = '"+cno+"'");
        if(!borrowquery.isActive()){
            QMessageBox::warning(this,"删除失败","请选择正确的卡号!");
        }else{
            QMessageBox::information(this,"删除成功","该用户"+cno+"的借阅记录已成功删除!");
        }
        cardquery.exec("delete from card where cno = '"+cno+"'");
        if(!cardquery.isActive()){
            QMessageBox::warning(this,"删除失败","请选择正确的卡号!");
        }else{
            QMessageBox::information(this,"删除成功","该用户"+cno+"的借书证号已成功删除!");
            on_refreshbutton_clicked();
        }
    }
}

void ManageUser::on_searchcnobutton_clicked()
{
    QSqlQuery query;
    QSqlQuery q;
    QString cno = ui->cno_line->text();
    query.exec("Select * from card where cno = '"+cno+"'");
    int row = 0;
    ui->BookTable->clearContents();
    ui->BookTable->setRowCount(query.size());
    while(query.next()){
        q.exec("select * from card where cno = '"+query.value(0).toString()+"'");
        if(q.next()){
            for(int i = 0 ; i < 5; i++){
                ui->BookTable->setItem(row,i,new QTableWidgetItem(q.value(i).toString()));
            }
        }
        row++;
    }
    ui->BookTable->show();
}
