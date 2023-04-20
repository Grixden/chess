#ifndef GAME_H
#define GAME_H

#include "pawn.h"
#include "emptyfield.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "Color.h"
#include "board.h"


/**
 *  @file   game.h
 *  @brief  Class which represents single game. At first game must be created then other behaviours.
 *  @author Artur Szukalski
 *  @date   18-04-2023
 ***********************************************/
class Game {

private:
    Color currentMove;
    vector<pair<int,int>> pieceMoves;
    bool isGameOver = false;
    Board * board;
    string summarizeFields;

public:
    /**
     *  @brief No-args constructor for Game class. Here board is created.
     ***********************************************/
    Game();
    /**
     *  @brief Constructor for Game class. Here board is created based on pieces position from file.
     *  @param loadedConfig two-dimensional table with pieces positions
     ***********************************************/

    Game(string** loadedConfig);
    /**
     *  @brief Destructor for Game class. All initialized fields in table are deleted.
     ***********************************************/
    ~Game();
    /**
     *  @brief Get current move color
     *  @return Returns piece color which turn is now
     ***********************************************/
    Color getCurrentMove();
    /**
     *  @return Returns true if game is over
     ***********************************************/
    bool getGameOver();
    /**
     *  @brief Sets game over flag
     *  @return Void
     ***********************************************/
    void setGameOver();
    /**
     *  @brief Fills all fields with empty field
     *  @return Void
     ***********************************************/
    void endGame();
    /**
     *  @brief Sets black or white piece move
     *  @return Void
     ***********************************************/
    void setCurrentMove();
    /**
     *  @brief Get current board
     *  @return Returns board
     ***********************************************/
    Board* getBoard();
    /**
     *  @brief Save each field status to one string
     *  @return string
     ***********************************************/
    string allFields();
};

#endif // GAME_H
