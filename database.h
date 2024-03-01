#ifndef DATABASE_H
#define DATABASE_H
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QTextEdit>
#include <QDate>
#include <QSqlError>
#include <QDateTime>

class dataBase
{
private:
    QSqlDatabase sdb;

public:

    dataBase();
    ~dataBase();
    bool open();
    void insert(QString task,QString start, QString deadLine);
    void removeData(int id);
    void editData(QString info, short int status, int id, QString param);


};

#endif // DATABASE_H
