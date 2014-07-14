//
//  Piece.h
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#ifndef __SquareWarrior__Piece__
#define __SquareWarrior__Piece__

#include <string>
#include <memory>
#include "cocos2d.h"


class Piece {
public:
    enum COLORS {
        BLACK,
        COLOR_2,
        COLOR_4,
        COLOR_8,
        COLOR_16,
        COLOR_32,
        COLOR_64,
        COLOR_128,
        COLOR_256,
        COLOR_512,
        COLOR_1024,
        COLOR_2048,
        HIGHEST_COLOR
    };
    static COLORS getNextColor(const COLORS& currentColor);
    
public:
    Piece();
    COLORS getColor() const;
    void setCoords(const int x, const int y) { mX = x; mY = y; }
    void setColor(const COLORS color);
    int  getX() const { return mX; }
    int  getY() const { return mY; }
    
    static std::string colorToSpriteName(const Piece::COLORS color);
    
private:
    int mX, mY;
    COLORS mColor;
};

typedef std::shared_ptr<Piece> PiecePtr;

#endif /* defined(__SquareWarrior__Piece__) */
