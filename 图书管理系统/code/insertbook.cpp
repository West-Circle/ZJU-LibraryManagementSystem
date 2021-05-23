#include "insertbook.h"
#include "ui_insertbook.h"
#include "admingui.h"
InsertBook::InsertBook(QWidget *parent, QString id) :
    QWidget(parent),
    ui(new Ui::InsertBook)
{
    ui->setupUi(this);
    aid = id;
    ui->idlabel->setText(ui->idlabel->text() + id);
}

InsertBook::~InsertBook()
{
    delete ui;
}

void InsertBook::on_back_clicked()
{
    this->hide();
    AdminGUI *ag = new AdminGUI(nullptr, aid);
    ag->show();
}

void InsertBook::on_insertbookbutton_clicked()
{
    QSqlQuery query;
    static int totalno = 0;
    static int stockno = 0;
    QString bno = ui->bno_line->text();
    QString category = ui->category_comboBox->currentText();
    QString title = ui->booktitle_line->text();
    QString press = ui->press_line->text();
    QString year = ui->year_line->text();
    QString author = ui->author_line->text();
    QString price = ui->price_line->text();
    QString total = ui->total_line->text();
    QString temptotal = total;
    QString stock = "";
    if(bno == ""){
        QMessageBox::warning(this,"输入错误","书号不能为空,请输入完整的信息!",QMessageBox::Ok);
        return;
    }else if(category == ""){
        QMessageBox::warning(this,"输入错误","类别不能为空,请输入完整的信息!",QMessageBox::Ok);
        return;
    }else if(title == ""){
        QMessageBox::warning(this,"输入错误","书名不能为空,请输入完整的信息!",QMessageBox::Ok);
        return;
    }else if(press == ""){
        QMessageBox::warning(this,"输入错误","出版社不能为空,请输入完整的信息!",QMessageBox::Ok);
        return;
    }else if(year == ""){
        QMessageBox::warning(this,"输入错误","出版年份不能为空,请输入完整的信息!",QMessageBox::Ok);
        return;
    }else if(author == ""){
        QMessageBox::warning(this,"输入错误","作者不能为空,请输入完整的信息!",QMessageBox::Ok);
        return;
    }else if(price == ""){
        QMessageBox::warning(this,"输入错误","价格不能为空,请输入完整的信息!",QMessageBox::Ok);
        return;
    }else if(total == ""){
        QMessageBox::warning(this,"输入错误","数量不能为空,请输入完整的信息!",QMessageBox::Ok);
        return;
    }
    query.exec("select * from book where bno = '"+bno+
               "' and category ='"+category+
               "' and title = '"+title+
               "' and press ='"+press+
               "' and year = '"+year+
               "' and author = '"+author+
               "' and price = '"+price+
               "'");
    if(!query.isActive()){
        QMessageBox::warning(this,"查询错误","查询失败",QMessageBox::Ok);
    }
    if(query.next()){ //already got this book
        totalno = query.value(7).toInt() + total.toInt();
        stockno = query.value(8).toInt() + total.toInt();
        total = QString::number(totalno);
        stock = QString::number(stockno);
        query.exec("update book set total = '"+total+"' where bno = '"+bno+"'");
        query.exec("update book set stock = '"+stock+"' where bno = '"+bno+"'");
        if(!query.isActive()){
            QMessageBox::information(this,"入库失败","入库失败,请重新入库!",QMessageBox::Ok);
            return;
        }else{
            QMessageBox::information(this,"入库成功","该图书《"+title+"》已存在库中,新入的"+temptotal+"本书已成功添加到该书的数量中!",QMessageBox::Ok);
            ui->bno_line->setText("");
            ui->category_comboBox->setCurrentText("");
            ui->booktitle_line->setText("");
            ui->press_line->setText("");
            ui->year_line->setText("");
            ui->author_line->setText("");
            ui->price_line->setText("");
            ui->total_line->setText("");
        }
    }else{ //if no this book
        query.exec("insert into book values('"+bno+"','"
                    +category+"','"+title+"','"+press+"','"+year+"','"
                    +author+"','"+price+"','"+total+"','"+total+"')");
        if(!query.isActive()){
            QMessageBox::information(this,"入库失败","入库失败,请重新入库!",QMessageBox::Ok);
            return;
        }
        else{
            QMessageBox::information(this,"入库成功","图书《"+title+"》已成功入库!",QMessageBox::Ok);
            ui->bno_line->setText("");
            ui->category_comboBox->setCurrentText("");
            ui->booktitle_line->setText("");
            ui->press_line->setText("");
            ui->year_line->setText("");
            ui->author_line->setText("");
            ui->price_line->setText("");
            ui->total_line->setText("");
        }
    }
}

