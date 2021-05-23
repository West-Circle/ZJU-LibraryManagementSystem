#include "mainwindow.h"
#include <QApplication>
#include "connectdatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!ConnectDatabase::openDatabase()){
        QMessageBox::critical(nullptr,"无法连接","数据库连接失败!");
    }
    else{
        QMessageBox::information(nullptr,"已连接","数据库连接成功!");
    }

    MainWindow w;
    w.show();


    return a.exec();
}
