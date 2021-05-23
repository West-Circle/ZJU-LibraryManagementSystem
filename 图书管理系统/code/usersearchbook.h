#ifndef USERSEARCHBOOK_H
#define USERSEARCHBOOK_H

#include <QWidget>
#include <QtSql>
#include <QString>
#include <QMessageBox>
namespace Ui {
class UserSearchBook;
}

class UserSearchBook : public QWidget
{
    Q_OBJECT

public:
    explicit UserSearchBook(QWidget *parent = nullptr, QString id = "");
    ~UserSearchBook();

private slots:
    void on_searchbutton_clicked();

    void on_listeverybookbutton_clicked();

    void on_refreshbutton_clicked();

    void on_logout_clicked();

private:
    Ui::UserSearchBook *ui;
};

#endif // USERSEARCHBOOK_H