void InsertBook::on_insertmanybookbutton_clicked()
{
    QSqlQuery query;
    int totalno = 0;
    int stockno = 0;
    QString stock = "";
    QFile file("C:\\Users\\ASUS\\Desktop\\Coding\\QT\\LibraryManagementSystem\\data.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"无法打开文件!";
    }
    while(!file.atEnd()){
        QByteArray l = file.readLine();
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString line = codec->toUnicode(l);
        QString bno = line.section(',',0,0);
        QString title = line.section(',',2,2);
        QString total = line.section(',',7,7);
        QString temptotal = total;
        query.exec("select * from book where bno = "+bno);
        if(!query.isActive()){
            QMessageBox::warning(this,"查询错误","查询失败",QMessageBox::Ok);
        }
        if(query.next()){ //已有此书
            totalno = query.value(7).toInt() + total.toInt();
            stockno = query.value(8).toInt() + total.toInt();
            total = QString::number(totalno);
            stock = QString::number(stockno);
            query.exec("update book set total = '"+total+"' where bno = "+bno);
            query.exec("update book set stock = '"+stock+"' where bno = "+bno);
            if(!query.isActive()){
                QMessageBox::information(this,"入库失败","入库失败,请重新入库!!",QMessageBox::Ok);
            }else
                QMessageBox::information(this,"入库成功","该图书《"+title+"》已存在库中,新入的"+temptotal+"本书已成功添加到该书的数量中!",QMessageBox::Ok);
        }else{ //库中未有此书
            query.exec("insert into book values("+line+",'"+total+"')");
            if(!query.isActive()){
                QMessageBox::information(this,"入库失败","入库失败,请重新入库!",QMessageBox::Ok);
                return;
            }else
                QMessageBox::information(this,"入库成功","图书《"+title+"》已成功入库!",QMessageBox::Ok);
        }
    }
}

void InsertBook::on_pushButton_clicked()
{
    QSqlQuery query;
    QString bno = ui->bno_line->text();
    if(bno == ""){
        QMessageBox::warning(this,"查询错误","书号不能为空,查询无效!",QMessageBox::Ok);
        return;
    }
    query.exec("select * from book where bno ='"+bno+"'");
    if(query.next()){
        ui->category_comboBox->setCurrentText(query.value(1).toString());
        ui->booktitle_line->setText(query.value(2).toString());
        ui->press_line->setText(query.value(3).toString());
        ui->year_line->setText(query.value(4).toString());
        ui->author_line->setText(query.value(5).toString());
        ui->price_line->setText(query.value(6).toString());
        QMessageBox::warning(this,"查询成功","查询成功,此书存在本库中,请输入需要添加的数量!",QMessageBox::Ok);
    }else{
        QMessageBox::warning(this,"查询错误","库中不存在此书,查询无效",QMessageBox::Ok);
        ui->category_comboBox->setCurrentText("");
        ui->booktitle_line->setText("");
        ui->press_line->setText("");
        ui->year_line->setText("");
        ui->author_line->setText("");
        ui->price_line->setText("");
        ui->total_line->setText("");
    }
}
