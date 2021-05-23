#include "connectdatabase.h"

QSqlDatabase ConnectDatabase::db = QSqlDatabase::addDatabase("QMYSQL");

ConnectDatabase::ConnectDatabase()
{

}

ConnectDatabase::~ConnectDatabase(){

}

bool ConnectDatabase::openDatabase(){
    db.setHostName("127.0.0.1");
    db.setDatabaseName("librarymanagementsystem");
    db.setUserName("root");
    db.setPassword("");//insert your password (your mysql password)
    if(!db.open()){
        return false;
    }
    else{
        return true;
    }
}

void ConnectDatabase::closeDatabase(){
    db.close();
}
