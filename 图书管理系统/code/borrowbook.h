#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QWidget>
#include <QtSql>
#include <QString>

namespace Ui {
class BorrowBook;
}

class BorrowBook : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowBook(QWidget *parent = nullptr, QString id = "");
    ~BorrowBook();


private slots:
    void on_back_clicked();

    void on_searchbutton_clicked();

    void on_listeverybookbutton_clicked();

    void on_refreshbutton_clicked();

    void on_borrowbutton_clicked();

private:
    Ui::BorrowBook *ui;
    QString aid;
};

#endif // BORROWBOOK_H
