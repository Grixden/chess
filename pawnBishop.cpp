#include "pawnBishop.h"
#include <game.h>
extern Game * game;

vector<pair<int,int>> PawnBishop::getPossiblePieceMoves(int x, int y) {
    moves.clear();

    int dir[]={-1,0,1};


    if(game->getCurrentMove() == BLACK){
        for(int k = 0; k < 3; k++){
            int newX = x+1;
            int newY = y+dir[k];
            if((newX >= 0 && newX < 8) && (newY >= 0 && newY < 8 )){
                printf("x: ");
                pair<int,int> pos(newX, newY);
                if(isOpponent(pos) && newY != y)
                    moves.push_back(pos);
                else if(isEmpty(pos) && newY == y)
                    moves.push_back(pos);
            }
        }

        if(x == 1){
            pair<int,int> pos(3, y);
            if(isEmpty(pos))
                moves.push_back(pos);
        }
    } else {
        for(int k = 0; k < 3; k++){
            int newX = x-1;
            int newY = y+dir[k];
            if((newX >= 0 && newX < 8) && (newY >= 0 && newY<8)){
                pair<int,int> pos(newX, newY);
                if(isOpponent(pos) && newY != y)
                    moves.push_back(pos);
                else if(isEmpty(pos) && newY == y)
                    moves.push_back(pos);
            }
        }

        if(x == 6){
            pair<int,int> pos(4, y);
            if(isEmpty(pos))
                moves.push_back(pos);
        }
    }


    int dir1[]={1,2,3,4,5,6,7};
    bool f1 = true, f2 = true, f3 = true, f4 = true;
    bool opponent = false;

    for(int k = 0; k < 7; k++){
        int newX = x+dir1[k];
        int newY = y+dir1[k];
        if((newX >= 0 && newX < 8) && (newY >= 0 && newY < 8) && f1){
            pair<int,int> pos(newX, newY);
            opponent = isOpponent(pos);
            if(opponent || isEmpty(pos))
                moves.push_back(pos);
            else
                f1 = false;
            if(opponent)
                f1 = false;

        }
        newX = x-dir1[k];
        newY = y-dir1[k];
        if((newX >= 0 && newX < 8) && (newY >= 0 && newY < 8) && f2){
            pair<int,int> pos(newX, newY);
            opponent = isOpponent(pos);
            if(opponent || isEmpty(pos))
                moves.push_back(pos);
            else
                f2 = false;
            if(opponent)
                f2 = false;
        }
        newX = x+dir1[k];
        newY = y-dir1[k];
        if((newX >= 0 && newX < 8) && (newY >= 0 && newY < 8) && f3){
            pair<int,int> pos(newX, newY);
            opponent = isOpponent(pos);
            if(opponent || isEmpty(pos))
                moves.push_back(pos);
            else
                f3 = false;
            if(opponent)
                f3 = false;
        }
        newX = x-dir1[k];
        newY = y+dir1[k];
        if((newX >= 0 && newX < 8) && (newY >= 0 && newY < 8) && f4){
            pair<int,int> pos(newX, newY);
            opponent = isOpponent(pos);
            if(opponent || isEmpty(pos))
                moves.push_back(pos);
            else
                f4 = false;
            if(opponent)
                f4 = false;
        }
    }


    return moves;
}


