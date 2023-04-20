#include "menu.h"
#include "ui_menu.h"
#include <QDebug>
#include <QToolButton>
#include "game.h"


menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    connect(menu::findChild<QPushButton *>("StartNewGame"),SIGNAL(released()),this,SLOT(onMenuButtonClick()));
    connect(menu::findChild<QToolButton *>("EndGame"),SIGNAL(released()),this,SLOT(onMenuButtonClick()));
    connect(menu::findChild<QToolButton *>("LoadGame"),SIGNAL(released()),this,SLOT(onMenuButtonClick()));
}

menu::~menu()
{
    delete ui;
}


void menu::onMenuButtonClick()
{
    QToolButton *btn = (QToolButton *)sender();
    if(btn->objectName() =="StartNewGame") {
        gameWindow = new MainWindow(this);
        gameWindow->show();
        this->hide();
    }

    if(btn->objectName() =="EndGame") {
        QApplication::quit();
    }

    if(btn->objectName() == "LoadGame"){
        gameWindow = new MainWindow(this, "E:/magisterskie/I_ps/Zaawansowane_C++/chess-game-master/chess/img/saved.txt");
        gameWindow->show();
        this->hide();
    }
}

