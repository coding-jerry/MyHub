#ifndef SQLTABLE_H
#define SQLTABLE_H
#include <QDebug>
#include <QMap>

//SQL数据库header
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class SQLTable
{
public:
    SQLTable();
    SQLTable(QSqlDatabase * db,const QString &user,const QString &password);
    ~SQLTable();

    //insert data
    void insertDataInSQLTable(QMap<QString,QString> &acount);
    //check data
    int checkDataInSQLTable(const QMap<QString,QString> &acount);
    //delete data

    //modify data


private:
    QSqlDatabase *dataBase;
    int num;

};

#endif // SQLTABLE_H
