#include "sqltable.h"

SQLTable::SQLTable()
{

}

SQLTable::SQLTable( QSqlDatabase * db,const QString &user,const QString &password)
{
    dataBase = new QSqlDatabase;
    dataBase = db;
    //open SQL
    if(dataBase->open(user,password))
    {
        qDebug() << "open Database success" << endl;
        QSqlQuery query(*dataBase);
        query.exec("create table course (id int primary key, "
                   "name varchar(20), password varchar(20)");
        num = 0;
    }
    else
    {
        qDebug() << "Error: open Database failed" << endl;
        return;
    }
}

void SQLTable::insertDataInSQLTable(QMap<QString, QString> &acount)
{
    QMap<QString,QString>::iterator it = acount.begin();
    QSqlQuery query(*dataBase);
    for(;it != acount.end();it++)
    {
        QString inser_str = "insert into course values(%1, %2, %3)";
        inser_str = inser_str.arg(num).arg(it.key()).arg(it.value());
        qDebug() << inser_str << endl;
        query.exec();
        num++;
    }


}

int SQLTable::checkDataInSQLTable(const QMap<QString, QString> &acount)
{
    return 0;
}
