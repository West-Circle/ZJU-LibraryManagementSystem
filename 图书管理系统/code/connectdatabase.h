#ifndef CONNECTDATABASE_H
#define CONNECTDATABASE_H

#include <QtSql>
#include <QSqlDatabase>

class ConnectDatabase
{
public:
    ConnectDatabase();
    ~ConnectDatabase();
    static bool openDatabase();
    static void closeDatabase();
private:
    static QSqlDatabase db;
};

#endif // CONNECTDATABASE_H
