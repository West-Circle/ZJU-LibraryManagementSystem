#include "returnbook.h"
#include "ui_returnbook.h"
#include "admingui.h"
ReturnBook::ReturnBook(QWidget *parent, QString id) :
    QWidget(parent),
    ui(new Ui::ReturnBook)
{
    ui->setupUi(this);
    aid = id;
    ui->idlabel->setText(ui->idlabel->text() + id);
}

ReturnBook::~ReturnBook()
{
    delete ui;
}

void ReturnBook::on_back_clicked()
{
    this->hide();
    AdminGUI *ag = new AdminGUI(nullptr, aid);
    ag->show();
}

void ReturnBook::on_listallborrowhistorybutton_clicked()
{
    ui->BookTable->clearContents();
    QSqlQuery query;
    query.exec("Select * from borrow");
    if(!query.isActive()){
        QMessageBox::warning(this,"查询错误","查询失败!");
        return;
    }
    int row = 0;
    ui->BookTable->setRowCount(query.size());
    while(query.next()){
        for(int i = 0; i < 5 ; i++){
            ui->BookTable->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
        }
        row++;
    }
    ui->BookTable->show();
}

void ReturnBook::on_searchcnoborrowhistorybutton_clicked()
{
    QSqlQuery query;
    int row = 0;
    ui->BookTable->clearContents();
    if(ui->cno_line->text() == ""){
        QMessageBox::warning(this,"输入错误","借书证号不能为空,请重新输入借书证号!");
        return;
    }
    QString cno = ui->cno_line->text();
    query.exec("select * from borrow where cno = '"+cno+"'");
    ui->BookTable->setRowCount(query.size());
    if(!query.isActive()){
        QMessageBox::warning(this,"查询错误","查询失败!");
        return;
    }
    while(query.next()){
        for(int i = 0 ; i < 5 ; i++){
            ui->BookTable->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
        }
        row++;
    }
    ui->BookTable->show();
}

void ReturnBook::on_returnbookbutton_clicked()
{
    QList<QTableWidgetItem*> list = ui->BookTable->selectedItems();
    QSqlQuery borrowquery;
    QSqlQuery bookquery;
    if(list.isEmpty()){
        QMessageBox::warning(this,"错误","请选择需要归还的书籍!");
        return;
    }
    QString cno = list.at(0)->text();
    QString bno = list.at(1)->text();
    QString adminid = list.at(2)->text();
    QString returndate = list.at(4)->text();
    if(QString::compare(returndate, "")){ // != 0
        QMessageBox::warning(this,"错误","该用户"+cno+"已经归还此书,请选择未归还的书籍!");
        return;
    }else{ // == 0 没有归还日期
        QString date = QDate::currentDate().toString("yyyy-MM-dd");
        borrowquery.exec("update borrow set return_date = '"+date+"' where cno = '"
                        +cno+"' and bno = '"+bno+"' and adminid = '"+adminid+"'");
        bookquery.exec("update book set stock = stock + 1 where bno = '"+bno+"'");
        if(!borrowquery.isActive()){
            QMessageBox::warning(this,"更新错误","更新失败!");
            return;
        }
        if(!bookquery.isActive()){
            QMessageBox::warning(this,"更新错误","更新失败!");
            return;
        }
        QMessageBox::information(this,"归还成功","用户"+cno+"已成功归还书籍,书号为"+bno+"!");
        on_listallborrowhistorybutton_clicked();
    }

}
