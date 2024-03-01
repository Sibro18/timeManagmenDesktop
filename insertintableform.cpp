#include "insertintableform.h"
#include "ui_insertintableform.h"


insertInTableForm::insertInTableForm(dataBase &base, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertInTableForm)
{
    ui->setupUi(this);
    db = base;
}

insertInTableForm::~insertInTableForm()
{
    delete ui;
}

void insertInTableForm::on_pushButton_clicked()
{

    QRegularExpression pattern("[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}");
    QRegularExpression pattern2("[0-9]{4}-[0-9]{2}-[0-9]{2}");
    if (ui->plaitTextEditTask->toPlainText() != "" && ui->plainTextEditStart->toPlainText() != "" && ui->plaitTextEditDead->toPlainText() != "" ){
       QString task = ui->plaitTextEditTask->toPlainText();
       QString start = ui->plainTextEditStart->toPlainText();
       QString deadLine = ui->plaitTextEditDead->toPlainText();

        if(!(pattern.match(start).hasMatch() || pattern.match(deadLine).hasMatch()) && !(pattern2.match(start).hasMatch() || pattern2.match(deadLine).hasMatch())){
            qDebug() << "the date was entered incorrectly!";
        }
        else{
           db.insert(task,start, deadLine);
           QWidget::close();
        }
    }
    else{
        qDebug() << "all fields must be filled in";
    }
}


void insertInTableForm::on_pushButton_2_clicked()
{
    close();
}

