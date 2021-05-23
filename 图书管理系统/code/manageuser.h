#ifndef MANAGEUSER_H
#define MANAGEUSER_H

#include <QWidget>
#include <QtSql>
#include <QString>
namespace Ui {
class ManageUser;
}

class ManageUser : public QWidget
{
    Q_OBJECT

public:
    explicit ManageUser(QWidget *parent = nullptr, QString id = "");
    ~ManageUser();

private slots:
    void on_back_clicked();

    void on_addcardbutton_clicked();

    void on_searchcardinfobutton_clicked();

    void on_refreshbutton_clicked();

    void on_deletecardbutton_clicked();

    void on_searchcnobutton_clicked();

private:
    Ui::ManageUser *ui;
    QString aid;
};

#endif // MANAGEUSER_H
