//
//  Field.h
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#ifndef __SquareWarrior__Field__
#define __SquareWarrior__Field__

#include "cocos2d.h"
#include "Piece.h"
#include <vector>

class Field {
public:
    
    enum MOVE_DIRECTION {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        UNKNOWN
    };
    
    static std::string directionToString(const MOVE_DIRECTION& direction);
    
    Field(cocos2d::Layer *layer);
    void update(const float delta);
    void moveField(const MOVE_DIRECTION direction);
    
private:
    void addRandomWarrior(const int num = 1);
    void moveLeft();
    void moveRight();
    void moveTop();
    void moveBottom();
    
private:
    cocos2d::Layer* mLayer;
    
    static const int FIELD_WIDTH = 4;
    static const int FIELD_HEIGHT = 4;
    Piece::COLORS mField[FIELD_WIDTH][FIELD_HEIGHT];
    cocos2d::Sprite* mFieldMap[FIELD_WIDTH][FIELD_HEIGHT];
};

typedef std::shared_ptr<Field> FieldPtr;


#endif /* defined(__SquareWarrior__Field__) */
