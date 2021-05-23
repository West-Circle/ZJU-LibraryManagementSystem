#ifndef INSERTBOOK_H
#define INSERTBOOK_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QTextCodec>
#include <QtDebug>
namespace Ui {
class InsertBook;
}

class InsertBook : public QWidget
{
    Q_OBJECT

public:
    explicit InsertBook(QWidget *parent = nullptr,QString id = "");
    ~InsertBook();


private slots:
    void on_back_clicked();

    void on_insertbookbutton_clicked();

    void on_insertmanybookbutton_clicked();

    void on_pushButton_clicked();

private:
    Ui::InsertBook *ui;
    QString aid;
};

#endif // INSERTBOOK_H
