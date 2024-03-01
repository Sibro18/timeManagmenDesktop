#ifndef UPDATEFORM_H
#define UPDATEFORM_H

#include <QDialog>
#include "database.h"
#include <QRegularExpression>
#include <QSqlQueryModel>
#include <QTableWidget>

namespace Ui {
class updateForm;
}

class updateForm : public QDialog
{
    Q_OBJECT

public:
    explicit updateForm(dataBase &base, QList<QString> values, QWidget *parent = nullptr);
    ~updateForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::updateForm *ui;
    dataBase db;
    int indexFromTable;
    void supportFun(QString data, QString param);
};

#endif // UPDATEFORM_H
