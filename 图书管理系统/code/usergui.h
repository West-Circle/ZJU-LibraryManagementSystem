#ifndef USERGUI_H
#define USERGUI_H

#include <QMainWindow>

namespace Ui {
class UserGUI;
}

class UserGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserGUI(QWidget *parent = nullptr);
    ~UserGUI();

private:
    Ui::UserGUI *ui;
};

#endif // USERGUI_H
