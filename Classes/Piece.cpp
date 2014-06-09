//
//  Piece.cpp
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#include "Piece.h"

Piece::Piece(const int color)
    :mColor(color)
{
}

int Piece::getColor() const
{
    return  mColor;
}