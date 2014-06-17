//
//  Field.cpp
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#include "Field.h"


Field::Field(cocos2d::Layer* layer)
    :mLayer(layer)
{
    mPieces.resize(16);
}


void Field::update(const float delta)
{
    
}

void Field::moveField(const Field::MOVE_DIRECTION direction)
{
    
}

std::string Field::directionToString(const Field::MOVE_DIRECTION &direction)
{
    switch (direction) {
        case TOP:
            return "TOP";
            break;
        case LEFT:
            return "LEFT";
        case BOTTOM:
            return "BOTTOM";
            break;
        case RIGHT:
            return "RIGHT";
            break;
    }
    return "Unknown";
}