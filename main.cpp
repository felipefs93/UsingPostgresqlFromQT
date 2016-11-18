#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "qsqldbhelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;

    const char* driverName = "QPSQL";
    QSQLDbHelper* qSQLDbHelper = new QSQLDbHelper(driverName);
    QSqlDatabase* db = qSQLDbHelper->connect("localhost","admin","admin","");

    if(db->open()) {
        qDebug() << "Db open";
        QSqlQuery* query = new QSqlQuery(*db);
        query->setForwardOnly(true);

        //Select empty person table
        QString name = "Paul";
        if(!query->prepare(QString("SELECT id, name from person where name = ? ")))
        {
            qDebug() << "Error = " << db->lastError().text();
            return -1;
        }else{
            query->addBindValue(name);
        }

        int queryResultRowCount = qSQLDbHelper->selectRowCountResult(query);
        qDebug() << "Initial Row Count = " << queryResultRowCount << "\n";

        //Insert into empty person table
        QString id = "1";
        QString age = "34";
        QString address = "Istanbul";
        if(!query->prepare(QString("INSERT INTO person(id, name, age, address) VALUES (?,?,?,?)"))){
            qDebug() << "Error = " << db->lastError().text();
            return -1;
        }else{
            query->addBindValue(id);
            query->addBindValue(name);
            query->addBindValue(age);
            query->addBindValue(address);
        }

        bool result = qSQLDbHelper->executeInsert(query);
        if(result)
            qDebug() << "Successful insert";
        else
            qDebug() << "Insert failed";

        //Select person table with 1 matching record
        if(!query->prepare(QString("SELECT id, name FROM person WHERE name = ?")))
        {
            qDebug() << "Error = ENTROU" << db->lastError().text();
            return -1;
        }else
            query->addBindValue(name);

        queryResultRowCount = qSQLDbHelper->selectRowCountResult(query);
        qDebug() << "After Insert Row Count = " << queryResultRowCount << "\n";

        //Update person table
        name = "Paul2";
        if(!query->prepare(QString("UPDATE person set name=? where id=? "))){
            qDebug() << "Error = " << db->lastError().text();
            return -1;
        }else{
            query->addBindValue(name);
            query->addBindValue(id);
        }

        result = qSQLDbHelper->executeUpdate(query);
        if(result)
            qDebug() << "Successful update";
        else
            qDebug() << "Update failed";

        //Select person table with 0 no matching record
        if(!query->prepare(QString("SELECT id, name FROM person WHERE name = ?"))){
            qDebug() << "Error = " << db->lastError().text();
            return -1;
        }else{
            query->addBindValue(name);
        }
        queryResultRowCount = qSQLDbHelper->selectRowCountResult(query);
        qDebug() << "After Update RowCount = " << queryResultRowCount << "\n";

        //Delete from person table whose name is Paul2
        //name = "Paul2";

        if(!query->prepare(QString("DELETE FROM person WHERE name = ?"))){
            qDebug() << "Error = " << db->lastError().text();
            return -1;
        }else{
            query->addBindValue(name);
        }

        result = qSQLDbHelper->executeDelete(query);
        if(result)
            qDebug() << "Successful delete";
        else
            qDebug() << "Delete failed";

        //Select person table with 0 no matching record
        if(!query->prepare(QString("SELECT id, name FROM person WHERE name = ? "))){
            qDebug() << "Error = " << db->lastError().text();
            return -1;
        }else{
            query->addBindValue(name);
        }
        queryResultRowCount = qSQLDbHelper->selectRowCountResult(query);
        qDebug() << "After delete row count = " << queryResultRowCount << "\n";

        delete query;
    }else {
        qDebug() << "Something went Wrong:" << db->lastError().text();
    }

    qSQLDbHelper->disConnect();
    delete qSQLDbHelper;

    return a.exec();
}
