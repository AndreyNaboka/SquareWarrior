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

class Field {
public:
    
    enum MOVE_DIRECTION {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };
    
    Field(cocos2d::Layer *layer);
    void update(const float delta);
    void moveField(const MOVE_DIRECTION direction);
    
private:
    cocos2d::Layer* mLayer;
};

typedef std::shared_ptr<Field> FieldPtr;


#endif /* defined(__SquareWarrior__Field__) */
