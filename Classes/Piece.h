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
    Piece(const int color);
    int getColor() const;
    
private:
    int mColor;
};

typedef std::shared_ptr<Piece> PiecePtr;

#endif /* defined(__SquareWarrior__Piece__) */
