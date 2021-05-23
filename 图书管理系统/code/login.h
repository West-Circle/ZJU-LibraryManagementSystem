#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "admingui.h"
#include "usersearchbook.h"
#include <QMessageBox>
#include <QString>
#include <QtSql>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_back_clicked();

    void on_Login_2_clicked();

private:
    Ui::Login *ui;
    AdminGUI *admingui;
    UserSearchBook *usb;
};

#endif // LOGIN_H
