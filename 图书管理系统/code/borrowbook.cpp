#include "borrowbook.h"
#include "ui_borrowbook.h"
#include "admingui.h"
BorrowBook::BorrowBook(QWidget *parent, QString id) :
    QWidget(parent),
    ui(new Ui::BorrowBook)
{
    ui->setupUi(this);
    aid = id;
    ui->idlabel->setText(ui->idlabel->text() + id);
}

BorrowBook::~BorrowBook()
{
    delete ui;
}

void BorrowBook::on_back_clicked()
{
    this->hide();
    AdminGUI *ag = new AdminGUI(nullptr, aid);
    ag->show();
}

void BorrowBook::on_searchbutton_clicked()
{
    int flag = 0;
    QSqlQuery bookquery;
    QString bno = ui->bno_line->text();
    QString category = ui->category_comboBox->currentText();
    QString title = ui->bookname_line->text();
    QString press = ui->press_line->text();
    QString author = ui->author_line->text();
    int loweryear = ui->yearbox1->value();
    int upperyear = ui->yearbox2->value();
    QString lowerprice = ui->pricebox1->text();
    QString upperprice = ui->pricebox2->text();
    QString query = "select * from book ";

    if(lowerprice.toDouble() > upperprice.toDouble()
            && lowerprice.toDouble() >= 0 && upperprice.toDouble() >= 0){
        QMessageBox::warning(this,"输入错误","输入的价格上下限错误,请重新输入!");
        return;
    }
    if(loweryear > upperyear
            && loweryear >= 0 && upperyear >= 0){
        QMessageBox::warning(this,"输入错误","输入的年份上下限错误,请重新输入!");
        return;
    }

    if(QString::compare(category, "")){
        query.append("where category = '"+category+"' ");
        flag = 1;
    }

    if(QString::compare(bno, "")){
        if(flag == 0){
            query.append("where bno like '%"+bno+"%' ");
            flag = 1;
        }
        else
            query.append("and bno like '%"+bno+"%' ");
    }

    if(QString::compare(title, "")){
        if(flag == 0){
            query.append("where title like '%"+title+"%' ");
            flag = 1;
        }
        else
            query.append("and title like '%"+title+"%' ");
    }

    if(QString::compare(press, "")){
        if(flag == 0){
            query.append("where press like '%"+press+"%' ");
            flag = 1;
        }
        else
            query.append("and press like '%"+press+"%' ");
    }

    if(QString::compare(author,"")){
        if(flag == 0){
            query.append("where author like '%"+author+"%' ");
            flag = 1;
        }
        else
            query.append("and author like '%"+author+"%' ");
    }

    if(loweryear >= 0 && upperyear >= 0
            && loweryear <= upperyear){
        if(flag == 0){
            query.append("where year <= '"+QString::number(upperyear)+
                         "' and year >= '"+QString::number(loweryear)+"' ");
            flag = 1;
        }
        else
            query.append("and year <= '"+QString::number(upperyear)+
                         "' and year >= '"+QString::number(loweryear)+"' ");
    }

    if(lowerprice.toDouble() >= 0 && upperprice.toDouble() >= 0
            && lowerprice.toDouble() <= upperprice.toDouble()){
        if(flag == 0){
            query.append("where price between '"+lowerprice+
                         "' and '"+upperprice+"' ");
            flag = 1;
        }
        else
            query.append("and price <='"+upperprice+
                         "' and price >= '"+lowerprice+"' ");
    }
    QSqlQuery q;
    ui->BookTable->clearContents();
    bookquery.exec(query);
    int row = 0;
    ui->BookTable->setRowCount(bookquery.size());
    while(bookquery.next()){
        q.exec("select * from book where bno = '"
                +bookquery.value(0).toString()+"'");
        if(q.next()){
            for(int i = 0; i < 9 ; i++){
                if(i == 6){ //price column
                    float p = q.value(i).toFloat();
                    ui->BookTable->setItem(row, i, new QTableWidgetItem(QString::number(p,'f',2)));
                }else{
                    ui->BookTable->setItem(row, i, new QTableWidgetItem(q.value(i).toString()));
                }
            }
        }
        row++;
    }
    ui->BookTable->show();
}

