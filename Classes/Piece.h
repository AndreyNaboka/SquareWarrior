//
//  Piece.h
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#ifndef __SquareWarrior__Piece__
#define __SquareWarrior__Piece__
#include <memory>



class Piece {
public:
    enum COLORS {
        BLACK,
        WHITE,
        YELLOW,
        GREEN,
        RED
    };

public:
    Piece();
    COLORS getColor() const;
    void setCoords(const int x, const int y) { mX = x; mY = y; }
    void setColor(const COLORS color)        { mColor = color; }
    int  getX() const { return mX; }
    int  getY() const { return mY; }
private:
    int mX, mY;
    COLORS mColor;
};

typedef std::shared_ptr<Piece> PiecePtr;

#endif /* defined(__SquareWarrior__Piece__) */
