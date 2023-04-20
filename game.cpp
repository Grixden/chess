#include "game.h"
#include <string>

Game::Game() {
    board = new Board();
    currentMove = BLACK;
}

Game::Game(string** loadedConfig) {
    board = new Board(loadedConfig);
    currentMove = (loadedConfig[8][1] == "black") ? BLACK : WHITE;
}


Game::~Game() {

}

Color Game::getCurrentMove() {
    return currentMove;
}

void Game::setCurrentMove() {
    currentMove = currentMove == BLACK ? WHITE : BLACK;
}

bool Game::getGameOver() {
    return isGameOver;
}

void Game::setGameOver() {
    this->isGameOver = board->isKingMatted();
}

void Game::endGame() {
    for(int i = 0; i < 8 ;i++)
        for(int j = 0; j < 8 ;j++)
            board->getField(i,j)->setPiece(new EmptyField(), INVISIBLE, "");
}

Board* Game::getBoard() {
    return this->board;
}

string Game::allFields(){
    for(int i = 0; i < 8 ;i++){
        for(int j = 0; j < 8 ;j++){
            summarizeFields += board->getField(i,j)->getPiece()->getIconName();
            if(j < 7)
                summarizeFields += ",";
        }
        summarizeFields += "\r\n";
    }
    return summarizeFields;
}
