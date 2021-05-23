#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QApplication>
#include <QMessageBox>
#include <QtDebug>
#include <QtWidgets>
#include <QSqlQuery>
#include "login.h"
#include "register.h"
#include "authentication.h"
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

    void on_loginbutton_clicked();

    void on_registerbutton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Login *login;
    Register *reg;
    Authentication *au;
};
#endif // MAINWINDOW_H
