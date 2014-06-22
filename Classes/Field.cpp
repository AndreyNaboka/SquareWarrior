//
//  Field.cpp
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#include "Field.h"
#include <iostream>

//----------------------------------------------------------------------------------------------------------
Field::Field(cocos2d::Layer* layer)
    :mLayer(layer)
{
    // Field background
    cocos2d::Sprite* background = cocos2d::Sprite::create("background.png");
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    const float backgroundWidthScale = visibleSize.width / background->getContentSize().width;
    const float backgroundHeightScale = visibleSize.height / background->getContentSize().height;
    background->setScale(backgroundWidthScale, backgroundHeightScale);
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    background->setPosition(origin.x + (visibleSize.width/2), origin.y + (visibleSize.height/2));
    mLayer->addChild(background);
    
    
    // Pieces prepare
    const float cellWidth = visibleSize.width / 4;
    const float cellHeight = cellWidth;
    const float topStartPosY = cellHeight * 4;
    for (int w = 0; w < FIELD_WIDTH; ++w) {
        for (int h = 0; h < FIELD_HEIGHT; ++h) {
            auto newPiece = mField.insert(mField.end(), PiecePtr(new Piece()));
            (*newPiece)->setCoords(w, h);
            
            mFieldMap[w][h] = cocos2d::Sprite::create(Piece::colorToSpriteName((*newPiece)->getColor()));
            const float cellSpriteWidth = mFieldMap[w][h]->getContentSize().width;
            const float cellSpriteHeight = mFieldMap[w][h]->getContentSize().height;

            mFieldMap[w][h]->setScale(cellWidth / cellSpriteWidth, cellHeight / cellSpriteHeight);
            mFieldMap[w][h]->setPosition(cellWidth * w + (cellWidth/2), topStartPosY - (cellHeight * h) - (cellHeight/2));
            mLayer->addChild(mFieldMap[w][h]);
        }
    }
    
    addRandomWarrior();
}

//----------------------------------------------------------------------------------------------------------
void Field::update(const float delta)
{
    
}

//----------------------------------------------------------------------------------------------------------
void Field::moveField(const Field::MOVE_DIRECTION direction)
{
    addRandomWarrior();
}

//----------------------------------------------------------------------------------------------------------
void Field::addRandomWarrior(const int num)
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
    const int xPos = freePieces.at(randomIndex)->getX();
    const int yPos = freePieces.at(randomIndex)->getY();
    mFieldMap[xPos][yPos]->setTexture(Piece::colorToSpriteName(Piece::WHITE));
}

//----------------------------------------------------------------------------------------------------------
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
        default:
            return "UNKNOWN";
            break;
    }
}