void BorrowBook::on_listeverybookbutton_clicked()
{
    QSqlQuery bookquery;
    QSqlQuery q;
    ui->BookTable->clearContents();
    bookquery.exec("Select * from book");
    int row = 0;
    ui->BookTable->setRowCount(bookquery.size());
    while(bookquery.next()){
        q.exec("select * from book where bno = '"+bookquery.value(0).toString()+"'");
        if(q.next()){
            for(int i = 0; i<9 ;i++){
                if(i == 6){ //price column
                    float p = q.value(i).toFloat();
                    ui->BookTable->setItem(row, i, new QTableWidgetItem(QString::number(p,'f',2)));
                }else{
                    ui->BookTable->setItem(row, i, new QTableWidgetItem(q.value(i).toString()));
                }
            }
        }
        row++;
    }
    ui->BookTable->show();
}

void BorrowBook::on_refreshbutton_clicked()
{
    //same as above
    QSqlQuery bookquery;
    QSqlQuery q;
    ui->BookTable->clearContents();
    bookquery.exec("Select * from book");
    int row = 0;
    ui->BookTable->setRowCount(bookquery.size());
    while(bookquery.next()){
        q.exec("select * from book where bno = '"+bookquery.value(0).toString()+"'");
        if(q.next()){
            for(int i = 0; i<9 ;i++){
                if(i == 6){ //price column
                    float p = q.value(i).toFloat();
                    ui->BookTable->setItem(row, i, new QTableWidgetItem(QString::number(p,'f',2)));
                }else{
                    ui->BookTable->setItem(row, i, new QTableWidgetItem(q.value(i).toString()));
                }
            }
        }
        row++;
    }
    ui->BookTable->show();
}

void BorrowBook::on_borrowbutton_clicked()
{
    QSqlQuery borrowquery;
    QSqlQuery bookquery;
    if(ui->cno_line->text() == ""){
        QMessageBox::warning(this,"输入错误","借书证号不能为空,请填写借书证号!");
        return;
    }
    QString borrow_cno = ui->cno_line->text();
    borrowquery.exec("select bno from borrow where cno ='"+borrow_cno+"' and return_date is null");
    if(!borrowquery.isActive()){
        QMessageBox::warning(this,"查询错误","查询失败");
        return;
    }
    if(borrowquery.size() >= 10){
        QMessageBox::warning(this,"借阅失败","您最多只能借阅10本书!");
        return;
    }else{ //可以借阅
        QList<QTableWidgetItem*> list = ui->BookTable->selectedItems();
        if(list.isEmpty()){
            QMessageBox::warning(this,"错误","请选择需要借阅的书籍!");
            return;
        }
        QString bno = list.at(0)->text();
        //如果这个人的借阅记录中显示已借阅且未归还这本书,那他不能再借阅这本书
        while(borrowquery.next()){
            if(bno == borrowquery.value(0).toString()){
                QMessageBox::warning(this,"借阅失败","抱歉,您已借阅过这本书且未归还,因此您不能再借阅这本书!");
                return;
            }
        }
        QString date = QDate::currentDate().toString("yyyy-MM-dd");
        int stock = 0;
        bookquery.exec("select stock from book where bno = '"+bno+"'");
        if(!bookquery.isActive()){
            QMessageBox::warning(this,"查询错误","查询失败!");
            return;
        }
        if(bookquery.next()){
            stock = bookquery.value(0).toInt();
            if(stock == 0){ //no stock
                QMessageBox::warning(this,"借阅失败","抱歉,书号为"+bno+"的库存不足,无法借阅,请选择其他书籍借阅!");
                return;
            }else{ //got stock can borrow
                borrowquery.exec("insert into borrow values ('"+borrow_cno
                                 +"','"+bno+"','"+aid+"','"+date+"', null)");
                if(!borrowquery.isActive()){
                    QMessageBox::warning(this,"输入错误","输入失败!");
                    return;
                }else{
                    stock = stock - 1;
                    bookquery.exec("update book set stock = '"+QString::number(stock)
                                   +"' where bno = '"+bno+"'");
                    QMessageBox::information(this,"借阅成功","您已成功借阅此书,书号为"+bno);
                    on_refreshbutton_clicked();
                }
            }
        }
    }
}
