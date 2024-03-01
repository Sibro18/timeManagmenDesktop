#include "database.h"

dataBase::dataBase(){



}

dataBase::~dataBase(){

    sdb.close();
}

bool dataBase::open(){
    if(!sdb.open())
    {
        sdb = QSqlDatabase::addDatabase("QSQLITE");

        sdb.setDatabaseName("//home//argento//task_manger.db");
    }
    return sdb.open();
}

void dataBase::insert(QString task,QString start, QString deadLine){

    if(!sdb.open()){
        qDebug() << "Что-то не так с соединением!";
        return;
    }
    QSqlQuery query;
    QString time_format = "yyyy-MM-dd HH:mm";

    if(start.size() <= 10) start += " 00:00";
    if(deadLine.size() <= 10) deadLine += " 00:00";
    QDateTime param1 = QDateTime::fromString(start,time_format);
    QDateTime param2 = QDateTime::fromString(deadLine,time_format);

    query.prepare("insert into task_table(task,start,deadline,status) VALUES (:task, :start, :deadLine, :status);");
    query.bindValue(":task", task);
    query.bindValue(":start", param1);
    query.bindValue(":deadLine", param2);
    query.bindValue(":status", 2);

    if(!query.exec()){
        qDebug() << "Ошибка при выполнении запроса:" << query.lastError();
    }
}

void dataBase::removeData(int id){

    if(!sdb.open()){
        qDebug() << "Что-то не так с соединением!";
        return;
    }
    QSqlQuery query;

    query.prepare("Delete from task_table where id =:id;");
    query.bindValue(":id",id);

    if(!query.exec()){
        qDebug() << "Ошибка при выполнении запроса:";
    }
}

void dataBase::editData(QString data, short int status, int id, QString param){

    if(!sdb.open()){
        qDebug() << "Что-то не так с соединением!";
        return;
    }

    QSqlQuery query;

    if(param != "status"){

        if(param == "start"){
            if(data.size() <= 10) data += " 00:00";
            QString time_format = "yyyy-MM-dd HH:mm";
            QDateTime date = QDateTime::fromString(data, time_format);

            query.prepare("Update task_table set start = :start where id = :id;");
            query.bindValue(":start",date);
            query.bindValue(":id",id);
        }
        else if(param == "deadLine"){
            if(data.size() <= 10) data += " 00:00";
            QString time_format = "yyyy-MM-dd HH:mm";
            QDateTime date = QDateTime::fromString(data, time_format);

            query.prepare("update task_table set deadline = :deadLine where id = :id;");
            query.bindValue(":deadLine",date);
            query.bindValue(":id",id);
        }
        else if(param == "task"){
            query.prepare("update task_table set task = :task where id =:id;");
            query.bindValue(":task",data);
            query.bindValue(":id",id);
        }
    }
    else if(status != -1){
        query.prepare("update task_table set status =:status where id =:id;");
        query.bindValue(":status",status);
        query.bindValue(":id",id);
    }


    if(!query.exec()){
        qDebug() << "Ошибка при выполнении запроса:";
    }

}

