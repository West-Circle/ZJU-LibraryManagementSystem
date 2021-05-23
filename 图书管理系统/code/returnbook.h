#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QWidget>
#include <QtSql>

namespace Ui {
class ReturnBook;
}

class ReturnBook : public QWidget
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = nullptr, QString id = "");
    ~ReturnBook();

private slots:
    void on_back_clicked();

    void on_listallborrowhistorybutton_clicked();

    void on_searchcnoborrowhistorybutton_clicked();

    void on_returnbookbutton_clicked();

private:
    Ui::ReturnBook *ui;
    QString aid;
};

#endif // RETURNBOOK_H
