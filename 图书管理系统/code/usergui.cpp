#include "usergui.h"
#include "ui_usergui.h"

UserGUI::UserGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserGUI)
{
    ui->setupUi(this);
}

UserGUI::~UserGUI()
{
    delete ui;
}
