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
            mField[w][h] = Piece::COLORS::BLACK;
            
            mFieldMap[w][h] = cocos2d::Sprite::create(Piece::colorToSpriteName(Piece::COLORS::BLACK));
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
    switch (direction) {
        case LEFT:
            moveLeft();
            break;
        case RIGHT:
            moveRight();
            break;
        case TOP:
            moveTop();
            break;
        case BOTTOM:
            moveBottom();
            break;
        default:
            return;
    }
    addRandomWarrior();
}

//----------------------------------------------------------------------------------------------------------
void Field::moveLeft()
{
    
}

//----------------------------------------------------------------------------------------------------------
void Field::moveRight()
{
    
}

//----------------------------------------------------------------------------------------------------------
void Field::moveTop()
{
    
}

//----------------------------------------------------------------------------------------------------------
void Field::moveBottom()
{
    
}

//----------------------------------------------------------------------------------------------------------
void Field::addRandomWarrior(const int num)
{
    std::vector<cocos2d::Vec2> freePieces;
    for (int w = 0; w < FIELD_WIDTH; ++w) {
        for (int h = 0; h < FIELD_HEIGHT; ++h) {
            if (mField[w][h] == Piece::COLORS::BLACK)
                freePieces.push_back(cocos2d::Vec2(w,h));
        }
    }
    
    if (freePieces.size() == 0)
        return;
    
    
    int randomIndex = rand() % freePieces.size();
    const int x = freePieces.at(randomIndex).x;
    const int y = freePieces.at(randomIndex).y;
    mField[x][y] = Piece::COLORS::WHITE;
    mFieldMap[x][y]->setTexture(Piece::colorToSpriteName(Piece::WHITE));
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