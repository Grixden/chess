#include "board.h"
#include <QString>
//
#include <QDebug>

Board::Board() {
    fields = new Field**[8];
    for(int i = 0; i < 8; i++ ) {
        fields[i] = new Field*[8];
        for(int j = 0; j < 8; j++) {
            fields[i][j] = new Field();
            if(i == 0) {
                if(j==0 || j==7)
                    fields[i][j]->setPiece(new Rook(), BLACK,":/img/rook.png");
                if(j==1 || j==6)
                    fields[i][j]->setPiece(new Knight(), BLACK, ":/img/knight.png");
                if(j==2 || j==5)
                    fields[i][j]->setPiece(new Bishop(), BLACK,":/img/bishop.png");
                if(j==3)
                    fields[i][j]->setPiece(new Queen(), BLACK, ":/img/queen.png");
                if(j==4)
                    fields[i][j]->setPiece(new King(), BLACK, ":/img/king.png");
             }

             if(i == 7) {
                if(j==0 || j==7)
                    fields[i][j]->setPiece(new Rook(), WHITE, ":/img/rook_white.png");
                if(j==1 || j==6)
                    fields[i][j]->setPiece(new Knight(), WHITE, ":/img/knight_white.png");
                if(j==2 || j==5)
                    fields[i][j]->setPiece(new Bishop(), WHITE, ":/img/bishop_white.png");
                if(j==3)
                    fields[i][j]->setPiece(new Queen(), WHITE, ":/img/queen_white.png");
                if(j==4)
                    fields[i][j]->setPiece(new King(), WHITE, ":/img/king_white.png");
             }

             if (i == 1)
                fields[i][j]->setPiece(new Pawn(), BLACK, ":/img/pawn.png");
             if(i == 6)
                fields[i][j]->setPiece(new Pawn(), WHITE, ":/img/pawn_white.png");
             if(i > 1 && i < 6)
                 fields[i][j]->setPiece(new EmptyField(), INVISIBLE, "");

        }
    }
}

Board::Board(string** loadedConfig) {
    Color color;
    fields = new Field**[8];
    for(int i = 0; i < 9; i++ ) {
        fields[i] = new Field*[8];
        for(int j = 0; j < 8; j++) {
            fields[i][j] = new Field();
            string iconPath = loadedConfig[i][j];
            qDebug() << QString::fromStdString(iconPath);

            if(QString::fromStdString(iconPath).contains("white"))
                color = WHITE;
            else if (!QString::fromStdString(iconPath).contains("_") & iconPath != "")
                color = BLACK;
            else
                color = INVISIBLE;

            if(QString::fromStdString(iconPath).contains("rook"))
                fields[i][j]->setPiece(new Rook(), color, iconPath);
            else if(QString::fromStdString(iconPath).contains("knight"))
                fields[i][j]->setPiece(new Knight(), color, iconPath);
            else if(QString::fromStdString(iconPath).contains("bishop"))
                fields[i][j]->setPiece(new Bishop(), color, iconPath);
            else if(QString::fromStdString(iconPath).contains("queen"))
                fields[i][j]->setPiece(new Queen(), color, iconPath);
            else if(QString::fromStdString(iconPath).contains("king"))
                fields[i][j]->setPiece(new King(), color, iconPath);
            else if(QString::fromStdString(iconPath).contains("pawn"))
                fields[i][j]->setPiece(new Pawn(), color, iconPath);
            else if(loadedConfig[i][j] == "")
                fields[i][j]->setPiece(new EmptyField(), color, iconPath);

        }
    }
}

Board::~Board() {
    for (int i=0; i<8; i++) {
        delete[] fields[i];
    }
    delete[] fields;
}

void Board::swapPiece(pair<int,int> previousPosition, pair<int,int> newPosition) {
    int x0 = previousPosition.first;
    int y0 = previousPosition.second;

    int x = newPosition.first;
    int y = newPosition.second;

    Piece* ptr = fields[x0][y0]->getPiece();
    Color color = fields[x0][y0]->getPiece()->getColor();
    string _white = color == WHITE ? "_white.png" : ".png";

       if (dynamic_cast<EmptyField*>(ptr))
            fields[x][y]->setPiece(new EmptyField(), INVISIBLE, "");
       if (dynamic_cast<Pawn*>(ptr))
            fields[x][y]->setPiece(new Pawn(), color, ":/img/pawn" + _white);
       if (dynamic_cast<Knight*>(ptr))
            fields[x][y]->setPiece(new Knight(), color, ":/img/knight" + _white);
       if (dynamic_cast<Bishop*>(ptr))
            fields[x][y]->setPiece(new Bishop(), color, ":/img/bishop" + _white);
       if (dynamic_cast<King*>(ptr))
            fields[x][y]->setPiece(new King(), color, ":/img/king" + _white);
       if (dynamic_cast<Queen*>(ptr))
            fields[x][y]->setPiece(new Queen(), color, ":/img/queen" + _white);
       if (dynamic_cast<Rook*>(ptr))
            fields[x][y]->setPiece(new Rook(), color, ":/img/rook" + _white);


   fields[x0][y0]->setPiece(new EmptyField(), INVISIBLE, "");
}

bool Board::isKingMatted() {
    int kings = 0;
    for (int i = 0; i < 8 ;i++) {
        for (int j = 0; j < 8 ;j++){
            if (dynamic_cast<King*>(getField(i,j)->getPiece())) {
                kings++;
            }
            if(kings == 2) {
                return false;
            }
        }
    }
    if (kings < 2)
        return true;
}

Field* Board::getField(int x, int y) {
    return fields[x][y];
}
