#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QSqlQueryModel>
#include <QTableWidget>
#include "insertintableform.h"
#include "database.h"
#include "updateform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAction1Triggered();
    void onAction2Triggered();
    void onAction3Triggered();
    void onAction4Triggered();
    void onAction5Triggered();
    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
    QToolBar *toolbar;
    updateForm* updForm;
    dataBase db;
    insertInTableForm* addForm;
};
#endif // MAINWINDOW_H
