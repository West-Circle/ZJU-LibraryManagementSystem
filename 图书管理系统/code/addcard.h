#ifndef ADDCARD_H
#define ADDCARD_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
namespace Ui {
class AddCard;
}

class AddCard : public QWidget
{
    Q_OBJECT

public:
    explicit AddCard(QWidget *parent = nullptr, QString id = "");
    ~AddCard();

private slots:
    void on_addcardbutton_clicked();

private:
    Ui::AddCard *ui;
    QString aid;
};

#endif // ADDCARD_H
