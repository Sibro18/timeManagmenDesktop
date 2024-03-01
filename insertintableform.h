#ifndef INSERTINTABLEFORM_H
#define INSERTINTABLEFORM_H

#include <QDialog>
#include <QRegularExpression>
#include <QSqlQueryModel>
#include <QTableWidget>

#include "database.h"

namespace Ui {
class insertInTableForm;
}

class insertInTableForm : public QDialog
{
    Q_OBJECT

public:
    explicit insertInTableForm(dataBase& base,QWidget *parent = nullptr);
    ~insertInTableForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::insertInTableForm *ui;
    dataBase db;
};

#endif // INSERTINTABLEFORM_H
