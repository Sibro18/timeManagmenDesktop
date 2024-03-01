#include "updateform.h"
#include "ui_updateform.h"

updateForm::updateForm(dataBase &base, QList<QString> values, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateForm)
{
    ui->setupUi(this);
    ui->plaitTextEditTask_2->setPlainText(values.at(1));
    ui->plainTextEditStart_2->setPlainText(values.at(2));
    ui->plaitTextEditDead_2->setPlainText(values.at(3));
    db = base;
    indexFromTable = values.at(0).toInt();
}

updateForm::~updateForm()
{
    delete ui;
}

void updateForm::on_pushButton_clicked()
{
    QString task = ui->plaitTextEditTask->toPlainText();
    QString start = ui->plainTextEditStart->toPlainText();
    QString dead= ui->plaitTextEditDead->toPlainText();
    QRegularExpression pattern("[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}");
    QRegularExpression pattern2("[0-9]{4}-[0-9]{2}-[0-9]{2}");
     qDebug() << start << " " << dead << task;
    if(task.size() > 0){
        supportFun(task,"task");
    }
    if(dead.size() > 0){
        if(!pattern.match(dead).hasMatch() && !pattern2.match(dead).hasMatch()){
            qDebug() << "the date was entered incorrectly!";
        }
        else{
            supportFun(dead,"deadLine");
        }
    }
    if(start.size() > 0){
        if(!pattern.match(start).hasMatch() && !pattern2.match(start).hasMatch()){
            qDebug() << "the date was entered incorrectly!";
        }
        else{
            supportFun(start,"start");
        }
    }
}

void updateForm::supportFun(QString data, QString param){
    db.editData(data,-1,indexFromTable,param);
}


void updateForm::on_pushButton_2_clicked()
{
    close();
}

