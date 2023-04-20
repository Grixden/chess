#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

/**
 *  @file   rook.h
 *  @brief  Child class which inherits behaviour for piece
 *  @author Artur Szukalski
 *  @date   18-04-2023
 ***********************************************/
class Rook : public Piece {

public:
    /**
     *  @brief Method calculates possible moves for rook
     *  @param x X-coordinate in field table
     *  @param y Y-coordinate in field table
     *  @return Returns vector of points where piece (rook) can move
     ***********************************************/
    virtual vector<pair<int,int>> getPossiblePieceMoves(int x, int y) override;
};

#endif // ROOK_H
