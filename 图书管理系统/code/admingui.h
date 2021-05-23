#ifndef ADMINGUI_H
#define ADMINGUI_H

#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QString>
#include <QtSql>
#include "insertbook.h"
#include "returnbook.h"
#include "manageuser.h"
#include "borrowbook.h"

namespace Ui {
class AdminGUI;
}

class AdminGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminGUI(QWidget *parent = nullptr, QString id = "");
    ~AdminGUI();

private slots:
    void on_actionAbout_Qt_triggered();

    void on_actionAbout_System_triggered();

    void on_insertbookbutton_clicked();

    void on_borrowbookbutton_clicked();

    void on_returnbookbutton_clicked();

    void on_manageuserbutton_clicked();

    void on_actionInsert_Book_triggered();

    void on_actionBorrow_Book_2_triggered();

    void on_actionReturn_Book_2_triggered();

    void on_actionManage_User_2_triggered();

    void on_actionExit_triggered();

    void on_actionExit_2_triggered();

private:
    Ui::AdminGUI *ui;
    QString aid;
    InsertBook *ib;
    BorrowBook *bb;
    ReturnBook *rb;
    ManageUser *mu;
};

#endif // ADMINGUI_H
