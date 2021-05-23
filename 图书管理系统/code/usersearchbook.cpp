#include "usersearchbook.h"
#include "ui_usersearchbook.h"
#include "mainwindow.h"
UserSearchBook::UserSearchBook(QWidget *parent, QString id) :
    QWidget(parent),
    ui(new Ui::UserSearchBook)
{
    ui->setupUi(this);
    ui->cnolabel->setText(ui->cnolabel->text()+id);
}

UserSearchBook::~UserSearchBook()
{
    delete ui;
}

void UserSearchBook::on_searchbutton_clicked()
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

void UserSearchBook::on_listeverybookbutton_clicked()
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

void UserSearchBook::on_refreshbutton_clicked()
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

void UserSearchBook::on_logout_clicked()
{
    MainWindow *w = new MainWindow();
    w->show();
    this->close();
}
