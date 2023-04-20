#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class menu;
}

/**
 *  @file   menu.h
 *  @brief  Menu for whole game
 *  @author Artur Szukalski
 *  @date   18-04-2023
 ***********************************************/
class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void onMenuButtonClick();

private:
    Ui::menu *ui;
    MainWindow *gameWindow;
};

#endif // MENU_H
