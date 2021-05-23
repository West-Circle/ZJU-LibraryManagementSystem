#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QApplication>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_back_clicked();

    void on_Login_2_clicked();

    void on_RegisterButton_clicked();

private:
    Ui::Register *ui;

};

#endif // REGISTER_H
