#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <QSqlDatabase>
#include <QtSql>

class ConnectDB
{
public:
    ConnectDB();
    QSqlDatabase db;
    QSqlQuery bookQuery;
    QSqlQuery borrowQuery;
    QSqlQuery cardQuery;
    QSqlQuery adminQuery;
};

#endif // CONNECTDB_H
