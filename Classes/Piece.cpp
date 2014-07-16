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
int Piece::getDamage(const Piece::COLORS& color)
{
    switch (color) {
        case BLACK:
            return 0;
            break;
        case COLOR_2:
            return 2;
            break;
        case COLOR_4:
            return 4;
            break;
        case COLOR_8:
            return 8;
            break;
        case COLOR_16:
            return 16;
            break;
        case COLOR_32:
            return 32;
            break;
        case COLOR_64:
            return 64;
            break;
        case COLOR_128:
            return 128;
            break;
        case COLOR_256:
            return 256;
            break;
        case COLOR_512:
            return 512;
            break;
        case COLOR_1024:
            return 1024;
            break;
        case COLOR_2048:
            return 2048;
            break;
        default:
            return 0;
    };
    return 0;
}

/**********************************************************/
std::string Piece::colorToSpriteName(const Piece::COLORS color)
{
    switch (color) {
    case BLACK:
        return "black.png";
        break;
    case COLOR_2:
        return "2.png";
        break;
    case COLOR_4:
        return "4.png";
        break;
    case COLOR_8:
        return "8.png";
        break;
    case COLOR_16:
        return "16.png";
        break;
    case COLOR_32:
        return "32.png";
        break;
    case COLOR_64:
        return "64.png";
        break;
    case COLOR_128:
        return "128.png";
        break;
    case COLOR_256:
        return "256.png";
        break;
    case COLOR_512:
        return "512.png";
        break;
    case COLOR_1024:
        return "1024.png";
        break;
    case COLOR_2048:
        return "2048.png";
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
        case COLOR_2:
            return COLOR_4;
            break;
        case COLOR_4:
            return COLOR_8;
            break;
        case COLOR_8:
            return COLOR_16;
            break;
        case COLOR_16:
            return COLOR_32;
            break;
        case COLOR_32:
            return COLOR_64;
            break;
        case COLOR_64:
            return COLOR_128;
            break;
        case COLOR_128:
            return COLOR_256;
            break;
        case COLOR_256:
            return COLOR_512;
            break;
        case COLOR_512:
            return COLOR_1024;
            break;
        case COLOR_1024:
            return COLOR_2048;
            break;            
        default:
            return BLACK;
    };
}