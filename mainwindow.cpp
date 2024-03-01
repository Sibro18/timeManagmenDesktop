#include "mainwindow.h"
#include "./ui_mainwindow.h"


void selectFromTable(QTableWidget* widget, dataBase db, QString str);
bool verificationDate(QDateTime dead);
void removeInformation(QTableWidget* widget, dataBase db);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/res/tasks-list-on-clipboard.svg"));
    db.open();

    toolbar = new QToolBar("", this);
    addToolBar(toolbar);
        QAction *action1 = new QAction(QIcon(":/icons/res/11954452971071026229jean_victor_balin_add.svg.med.png"),"Add", this);
        toolbar->addAction(action1);

        QAction *action2 = new QAction(QIcon(":/icons/res/v703268-1412879303.png"),"Delete", this);
        toolbar->addAction(action2);

        QAction *action3 = new QAction(QIcon(":/icons/res/UniversalEditButton2.svg.png"),"Edit", this);
        toolbar->addAction(action3);

        QAction *action4 = new QAction(QIcon(":/icons/res/1676524258_catherineasquithgallery-com-p-znachki-na-zelenom-fone-82.png"),"Succes", this);
        toolbar->addAction(action4);

        QAction *action5 = new QAction(QIcon(":/icons/res/574307.png"),"Refresh",this);
        toolbar->addAction(action5);

    connect(action1, &QAction::triggered, this, &MainWindow::onAction1Triggered);
    connect(action2, &QAction::triggered, this, &MainWindow::onAction2Triggered);
    connect(action3, &QAction::triggered, this, &MainWindow::onAction3Triggered);
    connect(action4, &QAction::triggered, this, &MainWindow::onAction4Triggered);
    connect(action5, &QAction::triggered, this, &MainWindow::onAction5Triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAction1Triggered()
{
    addForm = new insertInTableForm(db, this);
    addForm->show();

}

void MainWindow::onAction2Triggered()
{
    if(ui->tabWidget->currentIndex() == 0){
        removeInformation(ui->tableWidgetAct,db);
    }
    else if(ui->tabWidget->currentIndex() == 1){
        removeInformation(ui->tableWidgetDone,db);
    }
    else if(ui->tabWidget->currentIndex() == 2){
        removeInformation(ui->tableWidgetFailed,db);
    }
    else if(ui->tabWidget->currentIndex() == 3){
        removeInformation(ui->tableWidgetAll,db);
    }

}

void MainWindow::onAction3Triggered()
{
    if(ui->tabWidget->currentIndex() == 0 && ui->tableWidgetAct->rowCount() > 0){
        int indexRow = ui->tableWidgetAct->currentRow();
        QList<QString> values;

        for (int column_index = 0; column_index < ui->tableWidgetAct->columnCount(); ++column_index) {
            QTableWidgetItem* item = ui->tableWidgetAct->item(indexRow, column_index);
            if (item != nullptr) {
                QString value = item->text();
                values.append(value);
            } else {
                values.append(""); // Добавляем пустую строку, если ячейка пустая
            }
        }
        updForm = new updateForm(db,values,this);
        updForm->show();
    }
}

void MainWindow::onAction4Triggered()
{
    int indexRow = 0;
    if(ui->tabWidget->currentIndex() == 0){
        if(ui->tableWidgetAct->rowCount() > 0){
            indexRow = ui->tableWidgetAct->currentRow();
            auto indexToTable = ui->tableWidgetAct->item(indexRow,0);
            QString value = indexToTable->text();

            db.editData("", 1 , value.toInt() ,"status");
        }
    }

}

void MainWindow::onAction5Triggered(){

    QString str;
    QTableWidget* widget = nullptr;
    if(ui->tabWidget->currentIndex() == 0){
        str = "select * from task_table where status = 2";
        widget = ui->tableWidgetAct;
    }

    if(ui->tabWidget->currentIndex() == 1){
        str = "select * from task_table where status = 1";
        widget = ui->tableWidgetDone;
    }


    if(ui->tabWidget->currentIndex() == 2){
        str = "select * from task_table where status = 0";
        widget = ui->tableWidgetFailed;
    }


    if(ui->tabWidget->currentIndex() == 3){
        str = "select * from task_table";
        widget = ui->tableWidgetAll;
    }
    selectFromTable(widget,db,str);
}

void MainWindow::on_tabWidget_tabBarClicked(int index){
    if (index == 0){
        QString str = "select * from task_table where status = 2";
        selectFromTable(ui->tableWidgetAct,db,str);
    }
    else if(index == 1){
        QString str = "SELECT * FROM task_table where status = 1";
        selectFromTable(ui->tableWidgetDone,db,str);
    }
    else if (index == 2)
    {
        QString str = "SELECT * FROM task_table where status = 0";
        selectFromTable(ui->tableWidgetFailed,db,str);
    }
    else if (index == 3){
        QString str = "SELECT * FROM task_table";
        selectFromTable(ui->tableWidgetAll,db,str);
    }
}

void selectFromTable(QTableWidget* widget, dataBase db, QString str){

    if(db.open()){
        widget->horizontalHeader()->setStretchLastSection(false);
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(str);

        widget->setColumnCount(model->columnCount());
        widget->setRowCount(model->rowCount());
        widget->setColumnHidden(0, true);
        widget->setColumnHidden(4, true);

        QDateTime dead;

        QTableWidgetItem *idHeader = new QTableWidgetItem("id");
        QTableWidgetItem *task = new QTableWidgetItem("task");
        QTableWidgetItem *startDateHeader = new QTableWidgetItem("start date");
        QTableWidgetItem *deadlineHeader = new QTableWidgetItem("deadline");
        QTableWidgetItem *statusHeader = new QTableWidgetItem("status");

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int column = 0; column < model->columnCount(); ++column) {

                QModelIndex index = model->index(row, column);
                QString insertStr = model->data(index).toString();
                QModelIndex status = model->index(row,3);
                QModelIndex id = model->index(row,0);

                if(column == 2 || column == 3){
                    insertStr.replace("T", "  ");
                    insertStr.chop(7);
                }
                if(column == 3 && model->data(status).toInt() != 1){
                    dead = model->data(index).toDateTime();

                    if(!verificationDate(dead)){

                        int idForTable = model->data(id).toInt();
                        QModelIndex idStatus = model->index(row,4);
                        int stat = model->data(idStatus).toInt();
                        if(stat == 2){
                            db.editData("null",0,idForTable,"status");
                        }
                    }
                }
                if(column == 1){
                    QTextEdit *edit = new QTextEdit();
                    edit->setText(insertStr);
                    edit->setReadOnly(true);
                    widget->setCellWidget(row, column, edit);
                }
                else{
                    QTableWidgetItem *item = new QTableWidgetItem(insertStr);
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    widget->setItem(row, column, item);
                }
            }
        }

        // Установка заголовков столбцов
        widget->setHorizontalHeaderItem(0, idHeader); // 0 - индекс столбца "id"
        widget->setHorizontalHeaderItem(1, task); // 1 - индекс столбца "start date"
        widget->setHorizontalHeaderItem(2, startDateHeader); // 1 - индекс столбца "start date"
        widget->setHorizontalHeaderItem(3, deadlineHeader); // 2 - индекс столбца "deadline"
        widget->setHorizontalHeaderItem(4, statusHeader); // 3 - индекс столбца "status
        widget->verticalHeader()->setDefaultSectionSize(40);
        // set the resize mode to fixed, so the user cannot change the height/width

        widget->resizeColumnsToContents();
        widget->horizontalHeader()->setStretchLastSection(true);
    }
    else{
        qDebug() << "Что-то не так с соединением!";
    }
}

void removeInformation(QTableWidget* widget, dataBase db){
    int indexRow = 0;

    if(widget->rowCount() > 0){

        indexRow = widget->currentRow();
        auto indexToTable = widget->item(indexRow,0);
        QString value = indexToTable->text();
        db.removeData(value.toInt());

    }
}

bool verificationDate(QDateTime dead){
    bool flag = true;
    if(QDateTime::currentDateTime() >= dead){
        flag = false;
    }
    return flag;
}
