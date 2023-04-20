#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include "game.h"
#include <QThread>
#include "menu.h"
#include <QFile>
#include <QTextStream>

extern Game *game;

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    setWindowTitle("Chess");
    ui->setupUi(this);
    game = new Game();
    setCurrentMoveLayout();

    for(int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j ++) {
            QPushButton *btn = getClickedButton(i, j);
            btn->setIcon(QIcon(""));
            btn->setIcon(QIcon(QString::fromStdString(game->getBoard()->getField(i,j)->getPiece()->getIconName())));
            connect(btn, SIGNAL(released()),this,SLOT(onFieldClick()));
        }
    }

    connect(MainWindow::findChild<QToolButton *>("SaveGame"),SIGNAL(released()),this,SLOT(onButtonClick()));
    connect(MainWindow::findChild<QToolButton *>("Quit"),SIGNAL(released()),this,SLOT(onButtonClick()));
    connect(MainWindow::findChild<QToolButton *>("BackToMenu"),SIGNAL(released()),this,SLOT(onButtonClick()));
}

MainWindow::MainWindow(QWidget *parent, string filePath)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    setWindowTitle("Chess");
    ui->setupUi(this);
    //******************************************
    string** tab;
    QString filename = "E:/magisterskie/I_ps/Zaawansowane_C++/chess-game-master/chess/img/saved.txt";
    QFile file(filename);

    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    tab=new string* [9];
    for (int i=0;i<9;i++)
       tab[i]=new string[9];
    for(int a=0; a<8; a++){
        QString data = stream.readLine();
        QList columns = data.split(",");
        //qDebug() << columns;




        int i = 0;
        for (auto str : columns){
            tab[a][i] = str.toStdString();
            //qDebug() << QString::fromStdString(tab[a][i]);
            i++;
        }

    }

    file.close();
    //******************************************
    game = new Game(tab);
    setCurrentMoveLayout();

    for(int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j ++) {
            QPushButton *btn = getClickedButton(i, j);
            btn->setIcon(QIcon(""));
            btn->setIcon(QIcon(QString::fromStdString(game->getBoard()->getField(i,j)->getPiece()->getIconName())));
            connect(btn, SIGNAL(released()),this,SLOT(onFieldClick()));
        }
    }

    connect(MainWindow::findChild<QToolButton *>("SaveGame"),SIGNAL(released()),this,SLOT(onButtonClick()));
    connect(MainWindow::findChild<QToolButton *>("Quit"),SIGNAL(released()),this,SLOT(onButtonClick()));
    connect(MainWindow::findChild<QToolButton *>("BackToMenu"),SIGNAL(released()),this,SLOT(onButtonClick()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onFieldClick() {
    QPushButton *field = (QPushButton *)sender();
    qDebug() << field->objectName();
    pair<int,int> position = getPosition(field->objectName().toStdString());
    Field * f = game->getBoard()->getField(position.first, position.second);
    qDebug() <<  QString::fromStdString(f->getPiece()->getIconName());

    if(game->getCurrentMove() == f->getPiece()->getColor() || isClicked) {
        if(!isClicked) {
            positionFrom = position;
            possiblePositions = f->getMoves(position.first, position.second);
            uncheckColors();
            field->setStyleSheet("QPushButton { background-color : #C3FFA1; }");
            colorPossibleMoves(possiblePositions);
            isClicked = true;
        } else { 
            positionTo = position;
            if(isEmpty(positionTo) && hasMove()) {
                game->getBoard()->swapPiece(positionFrom, positionTo);
                game->setGameOver();
                updateGame();
            } else if (isOpponent(positionTo) && hasMove()) {
                game->getBoard()->swapPiece(positionFrom, positionTo);
                game->setGameOver();
                updateGame();
            }
            isClicked = false;
            uncheckColors();
        }
    }
}

bool MainWindow::isEmpty(pair<int,int> positionTo) {
    if (dynamic_cast<EmptyField*>(game->getBoard()->getField(positionTo.first, positionTo.second)->getPiece()))
        return true;
    return false;
}

bool MainWindow::hasMove() {
    if(std::find(possiblePositions.begin(), possiblePositions.end(), positionTo) != possiblePositions.end())
       return true;
    return false;
}

bool MainWindow::isOpponent(pair<int,int> positionTo) {
    Color c = game->getBoard()->getField(positionTo.first, positionTo.second)->getPiece()->getColor();
    if(c != game->getCurrentMove() && c != INVISIBLE)
        return true;
    return false;
}

void MainWindow::uncheckColors() {
    for(int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j ++) {
            QPushButton *btn = getClickedButton(i,j);
            if((i+j) % 2 == 0 )
                btn->setStyleSheet("QPushButton {background-color: #F2DCB8;}");
            else
                btn->setStyleSheet("QPushButton {background-color: #B88C67;}");
        }
    }
}

void MainWindow::colorPossibleMoves(vector<pair<int,int>> moves) {
    for (auto & i : moves) {
        if(isEmpty(i))
            getClickedButton(i.first, i.second)->setStyleSheet("QPushButton {background-color: #F2FFDF;}");
        if(isOpponent(i))
            getClickedButton(i.first, i.second)->setStyleSheet("QPushButton {background-color: #800000;}");
    }

}

void MainWindow::onButtonClick() {
    QToolButton *btn = (QToolButton *)sender();
    if(btn->objectName() =="SaveGame") {
        QString filename = "E:/magisterskie/I_ps/Zaawansowane_C++/chess-game-master/chess/img/saved.txt";
        QFile file(filename);
        //QString white = "white";
        //QString black = "black";
        file.open(QIODevice::WriteOnly | QFile::Truncate);
        QTextStream xout(&file);
        xout << QString::fromStdString(game->allFields());
        xout << ((game->getCurrentMove() == BLACK) ? "black" : "white");
        file.close();
    }
    if(btn->objectName() == "Quit")
        QApplication::quit();

    if(btn->objectName() == "BackToMenu"){
        menu *wnd;
        wnd = new menu(this);
        this->hide();
        wnd->show();
    }

}

QPushButton * MainWindow::getClickedButton(int x, int y) {
    QString fieldName = "Field_" + QString::number(x) + QString::number(y);
    QPushButton *btn = MainWindow::findChild<QPushButton *>(fieldName);
    return btn;
}

pair<int,int> MainWindow::getPosition(string s) {
    string index = s.substr(s.length() - 2);
    int x = stoi(index.substr(0,1));
    int y = stoi(index.substr(1,2));
    return pair<int,int>(x,y);
}

void MainWindow::updateGame() {
    for(int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j ++) {
            QPushButton *btn = getClickedButton(i, j);
            btn->setIcon(QIcon(QString::fromStdString(game->getBoard()->getField(i,j)->getPiece()->getIconName())));
        }
    }
    isGameOver();
    setCurrentMoveLayout();
}

void MainWindow::setCurrentMoveLayout() {
    QToolButton *turn = MainWindow::findChild<QToolButton *>("Turn");
    game->setCurrentMove();
    if(game->getCurrentMove() == BLACK)
        turn->setIcon(QIcon(QString::fromStdString(":/img/pawn.png")));
    else
        turn->setIcon(QIcon(QString::fromStdString(":/img/pawn_white.png" )));
}

void MainWindow::isGameOver(){
    if(game->getGameOver()) {
        QString msg = "The winner is color: " + QString::fromStdString((game->getCurrentMove() == WHITE) ? "WHITE" : "BLACK");
        qDebug()<<msg;
        QMessageBox::about(this,"Game Over", msg);
        game->endGame();
    }

}

