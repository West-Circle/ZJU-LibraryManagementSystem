#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include "register.h"

namespace Ui {
class Authentication;
}

class Authentication : public QWidget
{
    Q_OBJECT

public:
    explicit Authentication(QWidget *parent = nullptr);
    ~Authentication();
    QString code = "adminregister";

private slots:
    void on_authentic_button_clicked();

    void on_back_button_clicked();

private:
    Ui::Authentication *ui;
    Register *reg;
};

#endif // AUTHENTICATION_H
