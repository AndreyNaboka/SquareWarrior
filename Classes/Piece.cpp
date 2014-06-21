//
//  Piece.cpp
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#include "Piece.h"

Piece::Piece()
    :mColor(BLACK)
{
}

Piece::COLORS Piece::getColor() const
{
    return  mColor;
}