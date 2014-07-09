//
//  Piece.cpp
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#include "Piece.h"

/**********************************************************/
Piece::Piece()
    :mColor(BLACK)
{
}

/**********************************************************/
Piece::COLORS Piece::getColor() const
{
    return mColor;
}

/**********************************************************/
void Piece::setColor(const Piece::COLORS color)
{
    if (mColor == color) return;
    mColor = color;
}

/**********************************************************/
std::string Piece::colorToSpriteName(const Piece::COLORS color)
{
    switch (color) {
    case BLACK:
        return "black.png";
        break;
    case WHITE:
        return "white.png";
        break;
    case YELLOW:
        return "yellow.png";
        break;
    case GREEN:
        return "green.png";
        break;
    case RED:
        return "red.png";
        break;
    default:
        return "unknown";
    };
    return "";
}

/**********************************************************/
Piece::COLORS Piece::getNextColor(const COLORS& currentColor) 
{
    switch (currentColor) {
        case BLACK:
            return WHITE;
            break;
        case WHITE:
            return YELLOW;
            break;
        case YELLOW:
            return GREEN;
            break;
        case GREEN:
            return RED;
            break;
        case RED:
            return HIGHEST_COLOR;
            break;
        default:
            return BLACK;
    };
}