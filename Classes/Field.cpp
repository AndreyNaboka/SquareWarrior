//
//  Field.cpp
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#include "Field.h"
#include <iostream>


Field::Field(cocos2d::Layer* layer)
    :mLayer(layer)
{
    for (int w = 0; w < FIELD_WIDTH; ++w) {
        for (int h = 0; h < FIELD_HEIGHT; ++h) {
            auto newPiece = mField.insert(mField.end(), PiecePtr(new Piece()));
            (*newPiece)->setCoords(w, h);
        }
    }
}


void Field::update(const float delta)
{
    addRandomWarrior();
}

void Field::moveField(const Field::MOVE_DIRECTION direction)
{
    
}

void Field::addRandomWarrior()
{
    std::vector<PiecePtr> freePieces;
    freePieces.reserve(mField.size());
    for (auto i = mField.begin(); i != mField.end(); ++i) {
        if ((*i)->getColor()==Piece::BLACK)
            freePieces.push_back(*i);
    }
    
    if (freePieces.size()==0) {
        return;
    }
    
    int randomIndex = rand() % freePieces.size();
    freePieces.at(randomIndex)->setColor(Piece::WHITE);
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